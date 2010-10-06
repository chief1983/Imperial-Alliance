#include "EH_Medals/webget.h"

using namespace std;


////////////////////////////////////////////////////////////////////////////////////////////////

void CGetWebpage::MemBufferCreate(MemBuffer *b)
{
    b->size = MEM_BUFFER_SIZE;
    b->buffer =(unsigned	char *) malloc( b->size );
    b->position = b->buffer;
}

////////////////////////////////////////////////////////////////////////////////////////////////

void CGetWebpage::MemBufferGrow(MemBuffer *b)
{
    size_t sz;
    sz = b->position - b->buffer;
    b->size = b->size *2;
    b->buffer =(unsigned	char *) realloc(b->buffer,b->size);
    b->position = b->buffer + sz;	// readjust current position
}

////////////////////////////////////////////////////////////////////////////////////////////////

void CGetWebpage::MemBufferAddByte(MemBuffer *b,unsigned char byt)
{
    if( (size_t)(b->position-b->buffer) >= b->size )
        MemBufferGrow(b);

    *(b->position++) = byt;
}

////////////////////////////////////////////////////////////////////////////////////////////////

void CGetWebpage::MemBufferAddBuffer(MemBuffer *b,unsigned char *buffer, size_t size)
{
    while( ((size_t)(b->position-b->buffer)+size) >= b->size )
        MemBufferGrow(b);

    memcpy(b->position,buffer,size);
    b->position+=size;
}

////////////////////////////////////////////////////////////////////////////////////////////////

DWORD CGetWebpage::GetHostAddress(LPCSTR host)
{
    struct hostent *phe;
    char *p;

    phe = gethostbyname( host );
            
    if(phe==NULL)
        return 0;
    
    p = *phe->h_addr_list;
    return *((DWORD*)p);
}

////////////////////////////////////////////////////////////////////////////////////////////////

void CGetWebpage::SendString(SOCKET sock,LPCSTR str)
{
    send(sock,str,strlen(str),0);
}

////////////////////////////////////////////////////////////////////////////////////////////////

BOOL CGetWebpage::ValidHostChar(char ch)
{
    return( isalpha(ch) || isdigit(ch)
        || ch=='-' || ch=='.' || ch==':' );
}

////////////////////////////////////////////////////////////////////////////////////////////////

void CGetWebpage::ParseURL(LPCSTR url,LPSTR protocol,int lprotocol,
        LPSTR host,int lhost,LPSTR request,int lrequest,int *port)
{
    char *work,*ptr,*ptr2;

    *protocol = *host = *request = 0;
    *port=80;

    work = strdup(url);
    strupr(work);

    ptr = strchr(work,':');							// find protocol if any
    if(ptr!=NULL)
    {
        *(ptr++) = 0;
        lstrcpyn(protocol,work,lprotocol);
    }
    else
    {
        lstrcpyn(protocol,"HTTP",lprotocol);
        ptr = work;
    }

    if( (*ptr=='/') && (*(ptr+1)=='/') )			// skip past opening /'s 
        ptr+=2;

    ptr2 = ptr;										// find host
    while( ValidHostChar(*ptr2) && *ptr2 )
        ptr2++;

    *ptr2=0;
    lstrcpyn(host,ptr,lhost);

    lstrcpyn(request,url + (ptr2-work),lrequest);	// find the request

    ptr = strchr(host,':');							// find the port number, if any
    if(ptr!=NULL)
    {
        *ptr=0;
        *port = atoi(ptr+1);
    }

    free(work);
}

////////////////////////////////////////////////////////////////////////////////////////////////

