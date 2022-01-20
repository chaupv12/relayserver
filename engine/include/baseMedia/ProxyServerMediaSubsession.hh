#include "liveMedia.hh"
#include "RTSPCommon.hh"
#include "GroupsockHelper.hh" 

class ProxyServerMediaSubsession : public OnDemandServerMediaSubsession {
public:
	ProxyServerMediaSubsession(MediaSubsession& mediaSubsession, portNumBits initialPortNum, Boolean multiplexRTCPWithRTP);
	virtual ~ProxyServerMediaSubsession();

	char const* codecName() const { return fCodecName; }
	char const* url() const { return ((ProxyServerMediaSession*)fParentSession)->url(); }

private: // redefined virtual functions
	virtual FramedSource* createNewStreamSource(unsigned clientSessionId, unsigned& estBitrate);
	virtual void closeStreamSource(FramedSource* inputSource);
	virtual RTPSink* createNewRTPSink(Groupsock* rtpGroupsock, unsigned char rtpPayloadTypeIfDynamic, FramedSource* inputSource);
	virtual Groupsock* createGroupsock(struct sockaddr_storage const& addr, Port port);
	virtual RTCPInstance* createRTCP(Groupsock* RTCPgs, unsigned totSessionBW, /* in kbps */ unsigned char const* cname, RTPSink* sink);

private:
	static void subsessionByeHandler(void* clientData);
	void subsessionByeHandler();

	int verbosityLevel() const { return ((ProxyServerMediaSession*)fParentSession)->fVerbosityLevel; }

private:
	friend class ProxyRTSPClient;
	MediaSubsession& fClientMediaSubsession; // the 'client' media subsession object that corresponds to this 'server' media subsession
	char const* fCodecName;  // copied from "fClientMediaSubsession" once it's been set up
	ProxyServerMediaSubsession* fNext; // used when we're part of a queue
	Boolean fHaveSetupStream;
};