#ifndef _PASSIVE_SERVER_MEDIA_SUBSESSION_HH
#define _PASSIVE_SERVER_MEDIA_SUBSESSION_HH

#ifndef _SERVER_MEDIA_SESSION_HH
#include "ServerMediaSession.hh"
#endif

#ifndef _RTP_SINK_HH
#include "RTPSink.hh"
#endif
#ifndef _RTCP_HH
#include "RTCP.hh"
#endif

class PassiveServerMediaSubsession : public ServerMediaSubsession {
public:
	static PassiveServerMediaSubsession* createNew(RTPSink& rtpSink,
		RTCPInstance* rtcpInstance = NULL);

protected:
	PassiveServerMediaSubsession(RTPSink& rtpSink, RTCPInstance* rtcpInstance);
	// called only by createNew();
	virtual ~PassiveServerMediaSubsession();

	virtual Boolean rtcpIsMuxed();

protected: // redefined virtual functions
	virtual char const* sdpLines(int addressFamily);
	virtual void getStreamParameters(unsigned clientSessionId,
		struct sockaddr_storage const& clientAddress,
		Port const& clientRTPPort,
		Port const& clientRTCPPort,
		int tcpSocketNum,
		unsigned char rtpChannelId,
		unsigned char rtcpChannelId,
		struct sockaddr_storage& destinationAddress,
		u_int8_t& destinationTTL,
		Boolean& isMulticast,
		Port& serverRTPPort,
		Port& serverRTCPPort,
		void*& streamToken);
	virtual void startStream(unsigned clientSessionId, void* streamToken,
		TaskFunc* rtcpRRHandler,
		void* rtcpRRHandlerClientData,
		unsigned short& rtpSeqNum,
		unsigned& rtpTimestamp,
		ServerRequestAlternativeByteHandler* serverRequestAlternativeByteHandler,
		void* serverRequestAlternativeByteHandlerClientData);
	virtual float getCurrentNPT(void* streamToken);
	virtual void getRTPSinkandRTCP(void* streamToken,
		RTPSink const*& rtpSink, RTCPInstance const*& rtcp);
	virtual void deleteStream(unsigned clientSessionId, void*& streamToken);

protected:
	char* fSDPLines;
	RTPSink& fRTPSink;
	RTCPInstance* fRTCPInstance;
	HashTable* fClientRTCPSourceRecords; // indexed by client session id; used to implement RTCP "RR" handling
};

#endif
