#ifndef _H265_VIDEO_FILE_SINK_HH
#define _H265_VIDEO_FILE_SINK_HH

#ifndef _H264_OR_5_VIDEO_FILE_SINK_HH
#include "H264or5VideoFileSink.hh"
#endif

#include "liveDef.hh"

class H265VideoFileSink : public H264or5VideoFileSink {
public:
	static H265VideoFileSink* createNew(BaseEnv& env, char const* fileName,
		char const* sPropVPSStr = NULL,
		char const* sPropSPSStr = NULL,
		char const* sPropPPSStr = NULL,
		// The "sProp*Str" parameters are optional 'SDP format' strings
		// (comma-separated Base64-encoded) representing VPS, SPS, and/or PPS NAL-units
		// to prepend to the output
		unsigned bufferSize = MAX_BUFFER_SIZE /*100000*/,
		Boolean oneFilePerFrame = False);
	// See "FileSink.hh" for a description of these parameters.

protected:
	H265VideoFileSink(BaseEnv& env, FILE* fid, char const* sPropVPSStr, char const* sPropSPSStr, char const* sPropPPSStr, unsigned bufferSize, char const* perFrameFileNamePrefix);
	// called only by createNew()
	virtual ~H265VideoFileSink();
};

#endif
