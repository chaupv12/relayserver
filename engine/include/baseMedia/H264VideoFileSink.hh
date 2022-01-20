#include "liveDef.hh"
#ifndef _H264_VIDEO_FILE_SINK_HH
#define _H264_VIDEO_FILE_SINK_HH

#ifndef _H264_OR_5_VIDEO_FILE_SINK_HH
#include "H264or5VideoFileSink.hh"
#endif

class H264VideoFileSink : public H264or5VideoFileSink {
public:
	static H264VideoFileSink* createNew(BaseEnv& env, char const* fileName,
		char const* sPropParameterSetsStr = NULL,
		// "sPropParameterSetsStr" is an optional 'SDP format' string
		// (comma-separated Base64-encoded) representing SPS and/or PPS NAL-units
		// to prepend to the output
		unsigned bufferSize = MAX_BUFFER_SIZE /*100000*/,
		Boolean oneFilePerFrame = False);
	// See "FileSink.hh" for a description of these parameters.

protected:
	H264VideoFileSink(BaseEnv& env, FILE* fid,
		char const* sPropParameterSetsStr,
		unsigned bufferSize, char const* perFrameFileNamePrefix);
	// called only by createNew()
	virtual ~H264VideoFileSink();
};

#endif
