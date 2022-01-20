#ifndef _BASIC_UDP_SINK_HH
#define _BASIC_UDP_SINK_HH

#ifndef _MEDIA_SINK_HH
#include "MediaSink.hh"
#endif
#ifndef _GROUPSOCK_HH
#include <Groupsock.hh>
#endif

class BasicUDPSink: public MediaSink {
public:
  static BasicUDPSink* createNew(BaseEnv& env, Groupsock* gs,
				  unsigned maxPayloadSize = 1450);
protected:
  BasicUDPSink(BaseEnv& env, Groupsock* gs, unsigned maxPayloadSize);
      // called only by createNew()
  virtual ~BasicUDPSink();

private: // redefined virtual functions:
  virtual Boolean continuePlaying();

private:
  void continuePlaying1();

  static void afterGettingFrame(void* clientData, unsigned frameSize,
				unsigned numTruncatedBytes,
				struct timeval presentationTime,
				unsigned durationInMicroseconds);
  void afterGettingFrame1(unsigned frameSize, unsigned numTruncatedBytes,
			  unsigned durationInMicroseconds);

  static void sendNext(void* firstArg);

private:
  Groupsock* fGS;
  unsigned fMaxPayloadSize;
  unsigned char* fOutputBuffer;
  struct timeval fNextSendTime;
};

#endif
