#ifndef _H264_VIDEO_STREAM_DISCRETE_FRAMER_HH
#define _H264_VIDEO_STREAM_DISCRETE_FRAMER_HH

#ifndef _H264_OR_5_VIDEO_STREAM_DISCRETE_FRAMER_HH
#include "H264or5VideoStreamDiscreteFramer.hh"
#endif

class H264VideoStreamDiscreteFramer: public H264or5VideoStreamDiscreteFramer {
public:
  static H264VideoStreamDiscreteFramer*
  createNew(BaseEnv& env, FramedSource* inputSource,
	    Boolean includeStartCodeInOutput = False, Boolean insertAccessUnitDelimiters = False);

protected:
  H264VideoStreamDiscreteFramer(BaseEnv& env, FramedSource* inputSource,
				Boolean includeStartCodeInOutput, Boolean insertAccessUnitDelimiters);
      // called only by createNew()
  virtual ~H264VideoStreamDiscreteFramer();

private:
  // redefined virtual functions:
  virtual Boolean isH264VideoStreamFramer() const;
};

#endif
