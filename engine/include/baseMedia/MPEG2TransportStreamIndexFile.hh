#ifndef _MPEG2_TRANSPORT_STREAM_INDEX_FILE_HH
#define _MPEG2_TRANSPORT_STREAM_INDEX_FILE_HH

#ifndef _MEDIA_HH
#include "Media.hh"
#endif

#define INDEX_RECORD_SIZE 11

class MPEG2TransportStreamIndexFile: public Medium {
public:
  static MPEG2TransportStreamIndexFile* createNew(BaseEnv& env,
						  char const* indexFileName);

  virtual ~MPEG2TransportStreamIndexFile();

  // Functions that map between a playing time and a Transport packet number
  // in the original Transport Stream file:

  void lookupTSPacketNumFromNPT(float& npt, unsigned long& tsPacketNumber,
			    unsigned long& indexRecordNumber);
    // Looks up the Transport Stream Packet number corresponding to "npt".
	// (This may modify "npt" to a more exact value.)
        // (We also return the index record number that we looked up.)

  void lookupPCRFromTSPacketNum(unsigned long& tsPacketNumber, Boolean reverseToPreviousCleanPoint,
				float& pcr, unsigned long& indexRecordNumber);
    // Looks up the PCR timestamp for the transport packet "tsPacketNumber".
	// (Adjust "tsPacketNumber" only if "reverseToPreviousCleanPoint" is True.)
        // (We also return the index record number that we looked up.)

  // Miscellaneous functions used to implement 'trick play':
  Boolean readIndexRecordValues(unsigned long indexRecordNum,
				unsigned long& transportPacketNum, u_int8_t& offset,
				u_int8_t& size, float& pcr, u_int8_t& recordType);
  float getPlayingDuration();
  void stopReading() { closeFid(); }

  int mpegVersion();
      // returns the best guess for the version of MPEG being used for data within the underlying Transport Stream file.
      // (1,2,4, or 5 (representing H.264).  0 means 'don't know' (usually because the index file is empty))

private:
  MPEG2TransportStreamIndexFile(BaseEnv& env, char const* indexFileName);

  Boolean openFid();
  Boolean seekToIndexRecord(unsigned long indexRecordNumber);
  Boolean readIndexRecord(unsigned long indexRecordNum); // into "fBuf"
  Boolean readOneIndexRecord(unsigned long indexRecordNum); // closes "fFid" at end
  void closeFid();

  u_int8_t recordTypeFromBuf() { return fBuf[0]; }
  u_int8_t offsetFromBuf() { return fBuf[1]; }
  u_int8_t sizeFromBuf() { return fBuf[2]; }
  float pcrFromBuf(); // after "fBuf" has been read
  unsigned long tsPacketNumFromBuf();
  void setMPEGVersionFromRecordType(u_int8_t recordType);

  Boolean rewindToCleanPoint(unsigned long&ixFound);
      // used to implement "lookupTSPacketNumber()"

private:
  char* fFileName;
  FILE* fFid; // used internally when reading from the file
  int fMPEGVersion;
  unsigned long fCurrentIndexRecordNum; // within "fFid"
  float fCachedPCR;
  unsigned long fCachedTSPacketNumber, fCachedIndexRecordNumber;
  unsigned long fNumIndexRecords;
  unsigned char fBuf[INDEX_RECORD_SIZE]; // used for reading index records from file
};

#endif
