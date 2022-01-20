#ifndef _MPEG2_TRANSPORT_STREAM_DEMUX_HH
#define _MPEG2_TRANSPORT_STREAM_DEMUX_HH

#ifndef _FRAMED_SOURCE_HH
#include "FramedSource.hh"
#endif

class MPEG2TransportStreamDemux : public Medium {
public:
	static MPEG2TransportStreamDemux* createNew(BaseEnv& env,
		FramedSource* inputSource,
		FramedSource::onCloseFunc* onCloseFunc,
		void* onCloseClientData);

private:
	MPEG2TransportStreamDemux(BaseEnv& env, FramedSource* inputSource,
		FramedSource::onCloseFunc* onCloseFunc, void* onCloseClientData);
	// called only by createNew()
	virtual ~MPEG2TransportStreamDemux();

	static void handleEndOfFile(void* clientData);
	void handleEndOfFile();

private:
	class MPEG2TransportStreamParser* fParser;
	FramedSource::onCloseFunc* fOnCloseFunc;
	void* fOnCloseClientData;
};

#endif
