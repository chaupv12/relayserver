#ifndef _MPEG_1OR2_DEMUXED_SERVER_MEDIA_SUBSESSION_HH
#define _MPEG_1OR2_DEMUXED_SERVER_MEDIA_SUBSESSION_HH

#ifndef _ON_DEMAND_SERVER_MEDIA_SUBSESSION_HH
#include "OnDemandServerMediaSubsession.hh"
#endif
#ifndef _MPEG_1OR2_FILE_SERVER_DEMUX_HH
#include "MPEG1or2FileServerDemux.hh"
#endif

class MPEG1or2DemuxedServerMediaSubsession: public OnDemandServerMediaSubsession{
public:
  static MPEG1or2DemuxedServerMediaSubsession*
  createNew(MPEG1or2FileServerDemux& demux, u_int8_t streamIdTag,
	    Boolean reuseFirstSource,
	    Boolean iFramesOnly = False, double vshPeriod = 5.0);
  // The last two parameters are relevant for video streams only

private:
  MPEG1or2DemuxedServerMediaSubsession(MPEG1or2FileServerDemux& demux,
				       u_int8_t streamIdTag, Boolean reuseFirstSource,
				       Boolean iFramesOnly, double vshPeriod);
      // called only by createNew();
  virtual ~MPEG1or2DemuxedServerMediaSubsession();

private: // redefined virtual functions
  virtual void seekStreamSource(FramedSource* inputSource, double& seekNPT, double streamDuration, u_int64_t& numBytes);
  virtual FramedSource* createNewStreamSource(unsigned clientSessionId,
					      unsigned& estBitrate);
  virtual RTPSink* createNewRTPSink(Groupsock* rtpGroupsock,
                                    unsigned char rtpPayloadTypeIfDynamic,
				    FramedSource* inputSource);
  virtual float duration() const;

private:
  MPEG1or2FileServerDemux& fOurDemux;
  u_int8_t fStreamIdTag;
  Boolean fIFramesOnly; // for video streams
  double fVSHPeriod; // for video streams
};

#endif
