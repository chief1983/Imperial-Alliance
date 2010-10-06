#ifndef _WEBGET_H_
#define _WEBGET_H_


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <string>

 
#define MEM_BUFFER_SIZE 10


typedef struct
{ 
    LPSTR headerSend;
	LPSTR headerReceive;		
    LPSTR message;					
    long messageLength;	
} HTTPRequest;

typedef struct
{
    unsigned	char *buffer;
    unsigned	char *position;
    size_t		size;
} MemBuffer;



class CGetWebpage
{
public:
	
	CGetWebpage() {}
	~CGetWebpage() {}

	std::string SendRequest(bool isPost, LPCSTR url, std::string &psHeaderSend);
	
	std::string GetPage()   { return body; }
	std::string GetHeader() { return header; }

private:
	void  MemBufferCreate(MemBuffer *b);
	void  MemBufferGrow(MemBuffer *b);
	void  MemBufferAddByte(MemBuffer *b, unsigned char byt);
	void  MemBufferAddBuffer(MemBuffer *b, unsigned char *buffer, size_t size);
	DWORD GetHostAddress(LPCSTR host);
	void  SendString(SOCKET sock,LPCSTR str);
	BOOL  ValidHostChar(char ch);
	void  ParseURL(LPCSTR url,LPSTR protocol,int lprotocol, LPSTR host,int lhost,LPSTR request,int lrequest,int *port);
	int	  SendHTTP(LPCSTR url,LPCSTR headers,BYTE *post, DWORD postLength,HTTPRequest *req);

	std::string body;
	std::string header;
};


#endif
