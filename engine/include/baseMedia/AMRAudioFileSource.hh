#ifndef _AMR_AUDIO_FILE_SOURCE_HH
#define _AMR_AUDIO_FILE_SOURCE_HH

#ifndef _AMR_AUDIO_SOURCE_HH
#include "AMRAudioSource.hh"
#endif

class AMRAudioFileSource: public AMRAudioSource {
public:
  static AMRAudioFileSource* createNew(BaseEnv& env,
				       char const* fileName);

private:
  AMRAudioFileSource(BaseEnv& env, FILE* fid,
		     Boolean isWideband, unsigned numChannels);
	// called only by createNew()

  virtual ~AMRAudioFileSource();

private:
  // redefined virtual functions:
  virtual void doGetNextFrame();

private:
  FILE* fFid;
};

#endif
