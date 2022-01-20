#ifndef _MPEG_1OR2_VIDEO_STREAM_FRAMER_HH
#define _MPEG_1OR2_VIDEO_STREAM_FRAMER_HH

#ifndef _MPEG_VIDEO_STREAM_FRAMER_HH
#include "MPEGVideoStreamFramer.hh"
#endif

class MPEG1or2VideoStreamFramer: public MPEGVideoStreamFramer {
public:
  static MPEG1or2VideoStreamFramer*
      createNew(BaseEnv& env, FramedSource* inputSource,
		Boolean iFramesOnly = False,
		double vshPeriod = 5.0
		/* how often (in seconds) to inject a Video_Sequence_Header,
		   if one doesn't already appear in the stream */);

protected:
  MPEG1or2VideoStreamFramer(BaseEnv& env,
			    FramedSource* inputSource,
			    Boolean iFramesOnly, double vshPeriod,
			    Boolean createParser = True);
      // called only by createNew(), or by subclass constructors
  virtual ~MPEG1or2VideoStreamFramer();

private:
  // redefined virtual functions:
  virtual Boolean isMPEG1or2VideoStreamFramer() const;

private:
  double getCurrentPTS() const;

  friend class MPEG1or2VideoStreamParser; // hack
};

#endif
