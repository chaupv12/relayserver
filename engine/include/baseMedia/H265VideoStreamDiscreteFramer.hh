#ifndef _H265_VIDEO_STREAM_DISCRETE_FRAMER_HH
#define _H265_VIDEO_STREAM_DISCRETE_FRAMER_HH

#ifndef _H264_OR_5_VIDEO_STREAM_DISCRETE_FRAMER_HH
#include "H264or5VideoStreamDiscreteFramer.hh"
#endif

class H265VideoStreamDiscreteFramer: public H264or5VideoStreamDiscreteFramer {
public:
  static H265VideoStreamDiscreteFramer*
  createNew(BaseEnv& env, FramedSource* inputSource,
	    Boolean includeStartCodeInOutput = False, Boolean insertAccessUnitDelimiters = False);

protected:
  H265VideoStreamDiscreteFramer(BaseEnv& env, FramedSource* inputSource,
				Boolean includeStartCodeInOutput, Boolean insertAccessUnitDelimiters);
      // called only by createNew()
  virtual ~H265VideoStreamDiscreteFramer();

private:
  // redefined virtual functions:
  virtual Boolean isH265VideoStreamFramer() const;
};

#endif
