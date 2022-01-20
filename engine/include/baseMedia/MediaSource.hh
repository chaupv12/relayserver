#ifndef _MEDIA_SOURCE_HH
#define _MEDIA_SOURCE_HH

#ifndef _MEDIA_HH
#include "Media.hh"
#endif

class MediaSource: public Medium {
public:
  static Boolean lookupByName(BaseEnv& env, char const* sourceName, MediaSource*& resultSource);
  virtual void getAttributes() const;
      // attributes are returned in "env's" 'result message'

  // The MIME type of this source:
  virtual char const* MIMEtype() const;

  // Test for specific types of source:
  virtual Boolean isFramedSource() const;
  virtual Boolean isRTPSource() const;
  virtual Boolean isMPEG1or2VideoStreamFramer() const;
  virtual Boolean isMPEG4VideoStreamFramer() const;
  virtual Boolean isH264VideoStreamFramer() const;
  virtual Boolean isH265VideoStreamFramer() const;
  virtual Boolean isDVVideoStreamFramer() const;
  virtual Boolean isJPEGVideoSource() const;
  virtual Boolean isAMRAudioSource() const;
  virtual Boolean isMPEG2TransportStreamMultiplexor() const;

protected:
  MediaSource(BaseEnv& env); // abstract base class
  virtual ~MediaSource();

private:
  // redefined virtual functions:
  virtual Boolean isSource() const;
};

#endif
