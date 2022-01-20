#ifndef _AC3_AUDIO_FILE_SERVER_MEDIA_SUBSESSION_HH
#define _AC3_AUDIO_FILE_SERVER_MEDIA_SUBSESSION_HH

#ifndef _FILE_SERVER_MEDIA_SUBSESSION_HH
#include "FileServerMediaSubsession.hh"
#endif

class AC3AudioFileServerMediaSubsession : public FileServerMediaSubsession {
public:
	static AC3AudioFileServerMediaSubsession* createNew(BaseEnv& env, char const* fileName, Boolean reuseFirstSource);

private:
	AC3AudioFileServerMediaSubsession(BaseEnv& env, char const* fileName, Boolean reuseFirstSource);
	virtual ~AC3AudioFileServerMediaSubsession();

private:
	virtual FramedSource* createNewStreamSource(unsigned clientSessionId, unsigned& estBitrate);
	virtual RTPSink* createNewRTPSink(Groupsock* rtpGroupsock, unsigned char rtpPayloadTypeIfDynamic, FramedSource* inputSource);
};

#endif
