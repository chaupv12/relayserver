#ifndef _RAW_VIDEO_FRAME_PARAMETERS_HH
#define _RAW_VIDEO_FRAME_PARAMETERS_HH

class RawVideoFrameParameters {
public:
	RawVideoFrameParameters(unsigned width, unsigned height, unsigned depth, char const* sampling);
	virtual ~RawVideoFrameParameters();

public:
	u_int16_t pgroupSize; // in octets
	u_int16_t numPixelsInPgroup;
	u_int32_t scanLineSize; // in octets
	u_int32_t frameSize; // in octets
	u_int16_t scanLineIterationStep; // usually 1, but 2 for sampling=="YCbCr-4:2:0"
};

#endif
