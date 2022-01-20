#ifndef _MP3_AUDIO_FILE_SERVER_MEDIA_SUBSESSION_HH
#define _MP3_AUDIO_FILE_SERVER_MEDIA_SUBSESSION_HH

#ifndef _FILE_SERVER_MEDIA_SUBSESSION_HH
#include "FileServerMediaSubsession.hh"
#endif
#ifndef _MP3_ADU_INTERLEAVING_HH
#include "MP3ADUinterleaving.hh"
#endif
#ifndef _MP3_ADU_HH
#include "MP3ADU.hh"
#endif

class MP3AudioFileServerMediaSubsession: public FileServerMediaSubsession{
public:
  static MP3AudioFileServerMediaSubsession*
  createNew(BaseEnv& env, char const* fileName, Boolean reuseFirstSource,
	    Boolean generateADUs, Interleaving* interleaving);
      // Note: "interleaving" is used only if "generateADUs" is True,
      // (and a value of NULL means 'no interleaving')

protected:
  MP3AudioFileServerMediaSubsession(BaseEnv& env,
				    char const* fileName, Boolean reuseFirstSource,
				    Boolean generateADUs,
				    Interleaving* interleaving);
      // called only by createNew();
  virtual ~MP3AudioFileServerMediaSubsession();

  FramedSource* createNewStreamSourceCommon(FramedSource* baseMP3Source, unsigned mp3NumBytes, unsigned& estBitrate);
  void getBaseStreams(FramedSource* frontStream,
		      FramedSource*& sourceMP3Stream, ADUFromMP3Source*& aduStream/*if any*/);

protected: // redefined virtual functions
  virtual void seekStreamSource(FramedSource* inputSource, double& seekNPT, double streamDuration, u_int64_t& numBytes);
  virtual void setStreamSourceScale(FramedSource* inputSource, float scale);
  virtual FramedSource* createNewStreamSource(unsigned clientSessionId,
					      unsigned& estBitrate);
  virtual RTPSink* createNewRTPSink(Groupsock* rtpGroupsock,
                                    unsigned char rtpPayloadTypeIfDynamic,
				    FramedSource* inputSource);
  virtual void testScaleFactor(float& scale);
  virtual float duration() const;

protected:
  Boolean fGenerateADUs;
  Interleaving* fInterleaving;
  float fFileDuration;
};

#endif
