#ifndef _MP3_TRANSCODER_HH
#define _MP3_TRANSCODER_HH

#ifndef _MP3_ADU_HH
#include "MP3ADU.hh"
#endif
#ifndef _MP3_ADU_TRANSCODER_HH
#include "MP3ADUTranscoder.hh"
#endif

class MP3Transcoder: public MP3FromADUSource {
public:
  static MP3Transcoder* createNew(BaseEnv& env,
				  unsigned outBitrate /* in kbps */,
				  FramedSource* inputSource);

protected:
  MP3Transcoder(BaseEnv& env,
		MP3ADUTranscoder* aduTranscoder);
      // called only by createNew()
  virtual ~MP3Transcoder();
};

#endif
