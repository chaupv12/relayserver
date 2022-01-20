#ifndef _MPEG_1OR2_VIDEO_FILE_SERVER_MEDIA_SUBSESSION_HH
#define _MPEG_1OR2_VIDEO_FILE_SERVER_MEDIA_SUBSESSION_HH

#ifndef _FILE_SERVER_MEDIA_SUBSESSION_HH
#include "FileServerMediaSubsession.hh"
#endif

class MPEG1or2VideoFileServerMediaSubsession: public FileServerMediaSubsession{
public:
  static MPEG1or2VideoFileServerMediaSubsession*
  createNew(BaseEnv& env, char const* fileName, Boolean reuseFirstSource,
	    Boolean iFramesOnly = False,
	    double vshPeriod = 5.0
	    /* how often (in seconds) to inject a Video_Sequence_Header,
	       if one doesn't already appear in the stream */);

private:
  MPEG1or2VideoFileServerMediaSubsession(BaseEnv& env,
					 char const* fileName,
					 Boolean reuseFirstSource,
					 Boolean iFramesOnly,
					 double vshPeriod);
      // called only by createNew();
  virtual ~MPEG1or2VideoFileServerMediaSubsession();

private: // redefined virtual functions
  virtual FramedSource* createNewStreamSource(unsigned clientSessionId,
					      unsigned& estBitrate);
  virtual RTPSink* createNewRTPSink(Groupsock* rtpGroupsock,
                                    unsigned char rtpPayloadTypeIfDynamic,
				    FramedSource* inputSource);

private:
  Boolean fIFramesOnly;
  double fVSHPeriod;
};

#endif
