#ifndef _MP3_FILE_SOURCE_HH
#define _MP3_FILE_SOURCE_HH

#ifndef _FRAMED_FILE_SOURCE_HH
#include "FramedFileSource.hh"
#endif

class MP3StreamState; // forward

class MP3FileSource: public FramedFileSource {
public:
  static MP3FileSource* createNew(BaseEnv& env, char const* fileName);

  float filePlayTime() const;
  unsigned fileSize() const;
  void setPresentationTimeScale(unsigned scale);
  void seekWithinFile(double seekNPT, double streamDuration);
      // if "streamDuration" is >0.0, then we limit the stream to that duration, before treating it as EOF

protected:
  MP3FileSource(BaseEnv& env, FILE* fid);
	// called only by createNew()

  virtual ~MP3FileSource();

protected:
  void assignStream(FILE* fid, unsigned filesize);
  Boolean initializeStream();

  MP3StreamState* streamState() {return fStreamState;}

private:
  // redefined virtual functions:
  virtual void doGetNextFrame();
  virtual char const* MIMEtype() const;
  virtual void getAttributes() const;

private:
  static void fileReadableHandler(MP3FileSource* source, int mask);

private:
  MP3StreamState* fStreamState;
  Boolean fFidIsSeekable;
  Boolean fHaveStartedReading;
  unsigned fHaveBeenInitialized;
  struct timeval fFirstFramePresentationTime; // set on stream init
  Boolean fLimitNumBytesToStream;
  unsigned fNumBytesToStream; // used iff "fLimitNumBytesToStream" is True
};

#endif
