#ifndef _MPEG4_VIDEO_STREAM_FRAMER_HH
#define _MPEG4_VIDEO_STREAM_FRAMER_HH

#ifndef _MPEG_VIDEO_STREAM_FRAMER_HH
#include "MPEGVideoStreamFramer.hh"
#endif

class MPEG4VideoStreamFramer: public MPEGVideoStreamFramer {
public:
  static MPEG4VideoStreamFramer*
  createNew(BaseEnv& env, FramedSource* inputSource);

  u_int8_t profile_and_level_indication() const {
    return fProfileAndLevelIndication;
  }

  unsigned char* getConfigBytes(unsigned& numBytes) const;

  void setConfigInfo(u_int8_t profileAndLevelIndication, char const* configStr);
    // Assigns the "profile_and_level_indication" number, and the 'config' bytes.
    // If this function is not called, then this data is only assigned later, when it appears in the input stream.

protected:
  MPEG4VideoStreamFramer(BaseEnv& env,
			 FramedSource* inputSource,
			 Boolean createParser = True);
      // called only by createNew(), or by subclass constructors
  virtual ~MPEG4VideoStreamFramer();

  void startNewConfig();
  void appendToNewConfig(unsigned char* newConfigBytes,
			 unsigned numNewBytes);
  void completeNewConfig();

private:
  // redefined virtual functions:
  virtual Boolean isMPEG4VideoStreamFramer() const;

protected:
  u_int8_t fProfileAndLevelIndication;
  unsigned char* fConfigBytes;
  unsigned fNumConfigBytes;

private:
  unsigned char* fNewConfigBytes;
  unsigned fNumNewConfigBytes;
  friend class MPEG4VideoStreamParser; // hack
};

#endif
