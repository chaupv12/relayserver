#ifndef _MPEG2_TRANSPORT_FILE_SERVER_MEDIA_SUBSESSION_HH
#define _MPEG2_TRANSPORT_FILE_SERVER_MEDIA_SUBSESSION_HH

#ifndef _FILE_SERVER_MEDIA_SUBSESSION_HH
#include "FileServerMediaSubsession.hh"
#endif
#ifndef _MPEG2_TRANSPORT_STREAM_FRAMER_HH
#include "MPEG2TransportStreamFramer.hh"
#endif
#ifndef _BYTE_STREAM_FILE_SOURCE_HH
#include "ByteStreamFileSource.hh"
#endif
#ifndef _MPEG2_TRANSPORT_STREAM_TRICK_MODE_FILTER_HH
#include "MPEG2TransportStreamTrickModeFilter.hh"
#endif
#ifndef _MPEG2_TRANSPORT_STREAM_FROM_ES_SOURCE_HH
#include "MPEG2TransportStreamFromESSource.hh"
#endif

class ClientTrickPlayState; // forward

class MPEG2TransportFileServerMediaSubsession : public FileServerMediaSubsession {
public:
	static MPEG2TransportFileServerMediaSubsession* createNew(BaseEnv& env, char const* dataFileName, char const* indexFileName, Boolean reuseFirstSource);

protected:
	MPEG2TransportFileServerMediaSubsession(BaseEnv& env, char const* fileName, MPEG2TransportStreamIndexFile* indexFile, Boolean reuseFirstSource);
	
	// called only by createNew();
	virtual ~MPEG2TransportFileServerMediaSubsession();

	virtual ClientTrickPlayState* newClientTrickPlayState();

private: // redefined virtual functions
	// Note that because - to implement 'trick play' operations - we're operating on
	// more than just the input source, we reimplement some functions that are
	// already implemented in "OnDemandServerMediaSubsession", rather than
	// reimplementing "seekStreamSource()" and "setStreamSourceScale()":
	virtual void startStream(unsigned clientSessionId, void* streamToken,
		TaskFunc* rtcpRRHandler,
		void* rtcpRRHandlerClientData,
		unsigned short& rtpSeqNum,
		unsigned& rtpTimestamp,
		ServerRequestAlternativeByteHandler* serverRequestAlternativeByteHandler,
		void* serverRequestAlternativeByteHandlerClientData);

	virtual void pauseStream(unsigned clientSessionId, void* streamToken);
	virtual void seekStream(unsigned clientSessionId, void* streamToken, double& seekNPT, double streamDuration, u_int64_t& numBytes);
	virtual void setStreamScale(unsigned clientSessionId, void* streamToken, float scale);
	virtual void deleteStream(unsigned clientSessionId, void*& streamToken);

	// The virtual functions that are usually implemented by "ServerMediaSubsession"s:
	virtual FramedSource* createNewStreamSource(unsigned clientSessionId, unsigned& estBitrate);
	virtual RTPSink* createNewRTPSink(Groupsock* rtpGroupsock, unsigned char rtpPayloadTypeIfDynamic, FramedSource* inputSource);

	virtual void testScaleFactor(float& scale);
	virtual float duration() const;

private:
	ClientTrickPlayState* lookupClient(unsigned clientSessionId);

private:
	MPEG2TransportStreamIndexFile* fIndexFile;
	float fDuration;
	HashTable* fClientSessionHashTable; // indexed by client session id
};


// This class encapsulates the 'trick play' state for each current client (for
// a given "MPEG2TransportFileServerMediaSubsession" - i.e., Transport Stream file).
// It is used only within the implementation of "MPEG2TransportFileServerMediaSubsession", but is included here,
// in case subclasses of "MPEG2TransportFileServerMediaSubsession" want to use it.

class ClientTrickPlayState {
public:
	ClientTrickPlayState(MPEG2TransportStreamIndexFile* indexFile);

	// Functions to bring "fNPT", "fTSRecordNum" and "fIxRecordNum" in sync:
	unsigned long updateStateFromNPT(double npt, double seekDuration);
	void updateStateOnScaleChange();
	void updateStateOnPlayChange(Boolean reverseToPreviousVSH);

	void handleStreamDeletion();
	void setSource(MPEG2TransportStreamFramer* framer);

	void setNextScale(float nextScale) { fNextScale = nextScale; }
	Boolean areChangingScale() const { return fNextScale != fScale; }

protected:
	void updateTSRecordNum();
	void reseekOriginalTransportStreamSource();

protected:
	MPEG2TransportStreamIndexFile* fIndexFile;
	ByteStreamFileSource* fOriginalTransportStreamSource;
	MPEG2TransportStreamTrickModeFilter* fTrickModeFilter;
	MPEG2TransportStreamFromESSource* fTrickPlaySource;
	MPEG2TransportStreamFramer* fFramer;
	float fScale, fNextScale, fNPT;
	unsigned long fTSRecordNum, fIxRecordNum;
};

#endif
