#ifndef _AUDIO_INPUT_DEVICE_HH
#define _AUDIO_INPUT_DEVICE_HH

#ifndef _FRAMED_SOURCE_HH
#include "FramedSource.hh"
#endif

class AudioPortNames {
public:
  AudioPortNames();
  virtual ~AudioPortNames();

  unsigned numPorts;
  char** portName;
};

class AudioInputDevice: public FramedSource {
public:
  unsigned char bitsPerSample() const { return fBitsPerSample; }
  unsigned char numChannels() const { return fNumChannels; }
  unsigned samplingFrequency() const { return fSamplingFrequency; }

  virtual Boolean setInputPort(int portIndex) = 0;
  virtual double getAverageLevel() const = 0;

  static AudioInputDevice*
  createNew(BaseEnv& env, int inputPortNumber,
	    unsigned char bitsPerSample, unsigned char numChannels,
	    unsigned samplingFrequency, unsigned granularityInMS = 20);
  static AudioPortNames* getPortNames();

  static char** allowedDeviceNames;
  // If this is set to non-NULL, then it's a NULL-terminated array of strings
  // of device names that we are allowed to access.

protected:
  AudioInputDevice(BaseEnv& env,
		   unsigned char bitsPerSample,
		   unsigned char numChannels,
		   unsigned samplingFrequency,
		   unsigned granularityInMS);
	// we're an abstract base class

  virtual ~AudioInputDevice();

protected:
  unsigned char fBitsPerSample, fNumChannels;
  unsigned fSamplingFrequency;
  unsigned fGranularityInMS;
};

#endif
