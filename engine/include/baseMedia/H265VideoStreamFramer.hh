#ifndef _H265_VIDEO_STREAM_FRAMER_HH
#define _H265_VIDEO_STREAM_FRAMER_HH

#ifndef _H264_OR_5_VIDEO_STREAM_FRAMER_HH
#include "H264or5VideoStreamFramer.hh"
#endif

class H265VideoStreamFramer : public H264or5VideoStreamFramer {
public:
	static H265VideoStreamFramer* createNew(BaseEnv& env, FramedSource* inputSource,
		Boolean includeStartCodeInOutput = False,
		Boolean insertAccessUnitDelimiters = False);

protected:
	H265VideoStreamFramer(BaseEnv& env, FramedSource* inputSource,
		Boolean createParser,
		Boolean includeStartCodeInOutput, Boolean insertAccessUnitDelimiters);
	// called only by "createNew()"
	virtual ~H265VideoStreamFramer();

	// redefined virtual functions:
	virtual Boolean isH265VideoStreamFramer() const;
};

#endif
