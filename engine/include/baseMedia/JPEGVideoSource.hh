#ifndef _JPEG_VIDEO_SOURCE_HH
#define _JPEG_VIDEO_SOURCE_HH

#ifndef _FRAMED_SOURCE_HH
#include "FramedSource.hh"
#endif

class JPEGVideoSource: public FramedSource {
public:
  virtual u_int8_t type() = 0;
  virtual u_int8_t qFactor() = 0;
  virtual u_int8_t width() = 0; // # pixels/8 (or 0 for 2048 pixels)
  virtual u_int8_t height() = 0; // # pixels/8 (or 0 for 2048 pixels)

  virtual u_int8_t const* quantizationTables(u_int8_t& precision,
					     u_int16_t& length);
    // If "qFactor()" returns a value >= 128, then this function is called
    // to tell us the quantization tables that are being used.
    // (The default implementation of this function just returns NULL.)
    // "precision" and "length" are as defined in RFC 2435, section 3.1.8.

  virtual u_int16_t restartInterval();
    // If restart intervals are being used (i.e., 64 <= type() <= 127), then this function must be
    // redefined - by a subclass - to return a non-zero value.

protected:
  JPEGVideoSource(BaseEnv& env); // abstract base class
  virtual ~JPEGVideoSource();

private:
  // redefined virtual functions:
  virtual Boolean isJPEGVideoSource() const;
};

#endif
