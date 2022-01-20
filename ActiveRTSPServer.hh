#ifndef _DYNAMIC_RTSP_SERVER_HH
#define _DYNAMIC_RTSP_SERVER_HH

#ifndef _RTSP_SERVER_HH
#include "RTSPServerv2.hh"
#endif

class ActiveRTSPServer : public RTSPServerv2 {
public:
	static ActiveRTSPServer* createNew(BaseEnv& env, Port ourPort, UserAuthenticationDatabase* authDatabase, unsigned reclamationTestSeconds = 65);

protected:
	ActiveRTSPServer(BaseEnv& env, int ourSocketIPv4, int ourSocketIPv6, Port ourPort, UserAuthenticationDatabase* authDatabase, unsigned reclamationTestSeconds);
	// called only by createNew();
	virtual ~ActiveRTSPServer();

protected: // redefined virtual functions
	virtual void lookupServerMediaSession(char const* streamName, lookupServerMediaSessionCompletionFunc* completionFunc, void* completionClientData, Boolean isFirstLookupInSession);
};

#endif
