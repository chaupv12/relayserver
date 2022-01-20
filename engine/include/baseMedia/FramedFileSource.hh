#ifndef _FRAMED_FILE_SOURCE_HH
#define _FRAMED_FILE_SOURCE_HH

#ifndef _FRAMED_SOURCE_HH
#include "FramedSource.hh"
#endif

class FramedFileSource: public FramedSource {
protected:
  FramedFileSource(BaseEnv& env, FILE* fid); // abstract base class
  virtual ~FramedFileSource();

protected:
  FILE* fFid;
};

#endif
