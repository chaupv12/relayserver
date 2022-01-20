#ifndef _QUICKTIME_GENERIC_RTP_SOURCE_HH
#define _QUICKTIME_GENERIC_RTP_SOURCE_HH

#ifndef _MULTI_FRAMED_RTP_SOURCE_HH
#include "MultiFramedRTPSource.hh"
#endif

class QuickTimeGenericRTPSource : public MultiFramedRTPSource {
public:
	static QuickTimeGenericRTPSource*
		createNew(BaseEnv& env, Groupsock* RTPgs,
			unsigned char rtpPayloadFormat, unsigned rtpTimestampFrequency,
			char const* mimeTypeString);

	// QuickTime-specific information, set from the QuickTime header
	// in each packet.  This, along with the data following the header,
	// is used by receivers.
	struct QTState {
		char PCK;
		unsigned timescale;
		char* sdAtom;
		unsigned sdAtomSize;
		unsigned short width, height;
		// later add other state as needed #####
	} qtState;

protected:
	virtual ~QuickTimeGenericRTPSource();

private:
	QuickTimeGenericRTPSource(BaseEnv& env, Groupsock* RTPgs,
		unsigned char rtpPayloadFormat,
		unsigned rtpTimestampFrequency,
		char const* mimeTypeString);
	// called only by createNew()

private:
	// redefined virtual functions:
	virtual Boolean processSpecialHeader(BufferedPacket* packet,
		unsigned& resultSpecialHeaderSize);
	virtual char const* MIMEtype() const;

private:
	char const* fMIMEtypeString;
};

#endif
