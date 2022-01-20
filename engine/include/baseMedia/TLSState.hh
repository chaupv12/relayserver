#define NO_OPENSSL 0

#ifndef _TLS_STATE_HH
#define _TLS_STATE_HH

#ifndef _NET_COMMON_H
#include "NetCommon.h"
#endif
#ifndef _BOOLEAN_HH
#include "Boolean.hh"
#endif
#ifndef NO_OPENSSL
#include <openssl/ssl.h>
#endif

class TLSState {
public:
	TLSState(class RTSPClientv2& client);
	virtual ~TLSState();

public:
	Boolean isNeeded;

	int connect(int socketNum); // returns: -1 (unrecoverable error), 0 (pending), 1 (done)
	int write(const char* data, unsigned count);
	int read(u_int8_t* buffer, unsigned bufferSize);

private:
	void reset();
	Boolean setup(int socketNum);

#ifndef NO_OPENSSL
private:
	class RTSPClient& fClient;
	Boolean fHasBeenSetup;
	SSL_CTX* fCtx;
	SSL* fCon;
#endif
};

#endif
