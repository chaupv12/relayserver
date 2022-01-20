#ifndef _AMR_AUDIO_FILE_SERVER_MEDIA_SUBSESSION_HH
#define _AMR_AUDIO_FILE_SERVER_MEDIA_SUBSESSION_HH

#ifndef _FILE_SERVER_MEDIA_SUBSESSION_HH
#include "FileServerMediaSubsession.hh"
#endif

class AMRAudioFileServerMediaSubsession: public FileServerMediaSubsession{
public:
  static AMRAudioFileServerMediaSubsession*
  createNew(BaseEnv& env, char const* fileName, Boolean reuseFirstSource);

private:
  AMRAudioFileServerMediaSubsession(BaseEnv& env,
				      char const* fileName, Boolean reuseFirstSource);
      // called only by createNew();
  virtual ~AMRAudioFileServerMediaSubsession();

private: // redefined virtual functions
  virtual FramedSource* createNewStreamSource(unsigned clientSessionId,
					      unsigned& estBitrate);
  virtual RTPSink* createNewRTPSink(Groupsock* rtpGroupsock,
                                    unsigned char rtpPayloadTypeIfDynamic,
				    FramedSource* inputSource);
};

#endif
