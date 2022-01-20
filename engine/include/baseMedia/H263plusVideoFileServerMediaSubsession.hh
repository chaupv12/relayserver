#ifndef _H263PLUS_VIDEO_FILE_SERVER_MEDIA_SUBSESSION_HH
#define _H263PLUS_VIDEO_FILE_SERVER_MEDIA_SUBSESSION_HH

#ifndef _FILE_SERVER_MEDIA_SUBSESSION_HH
#include "FileServerMediaSubsession.hh"
#endif

class H263plusVideoFileServerMediaSubsession: public FileServerMediaSubsession{
public:
  static H263plusVideoFileServerMediaSubsession*
  createNew(BaseEnv& env, char const* fileName, Boolean reuseFirstSource);

private:
  H263plusVideoFileServerMediaSubsession(BaseEnv& env,
					 char const* fileName, Boolean reuseFirstSource);
      // called only by createNew();
  virtual ~H263plusVideoFileServerMediaSubsession();

private: // redefined virtual functions
  virtual FramedSource* createNewStreamSource(unsigned clientSessionId,
					      unsigned& estBitrate);
  virtual RTPSink* createNewRTPSink(Groupsock* rtpGroupsock,
                                    unsigned char rtpPayloadTypeIfDynamic,
				                    FramedSource* inputSource);
};

#endif
