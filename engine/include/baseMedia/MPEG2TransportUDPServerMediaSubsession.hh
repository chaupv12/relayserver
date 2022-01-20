#ifndef _MPEG2_TRANSPORT_UDP_SERVER_MEDIA_SUBSESSION_HH
#define _MPEG2_TRANSPORT_UDP_SERVER_MEDIA_SUBSESSION_HH

#ifndef _ON_DEMAND_SERVER_MEDIA_SUBSESSION_HH
#include "OnDemandServerMediaSubsession.hh"
#endif

class MPEG2TransportUDPServerMediaSubsession: public OnDemandServerMediaSubsession {
public:
  static MPEG2TransportUDPServerMediaSubsession*
  createNew(BaseEnv& env,
	    char const* inputAddressStr, // An IP multicast address, or use "0.0.0.0" or NULL for unicast input
	    Port const& inputPort,
	    Boolean inputStreamIsRawUDP = False); // otherwise (default) the input stream is RTP/UDP
protected:
  MPEG2TransportUDPServerMediaSubsession(BaseEnv& env,
					 char const* inputAddressStr, Port const& inputPort, Boolean inputStreamIsRawUDP);
      // called only by createNew();
  virtual ~MPEG2TransportUDPServerMediaSubsession();

protected: // redefined virtual functions
  virtual FramedSource* createNewStreamSource(unsigned clientSessionId,
					      unsigned& estBitrate);
  virtual RTPSink* createNewRTPSink(Groupsock* rtpGroupsock,
				    unsigned char rtpPayloadTypeIfDynamic,
				    FramedSource* inputSource);
protected:
  char const* fInputAddressStr;
  Port fInputPort;
  Groupsock* fInputGroupsock;
  Boolean fInputStreamIsRawUDP;
};

#endif
