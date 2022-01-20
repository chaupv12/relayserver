#ifndef _DEVICE_SOURCE_HH
#define _DEVICE_SOURCE_HH

#ifndef _FRAMED_SOURCE_HH
#include "FramedSource.hh"
#endif

// The following class can be used to define specific encoder parameters
class DeviceParameters {
  //%%% TO BE WRITTEN %%%
};

class DeviceSource: public FramedSource {
public:
  static DeviceSource* createNew(BaseEnv& env,
				 DeviceParameters params);

public:
  static EventTriggerId eventTriggerId;
  // Note that this is defined here to be a static class variable, because this code is intended to illustrate how to
  // encapsulate a *single* device - not a set of devices.
  // You can, however, redefine this to be a non-static member variable.

protected:
  DeviceSource(BaseEnv& env, DeviceParameters params);
  // called only by createNew(), or by subclass constructors
  virtual ~DeviceSource();

private:
  // redefined virtual functions:
  virtual void doGetNextFrame();
  //virtual void doStopGettingFrames(); // optional

private:
  static void deliverFrame0(void* clientData);
  void deliverFrame();

private:
  static unsigned referenceCount; // used to count how many instances of this class currently exist
  DeviceParameters fParams;
};

#endif
