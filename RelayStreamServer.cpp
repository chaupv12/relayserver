#include <BaseUtilEnv.hh>
#include "ActiveRTSPServer.hh"
#include "version.hh"
#include <GroupsockHelper.hh>

int main(int argc, char** argv) {
	TaskScheduler* scheduler = BaseTaskScheduler::createNew();
	BaseEnv* env = BaseUtilEnv::createNew(*scheduler);

	UserAuthenticationDatabase* authDB = NULL;
#ifdef ACCESS_CONTROL
	// To implement client access control to the RTSP server, do the following:
	authDB = new UserAuthenticationDatabase;
	authDB->addUserRecord("username1", "password1"); // replace these with real strings
	// Repeat the above with each <username>, <password> that you wish to allow access to the server.
#endif

	//Create the RTSP server with the default port(554), the alternative port(8554)
	RTSPServerv2* rtspServer;
	portNumBits rtspServerPortNum = 554;
	rtspServer = ActiveRTSPServer::createNew(*env, rtspServerPortNum, authDB);
	if (rtspServer == NULL) {
		rtspServerPortNum = 8554;
		rtspServer = ActiveRTSPServer::createNew(*env, rtspServerPortNum, authDB);
	}
	if (rtspServer == NULL) {
		*env << "Failed to create RTSP server: " << env->getResultMsg() << "\n";
		return -1;
	}

	*env << "RTSP Relay Media Server\n";
	*env << "\tversion " << MEDIA_SERVER_VERSION_STRING << " (Streaming Media library version " << LIVEMEDIA_LIBRARY_VERSION_STRING << ").\n";

	
	env->taskScheduler().doEventLoop(); // does not return

	return 0; // only to prevent compiler warning
}
