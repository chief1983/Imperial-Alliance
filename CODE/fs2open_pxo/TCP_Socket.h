// TCP_Socket.h
// TCP_Socket for FS2Open PXO
// Derek Meek
// 2-14-2003

// ############## ATTENTION ##########
// Licensed under the Academic Free License version 2.0
// View License at http://www.opensource.org/licenses/afl-2.0.php
// ###################################


/*
 * $Logfile: /Freespace2/code/fs2open_pxo/TCP_Socket.h $
 * $Revision: 1.1.1.1 $
 * $Date: 2004/08/13 22:47:40 $
 * $Author: Spearhawk $
 *
 *
 * $Log: TCP_Socket.h,v $
 * Revision 1.1.1.1  2004/08/13 22:47:40  Spearhawk
 * no message
 *
 * Revision 1.1.1.1  2004/08/13 20:44:54  Darkhill
 * no message
 *
 * Revision 1.6  2004/03/31 05:42:26  Goober5000
 * got rid of all those nasty warnings from xlocale and so forth; also added comments
 * for #pragma warning disable to indicate the message being disabled
 * --Goober5000
 *
 * Revision 1.5  2004/03/09 17:59:01  Kazan
 * Disabled multithreaded TCP_Socket in favor of safer single threaded
 * FS2NetD doesn't kill the game on connection failure now - just gives warning message and effectively dsiables itself until they try to connect again
 *
 * Revision 1.4  2004/02/21 00:59:43  Kazan
 * FS2NETD License Comments
 *
 * Revision 1.3  2003/10/13 06:02:50  Kazan
 * Added Log Comment Thingy to these files
 *
 *
 *
 */

// Enable Multithread
//#define MT_TCP_Socket

// Enable MultiThreaded Receive - FreeSpace 2 TCP_Socket only!
//#define FS2_TCP_RMultithread

#if defined(WIN32)
// Windows Version
#include <windows.h>
#include <process.h>

#pragma warning(push, 2)	// ignore all those warnings for Microsoft stuff
#include <string>
#pragma warning(pop)

//#include <winsock2.h>

#if !defined(STYPE)
#define STYPE SOCKET
#endif



#if !defined(CLOSEFUNC)
#define CLOSEFUNC closesocket
#endif

#else
// Unix Version
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>

#if !defined(STYPE)
#define STYPE int
#endif

#if !defined(CLOSEFUNC)
#define CLOSEFUNC close
#endif


#endif


#if !defined(__TCP_SOCKET_H_)
#define __TCP_SOCKET_H_

// From UDP_Socket
int startWinsock();


class Generic_Socket
{
	protected:

		bool Initialized;
		STYPE mySocket;
		int port;

	public:
		Generic_Socket() : Initialized(false), port(0) {}
		
		bool isInitialized() { return Initialized; }
		void Close() { CLOSEFUNC(mySocket); Initialized = false; }
		void SetPort(int aport) { port = aport; } 

		// purely virtual
		virtual bool InitSocket()=0;
};




#if defined(WIN32) && defined(MT_TCP_Socket)
typedef void (__cdecl *sproc)(STYPE);
#endif

#define TCP_SOCKET_TIMEOUT 15000

#if defined(FS2_TCP_RMultithread)
#define FS2_TCP_MaxWaiting 20
#define FS2_TCP_ReceiveBuffer 16384


#endif
class TCP_Socket : public Generic_Socket
{
	private:
		bool ServerMode;
#if defined(FS2_TCP_RMultithread)
		int QueueLen;
		char ReceiveBuffer[FS2_TCP_MaxWaiting][FS2_TCP_ReceiveBuffer];
		int	ReceiveLen[FS2_TCP_MaxWaiting];

		bool Lock;
		bool MtDie;
#endif

#if defined(WIN32) && defined(MT_TCP_Socket)
		// used for servers in windows
		STYPE nServerSocket;
		sproc nServProc;
#endif

	public:
		TCP_Socket(int aport = 0, bool WillbeServer = false) : ServerMode(WillbeServer), Generic_Socket() { port = aport; }
		~TCP_Socket() 
			{ 

#if defined(FS2_TCP_RMultithread)
				MtDie = true; 
#endif
				Close(); 
			}
		void MakeFromSocket(STYPE nSocket) { mySocket = nSocket; Initialized = true; }


		// if "WillbeServer" wasn't set on construction SetServerMode() MUST be called BEFORE InitSocket() for this to be a server
		void SetServerMode() { ServerMode = true; };

		// arguments are ignored if we're in ServerMode
		bool InitSocket(void) { return TCP_Socket::InitSocket("", 0);}

		bool InitSocket(std::string rem_host, int rem_port);

#if defined(FS2_TCP_RMultithread)

		void IgnorePackets() { ClearData(); QueueLen = 0; }
		bool MT_DataReady() { return (QueueLen > 0); }
		
		void ClearData() { memset(ReceiveBuffer, 0, FS2_TCP_MaxWaiting * FS2_TCP_ReceiveBuffer); }
		int GetDataFromNetwork();
		void RemoveFirstPacket();

		friend void _cdecl tcp_socket_mt_run(void *arg);
#else
		void IgnorePackets();
#endif
	

		STYPE GetSocketNum() { return mySocket; }; 



		bool DataReady();
		bool OOBDataReady();


		int GetData(char *buffer, int blen, bool OOB=false);
		int SendData(char *buffer, int msg_len, bool OOB=false);

		//server calls

#if defined(MT_TCP_Socket)
		// AcceptConnections will accept a connection and spawn a new server process 
		// the argument is a function pointer

		bool AcceptConnections(sproc server_process);
#endif
		STYPE AcceptConnections();

#if defined(WIN32) && defined(MT_TCP_Socket)
		// used for servers in windows
		friend void __cdecl StartServerProc(void *arg);
#endif
	};

	//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

#endif