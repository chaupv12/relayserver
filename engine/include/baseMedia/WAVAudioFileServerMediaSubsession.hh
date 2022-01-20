#ifndef _WAV_AUDIO_FILE_SERVER_MEDIA_SUBSESSION_HH
#define _WAV_AUDIO_FILE_SERVER_MEDIA_SUBSESSION_HH

#ifndef _FILE_SERVER_MEDIA_SUBSESSION_HH
#include "FileServerMediaSubsession.hh"
#endif

class WAVAudioFileServerMediaSubsession : public FileServerMediaSubsession {
public:
	static WAVAudioFileServerMediaSubsession*
		createNew(BaseEnv& env, char const* fileName, Boolean reuseFirstSource,
			Boolean convertToULaw = False);
	// If "convertToULaw" is True, 16-bit audio streams are converted to
	// 8-bit u-law audio prior to streaming.

protected:
	WAVAudioFileServerMediaSubsession(BaseEnv& env, char const* fileName,
		Boolean reuseFirstSource, Boolean convertToULaw);
	// called only by createNew();
	virtual ~WAVAudioFileServerMediaSubsession();

protected: // redefined virtual functions
	virtual void seekStreamSource(FramedSource* inputSource, double& seekNPT, double streamDuration, u_int64_t& numBytes);
	virtual void setStreamSourceScale(FramedSource* inputSource, float scale);
	virtual void setStreamSourceDuration(FramedSource* inputSource, double streamDuration, u_int64_t& numBytes);

	virtual FramedSource* createNewStreamSource(unsigned clientSessionId,
		unsigned& estBitrate);
	virtual RTPSink* createNewRTPSink(Groupsock* rtpGroupsock,
		unsigned char rtpPayloadTypeIfDynamic,
		FramedSource* inputSource);
	virtual void testScaleFactor(float& scale);
	virtual float duration() const;

protected:
	Boolean fConvertToULaw;

	// The following parameters of the input stream are set after
	// "createNewStreamSource" is called:
	unsigned char fAudioFormat;
	unsigned char fBitsPerSample;
	unsigned fSamplingFrequency;
	unsigned fNumChannels;
	float fFileDuration;
};

#endif
