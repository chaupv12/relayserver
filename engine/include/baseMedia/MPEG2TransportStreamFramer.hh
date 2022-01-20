#ifndef _MPEG2_TRANSPORT_STREAM_FRAMER_HH
#define _MPEG2_TRANSPORT_STREAM_FRAMER_HH

#ifndef _FRAMED_FILTER_HH
#include "FramedFilter.hh"
#endif

#ifndef _HASH_TABLE_HH
#include "HashTable.hh"
#endif

class MPEG2TransportStreamFramer : public FramedFilter {
public:
	static MPEG2TransportStreamFramer*
		createNew(BaseEnv& env, FramedSource* inputSource);

	u_int64_t tsPacketCount() const { return fTSPacketCount; }

	void changeInputSource(FramedSource* newInputSource) { fInputSource = newInputSource; }

	void clearPIDStatusTable();
	void setNumTSPacketsToStream(unsigned long numTSRecordsToStream);
	void setPCRLimit(float pcrLimit);

protected:
	MPEG2TransportStreamFramer(BaseEnv& env, FramedSource* inputSource);
	// called only by createNew()
	virtual ~MPEG2TransportStreamFramer();

private:
	// Redefined virtual functions:
	virtual void doGetNextFrame();
	virtual void doStopGettingFrames();

private:
	static void afterGettingFrame(void* clientData, unsigned frameSize,
		unsigned numTruncatedBytes,
		struct timeval presentationTime,
		unsigned durationInMicroseconds);
	void afterGettingFrame1(unsigned frameSize,
		struct timeval presentationTime);

	Boolean updateTSPacketDurationEstimate(unsigned char* pkt, double timeNow);

private:
	u_int64_t fTSPacketCount;
	double fTSPacketDurationEstimate;
	HashTable* fPIDStatusTable;
	u_int64_t fTSPCRCount;
	Boolean fLimitNumTSPacketsToStream;
	unsigned long fNumTSPacketsToStream; // used iff "fLimitNumTSPacketsToStream" is True
	Boolean fLimitTSPacketsToStreamByPCR;
	float fPCRLimit; // used iff "fLimitTSPacketsToStreamByPCR" is True
};

#endif
