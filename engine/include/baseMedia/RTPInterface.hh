#ifndef _RTP_INTERFACE_HH
#define _RTP_INTERFACE_HH

#ifndef _MEDIA_HH
#include <Media.hh>
#endif
#ifndef _GROUPSOCK_HH
#include "Groupsock.hh"
#endif

// Typedef for an optional auxilliary handler function, to be called
// when each new packet is read:
typedef void AuxHandlerFunc(void* clientData, unsigned char* packet, unsigned& packetSize);

typedef void ServerRequestAlternativeByteHandler(void* instance, u_int8_t requestByte);
// A hack that allows a handler for RTP/RTCP packets received over TCP to process RTSP commands that may also appear within
// the same TCP connection.  A RTSP server implementation would supply a function like this - as a parameter to
// "ServerMediaSubsession::startStream()".

class RTPInterface {
public:
	RTPInterface(Medium* owner, Groupsock* gs);
	virtual ~RTPInterface();

	Groupsock* gs() const { return fGS; }

	void setStreamSocket(int sockNum, unsigned char streamChannelId);
	void addStreamSocket(int sockNum, unsigned char streamChannelId);
	void removeStreamSocket(int sockNum, unsigned char streamChannelId);
	static void setServerRequestAlternativeByteHandler(BaseEnv& env, int socketNum, ServerRequestAlternativeByteHandler* handler, void* clientData);
	static void clearServerRequestAlternativeByteHandler(BaseEnv& env, int socketNum);

	Boolean sendPacket(unsigned char* packet, unsigned packetSize);
	void startNetworkReading(TaskScheduler::BackgroundHandlerProc* handlerProc);
	Boolean handleRead(unsigned char* buffer, unsigned bufferMaxSize,
		// out parameters:
		unsigned& bytesRead, struct sockaddr_storage& fromAddress, int& tcpSocketNum, unsigned char& tcpStreamChannelId, Boolean& packetReadWasIncomplete);
	// Note: If "tcpSocketNum" < 0, then the packet was received over UDP, and "tcpStreamChannelId"
	//   is undefined (and irrelevant).


	// Otherwise (if "tcpSocketNum" >= 0), the packet was received (interleaved) over TCP, and
	//   "tcpStreamChannelId" will return the channel id.

	void stopNetworkReading();

	BaseEnv& envir() const { return fOwner->envir(); }

	void setAuxilliaryReadHandler(AuxHandlerFunc* handlerFunc,
		void* handlerClientData) {
		fAuxReadHandlerFunc = handlerFunc;
		fAuxReadHandlerClientData = handlerClientData;
	}

	void forgetOurGroupsock() { fGS = NULL; }
	// This may be called - *only immediately prior* to deleting this - to prevent our destructor
	// from turning off background reading on the 'groupsock'.  (This is in case the 'groupsock'
	// is also being read from elsewhere.)

private:
	// Helper functions for sending a RTP or RTCP packet over a TCP connection:
	Boolean sendRTPorRTCPPacketOverTCP(unsigned char* packet, unsigned packetSize, int socketNum, unsigned char streamChannelId);
	Boolean sendDataOverTCP(int socketNum, u_int8_t const* data, unsigned dataSize, Boolean forceSendToSucceed);

private:
	friend class SocketDescriptor;
	Medium* fOwner;
	Groupsock* fGS;
	class tcpStreamRecord* fTCPStreams; // optional, for RTP-over-TCP streaming/receiving

	unsigned short fNextTCPReadSize;
	// how much data (if any) is available to be read from the TCP stream
	int fNextTCPReadStreamSocketNum;
	unsigned char fNextTCPReadStreamChannelId;
	TaskScheduler::BackgroundHandlerProc* fReadHandlerProc; // if any

	AuxHandlerFunc* fAuxReadHandlerFunc;
	void* fAuxReadHandlerClientData;
};

#endif
