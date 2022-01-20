#ifndef _WAV_AUDIO_FILE_SOURCE_HH
#define _WAV_AUDIO_FILE_SOURCE_HH

#ifndef _AUDIO_INPUT_DEVICE_HH
#include "AudioInputDevice.hh"
#endif

typedef enum {
	WA_PCM = 0x01,
	WA_PCMA = 0x06,
	WA_PCMU = 0x07,
	WA_IMA_ADPCM = 0x11,
	WA_UNKNOWN
} WAV_AUDIO_FORMAT;


class WAVAudioFileSource : public AudioInputDevice {
public:

	static WAVAudioFileSource* createNew(BaseEnv& env,
		char const* fileName);

	unsigned numPCMBytes() const;
	void setScaleFactor(int scale);
	void seekToPCMByte(unsigned byteNumber);
	void limitNumBytesToStream(unsigned numBytesToStream);
	// if "numBytesToStream" is >0, then we limit the stream to that number of bytes, before treating it as EOF

	unsigned char getAudioFormat();

protected:
	WAVAudioFileSource(BaseEnv& env, FILE* fid);
	// called only by createNew()

	virtual ~WAVAudioFileSource();

	static void fileReadableHandler(WAVAudioFileSource* source, int mask);
	void doReadFromFile();

private:
	// redefined virtual functions:
	virtual void doGetNextFrame();
	virtual void doStopGettingFrames();
	virtual Boolean setInputPort(int portIndex);
	virtual double getAverageLevel() const;

protected:
	unsigned fPreferredFrameSize;

private:
	FILE* fFid;
	double fPlayTimePerSample; // useconds
	Boolean fFidIsSeekable;
	unsigned fLastPlayTime; // useconds
	Boolean fHaveStartedReading;
	unsigned fWAVHeaderSize;
	unsigned fFileSize;
	int fScaleFactor;
	Boolean fLimitNumBytesToStream;
	unsigned fNumBytesToStream; // used iff "fLimitNumBytesToStream" is True
	unsigned char fAudioFormat;
};

#endif
