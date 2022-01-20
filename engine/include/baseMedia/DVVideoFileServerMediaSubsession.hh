#ifndef _DV_VIDEO_FILE_SERVER_MEDIA_SUBSESSION_HH
#define _DV_VIDEO_FILE_SERVER_MEDIA_SUBSESSION_HH

#ifndef _FILE_SERVER_MEDIA_SUBSESSION_HH
#include "FileServerMediaSubsession.hh"
#endif

class DVVideoFileServerMediaSubsession: public FileServerMediaSubsession{
public:
  static DVVideoFileServerMediaSubsession*
  createNew(BaseEnv& env, char const* fileName, Boolean reuseFirstSource);

private:
  DVVideoFileServerMediaSubsession(BaseEnv& env, char const* fileName, Boolean reuseFirstSource);
      // called only by createNew();
  virtual ~DVVideoFileServerMediaSubsession();

private: // redefined virtual functions
  virtual char const* getAuxSDPLine(RTPSink* rtpSink, FramedSource* inputSource);
  virtual void seekStreamSource(FramedSource* inputSource, double& seekNPT, double streamDuration, u_int64_t& numBytes);
  virtual void setStreamSourceDuration(FramedSource* inputSource, double streamDuration, u_int64_t& numBytes);
  virtual FramedSource* createNewStreamSource(unsigned clientSessionId, unsigned& estBitrate);
  virtual RTPSink* createNewRTPSink(Groupsock* rtpGroupsock, unsigned char rtpPayloadTypeIfDynamic, FramedSource* inputSource);
  virtual float duration() const;

private:
  float fFileDuration; // in seconds
};

#endif
