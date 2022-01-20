#ifndef _H264_VIDEO_STREAM_FRAMER_HH
#define _H264_VIDEO_STREAM_FRAMER_HH

#ifndef _H264_OR_5_VIDEO_STREAM_FRAMER_HH
#include "H264or5VideoStreamFramer.hh"
#endif

class H264VideoStreamFramer: public H264or5VideoStreamFramer {
public:
  static H264VideoStreamFramer* createNew(BaseEnv& env, FramedSource* inputSource,
					  Boolean includeStartCodeInOutput = False,
					  Boolean insertAccessUnitDelimiters = False);

protected:
  H264VideoStreamFramer(BaseEnv& env, FramedSource* inputSource,
			Boolean createParser,
			Boolean includeStartCodeInOutput, Boolean insertAccessUnitDelimiters);
      // called only by "createNew()"
  virtual ~H264VideoStreamFramer();

  // redefined virtual functions:
  virtual Boolean isH264VideoStreamFramer() const;
};

#endif
