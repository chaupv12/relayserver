#ifndef _FRAMED_FILTER_HH
#define _FRAMED_FILTER_HH

#ifndef _FRAMED_SOURCE_HH
#include "FramedSource.hh"
#endif

class FramedFilter : public FramedSource {
public:
	FramedSource* inputSource() const { return fInputSource; }

	void reassignInputSource(FramedSource* newInputSource) { fInputSource = newInputSource; }

	// Call before destruction if you want to prevent the destructor from closing the input source
	void detachInputSource();

protected:
	FramedFilter(BaseEnv& env, FramedSource* inputSource);
	// abstract base class
	virtual ~FramedFilter();

protected:
	// Redefined virtual functions (with default 'null' implementations):
	virtual char const* MIMEtype() const;
	virtual void getAttributes() const;
	virtual void doStopGettingFrames();

protected:
	FramedSource* fInputSource;
};

#endif
