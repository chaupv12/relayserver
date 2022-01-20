#ifndef _ADTS_AUDIO_FILE_SOURCE_HH
#define _ADTS_AUDIO_FILE_SOURCE_HH

#ifndef _FRAMED_FILE_SOURCE_HH
#include "FramedFileSource.hh"
#endif

class ADTSAudioFileSource : public FramedFileSource {
public:
	static ADTSAudioFileSource* createNew(BaseEnv& env,
		char const* fileName);

	unsigned samplingFrequency() const { return fSamplingFrequency; }
	unsigned numChannels() const { return fNumChannels; }
	char const* configStr() const { return fConfigStr; }
	// returns the 'AudioSpecificConfig' for this stream (in ASCII form)

private:
	ADTSAudioFileSource(BaseEnv& env, FILE* fid, u_int8_t profile,
		u_int8_t samplingFrequencyIndex, u_int8_t channelConfiguration);
	// called only by createNew()

	virtual ~ADTSAudioFileSource();

private:
	// redefined virtual functions:
	virtual void doGetNextFrame();

private:
	unsigned fSamplingFrequency;
	unsigned fNumChannels;
	unsigned fuSecsPerFrame;
	char fConfigStr[5];
};

#endif