int CGetWebpage::SendHTTP(LPCSTR url,LPCSTR headerReceive,BYTE *post,
        DWORD postLength,HTTPRequest *req)
{
    WSADATA			WsaData;
    SOCKADDR_IN		sin;
    SOCKET			sock;
    char			buffer[512];
    char			protocol[20],host[256],request[1024];
    int				l,port,chars,err;
    MemBuffer		headersBuffer,messageBuffer;
	char			headerSend[1024];
    BOOL			done;
    
    ParseURL(url,protocol,sizeof(protocol),host,sizeof(host),		// Parse the URL
        request,sizeof(request),&port);
    if(strcmp(protocol,"HTTP"))
        return 1;

    err = WSAStartup (0x0101, &WsaData);							// Init Winsock
    if(err!=0)
        return 1;

    sock = socket (AF_INET, SOCK_STREAM, 0);
	
	if (sock == INVALID_SOCKET)
        return 1;

    sin.sin_family = AF_INET;										//Connect to web sever
    sin.sin_port = htons( (unsigned short)port );
    sin.sin_addr.s_addr = GetHostAddress(host);

    if( connect (sock,(LPSOCKADDR)&sin, sizeof(SOCKADDR_IN) ) )
	{

        return 1;
	}

    if( !*request )
        lstrcpyn(request,"/",sizeof(request));

    if( post == NULL )
	{
        SendString(sock,"GET ");
		strcpy(headerSend, "GET ");
	}
    else 
	{
		SendString(sock,"POST ");
		strcpy(headerSend, "POST ");
	}
    SendString(sock,request);
		strcat(headerSend, request);

    SendString(sock," HTTP/1.0\r\n");
		strcat(headerSend, " HTTP/1.0\r\n");

    SendString(sock,"Accept: image/gif, image/x-xbitmap,"
        " image/jpeg, image/pjpeg, application/vnd.ms-excel,"
        " application/msword, application/vnd.ms-powerpoint,"
        " */*\r\n");
		strcat(headerSend, "Accept: image/gif, image/x-xbitmap,"
        " image/jpeg, image/pjpeg, application/vnd.ms-excel,"
        " application/msword, application/vnd.ms-powerpoint,"
        " */*\r\n");

    SendString(sock,"Accept-Language: en-us\r\n");
		strcat(headerSend, "Accept-Language: en-us\r\n");

    SendString(sock,"Accept-Encoding: gzip, deflate\r\n");
		strcat(headerSend, "Accept-Encoding: gzip, deflate\r\n");

    SendString(sock,"User-Agent: Mozilla/4.0\r\n");
		strcat(headerSend, "User-Agent: Mozilla/4.0\r\n");

    if(postLength)
    {
        sprintf(buffer,"Content-Length: %ld\r\n",postLength);
        SendString(sock,buffer);
		strcat(headerSend, buffer);
    }

    SendString(sock,"Host: ");
		strcat(headerSend, "Host: ");

    SendString(sock,host);
		strcat(headerSend, host);

    SendString(sock,"\r\n");
		strcat(headerSend, "\r\n");

    if( (headerReceive!=NULL) && *headerReceive )
	{
        SendString(sock,headerReceive);
		strcat(headerSend, headerReceive);
	}
    
    SendString(sock,"\r\n");	// Send a blank line to signal end of HTTP headerReceive
		strcat(headerSend, "\r\n");

    if( (post!=NULL) && postLength )
	{
        send(sock,(const char*)post,postLength,0);
		post[postLength]	= '\0';
		
		strcat(headerSend, (const char*)post);
	}
    
	req->headerSend		= (char*) malloc( sizeof(char*) * strlen(headerSend));
	strcpy(req->headerSend, (char*) headerSend );

    MemBufferCreate(&headersBuffer );
    chars = 0;
    done = FALSE;

    while(!done)
    {
        l = recv(sock,buffer,1,0);
        if(l<0)
            done=TRUE;

        switch(*buffer)
        {
            case '\r':
                break;
            case '\n':
                if(chars==0)
                    done = TRUE;
                chars=0;
                break;
            default:
                chars++;
                break;
        }

        MemBufferAddByte(&headersBuffer,*buffer);
    }

    req->headerReceive	= (char*) headersBuffer.buffer;
    *(headersBuffer.position) = 0;

    MemBufferCreate(&messageBuffer);				

    do
    {
        l = recv(sock,buffer,sizeof(buffer)-1,0);
        if(l<0)
            break;
        *(buffer+l)=0;
        MemBufferAddBuffer(&messageBuffer, (unsigned char*)&buffer, l);
    } while(l>0);
    *messageBuffer.position = 0;
    req->message = (char*) messageBuffer.buffer;
    req->messageLength = (messageBuffer.position - messageBuffer.buffer);

    closesocket(sock);					

    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////

string CGetWebpage::SendRequest(bool IsPost, LPCSTR url, string &psHeaderSend)
{
	HTTPRequest			req;
    int					i,rtn;
    LPSTR				buffer;

    req.headerSend							= NULL;
	req.headerReceive						= NULL;
    req.message								= NULL;

    //Read in arguments
	if(IsPost)
    {													/* POST */
		i		= psHeaderSend.length();
		buffer  = (char*) malloc(i+1);
		strcpy(buffer, psHeaderSend.c_str());

		rtn				= SendHTTP(	url,
									"Content-Type: application/x-www-form-urlencoded\r\n",
									(unsigned char*)buffer,
									i,
									&req);
        
        free(buffer);
    }
    else												/* GET */
        rtn = SendHTTP(url,NULL,NULL,0,&req);


	if(!rtn)											//Output message and/or headerSend 
	{
		psHeaderSend = req.headerSend;
		header		 = req.headerReceive;
		body		 = req.message;


		free(req.headerSend);
		free(req.headerReceive);
        free(req.message);
    }
    else
	{
		return "error";
		//std::cout << "Error connecting to database, please check your connection!" << endl;
		//Message("Webpage retrevial failed", "Failed to get the webpage: " + string(url) + "\n" + psHeaderSend);
		
	}

	return body;
}

////////////////////////////////////////////////////////////////////////////////////////////////

