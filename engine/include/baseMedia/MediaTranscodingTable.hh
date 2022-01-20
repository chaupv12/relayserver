#ifndef _MEDIA_TRANSCODING_TABLE_HH
#define _MEDIA_TRANSCODING_TABLE_HH

#ifndef _FRAMED_FILTER_HH
#include "FramedFilter.hh"
#endif
#ifndef _MEDIA_SESSION_HH
#include "MediaSession.hh"
#endif

class MediaTranscodingTable: public Medium {
public:
  virtual FramedFilter* lookupTranscoder(MediaSubsession& /*inputCodecDescription*/, // in
		   char*& outputCodecName/* out; must be delete[]d later */) {
    // Default implementation: Return NULL (indicating: no transcoding).
    // You would reimplement this virtual function in a subclass to return a new 'transcoding'
    // "FramedFilter" (subclass) object for each ("mediumName","codecName") that you wish to
    // transcode (or return NULL for no transcoding).
    // (Note that "inputCodecDescription" must have a non-NULL "readSource()"; this is used
    //  as the input to the new "FramedFilter" (subclass) object.)
    outputCodecName = NULL;
    return NULL;
  }

  virtual Boolean weWillTranscode(char const* /*mediumName*/, char const* /*codecName*/) {
    // Default implementation: Return False.
    // You would reimplement this in a subclass - returning True for each
    // <mediumName>/<codecName> for which you'll do transcoding.
    // Note: Unlike "lookupTranscoder()", this function does not actually create any 'transcoding'
    // filter objects.  (It may be called before "MediaSubsession::initiate()".)
    return False;
  }

protected: // we are to be subclassed only
  MediaTranscodingTable(BaseEnv& env)
    : Medium(env) {
  }
  virtual ~MediaTranscodingTable() {
  }
};

#endif
