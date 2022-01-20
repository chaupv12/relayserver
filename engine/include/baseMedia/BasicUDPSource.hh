#ifndef _BASIC_UDP_SOURCE_HH
#define _BASIC_UDP_SOURCE_HH

#ifndef _FRAMED_SOURCE_HH
#include "FramedSource.hh"
#endif
#ifndef _GROUPSOCK_HH
#include "Groupsock.hh"
#endif

class BasicUDPSource: public FramedSource {
public:
  static BasicUDPSource* createNew(BaseEnv& env, Groupsock* inputGS);

  virtual ~BasicUDPSource();

  Groupsock* gs() const { return fInputGS; }

private:
  BasicUDPSource(BaseEnv& env, Groupsock* inputGS);
      // called only by createNew()

  static void incomingPacketHandler(BasicUDPSource* source, int mask);
  void incomingPacketHandler1();

private: // redefined virtual functions:
  virtual unsigned maxFrameSize() const;
  virtual void doGetNextFrame();
  virtual void doStopGettingFrames();

private:
  Groupsock* fInputGS;
  Boolean fHaveStartedReading;
};

#endif
