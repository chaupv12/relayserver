#include "BaseUtilEnv.hh"
#include "ActiveRTSPServer.hh"
#include <liveMedia.hh>
#include "ProxyServerMediaSubsession.hh"
#include <string.h>

#include "liveDef.hh"

ActiveRTSPServer* ActiveRTSPServer::createNew(BaseEnv& env, Port ourPort, UserAuthenticationDatabase* authDatabase, unsigned reclamationTestSeconds) {
	int ourSocketIPv4 = setUpOurSocket(env, ourPort, AF_INET);
	int ourSocketIPv6 = setUpOurSocket(env, ourPort, AF_INET6);
	if (ourSocketIPv4 < 0 && ourSocketIPv6 < 0) return NULL;

	return new ActiveRTSPServer(env, ourSocketIPv4, ourSocketIPv6, ourPort, authDatabase, reclamationTestSeconds);
}

ActiveRTSPServer::ActiveRTSPServer(BaseEnv& env, int ourSocketIPv4, int ourSocketIPv6, Port ourPort, UserAuthenticationDatabase* authDatabase, unsigned reclamationTestSeconds)
	: RTSPServerv2(env, ourSocketIPv4, ourSocketIPv6, ourPort, authDatabase, reclamationTestSeconds) {
}

ActiveRTSPServer::~ActiveRTSPServer() {
}

static ServerMediaSession* createNewSMS(BaseEnv& env, char const* fileName, FILE* fid); // forward
static ServerMediaSession* createNewSMSRelay(BaseEnv& env, GenericMediaServer* ourMedServer, char* relayInputUrl, char const* streamName);

void RemoveChars(char* s, char c)
{
	int writer = 0, reader = 0;

	while (s[reader])
	{
		if (s[reader] != c)
		{
			s[writer++] = s[reader];
		}

		reader++;
	}

	s[writer] = 0;
}


void ActiveRTSPServer::lookupServerMediaSession(char const* streamName, lookupServerMediaSessionCompletionFunc* completionFunc, void* completionClientData, Boolean isFirstLookupInSession) {

	if (strncmp(streamName, "stream?url=[rtsp://", 19) != 0 && strncmp(streamName, "stream?url=[rtsps://", 20) != 0) {
		// First, check whether the specified "streamName" exists as a local file:
		FILE* fid = fopen(streamName, "rb");
		Boolean const fileExists = fid != NULL;

		// Next, check whether we already have a "ServerMediaSession" for this file:
		ServerMediaSession* sms = getServerMediaSession(streamName);
		Boolean const smsExists = sms != NULL;

		// Handle the four possibilities for "fileExists" and "smsExists":
		if (!fileExists) {
			if (smsExists) {
				// "sms" was created for a file that no longer exists. Remove it:
				removeServerMediaSession(sms);
			}

			sms = NULL;
		}
		else {
			if (smsExists && isFirstLookupInSession) {
				// Remove the existing "ServerMediaSession" and create a new one, in case the underlying
				// file has changed in some way:
				removeServerMediaSession(sms);
				sms = NULL;
			}

			if (sms == NULL) {
				sms = createNewSMS(envir(), streamName, fid);
				addServerMediaSession(sms);
			}

			fclose(fid);
		}

		if (completionFunc != NULL) {
			(*completionFunc)(completionClientData, sms);
		}
	}
	else {
		int verbosityLevel = 1;
		portNumBits tunnelOverHTTPPortNum = 0;
		portNumBits rtspServerPortNum = 554;
		char* username = NULL;
		char* password = NULL;
		char* relayInputUrl = NULL;
		char* input = (char*)streamName;
		char* p;
		p = strtok(input, "=");

		if (p)
		{
			p = strtok(NULL, "=");
			if (p)
				relayInputUrl = p;
		}
		RemoveChars(relayInputUrl, '[');
		RemoveChars(relayInputUrl, ']');

		char streamNames[60];
		sprintf(streamNames, "stream?url=[%s]", relayInputUrl);

		ServerMediaSession* sms = getServerMediaSession(streamNames);
		Boolean const smsExists = sms != NULL;

		if (sms == NULL) {
			sms = ProxyServerMediaSession::createNew(envir(), this, relayInputUrl, streamNames, username, password, tunnelOverHTTPPortNum, verbosityLevel);
			
			char sdp[600];

			sprintf(sdp, "%s", sms->getBasicSDP());
			MediaSession* ms = MediaSession::createNew(envir(), sdp);

			if (ms != NULL) {
				MediaSubsessionIterator iter(*ms);

				for (MediaSubsession* mss = iter.next(); mss != NULL; mss = iter.next()) {

					ServerMediaSubsession* smss = new ProxyServerMediaSubsession(*mss, 554, false);
					sms->addSubsession(smss);

				}
			}

			addServerMediaSession(sms);
		}

		if (completionFunc != NULL) {
			(*completionFunc)(completionClientData, sms);
		}

	}
}

// Special code for handling Matroska files:
struct MatroskaDemuxCreationState {
	MatroskaFileServerDemux* demux;
	char watchVariable;
};
static void onMatroskaDemuxCreation(MatroskaFileServerDemux * newDemux, void* clientData)
{
	MatroskaDemuxCreationState* creationState = (MatroskaDemuxCreationState*)clientData;
	creationState->demux = newDemux;
	creationState->watchVariable = 1;
}
// END Special code for handling Matroska files:

// Special code for handling Ogg files:
struct OggDemuxCreationState {
	OggFileServerDemux* demux;
	char watchVariable;
};
static void onOggDemuxCreation(OggFileServerDemux * newDemux, void* clientData) {
	OggDemuxCreationState* creationState = (OggDemuxCreationState*)clientData;
	creationState->demux = newDemux;
	creationState->watchVariable = 1;
}
// END Special code for handling Ogg files:

#define NEW_SMS(description) do {\
char const* descStr = description\
    ", streamed by the Clamos Media Server";\
sms = ServerMediaSession::createNew(env, fileName, fileName, descStr);\
} while(0)

#define NEW_SMS_RELAY(streamName, ourMediaServer) do {\
char const* strName = streamName;\
sms = ProxyServerMediaSession::createNew(env, ourMedServer, relayInputUrl, strName, "", "", 80, 1);\
} while(0)


static ServerMediaSession* createNewSMSRelay(BaseEnv& env, GenericMediaServer* ourMedServer, char* relayInputUrl, char const* streamName) {

	ServerMediaSession* sms = NULL;

	NEW_SMS_RELAY(streamName, ourMedServer);
	
	MediaSession* ms = (MediaSession*)sms;
	MediaSubsessionIterator iter(*ms);

	for (MediaSubsession* mss = iter.next(); mss != NULL; mss = iter.next()) {

		ServerMediaSubsession* smss = new ProxyServerMediaSubsession(*mss, 554, false);
		sms->addSubsession(smss);
	}


	return sms;
}

	static ServerMediaSession* createNewSMS(BaseEnv & env, char const* fileName, FILE* /*fid*/) {
		// Use the file name extension to determine the type of "ServerMediaSession":
		char const* extension = strrchr(fileName, '.');
		if (extension == NULL) return NULL;

		ServerMediaSession* sms = NULL;
		Boolean const reuseSource = False;
		if (strcmp(extension, ".aac") == 0) {
			// Assumed to be an AAC Audio (ADTS format) file:
			NEW_SMS("AAC Audio");
			sms->addSubsession(ADTSAudioFileServerMediaSubsession::createNew(env, fileName, reuseSource));
		}
		else if (strcmp(extension, ".amr") == 0) {
			// Assumed to be an AMR Audio file:
			NEW_SMS("AMR Audio");
			sms->addSubsession(AMRAudioFileServerMediaSubsession::createNew(env, fileName, reuseSource));
		}
		else if (strcmp(extension, ".ac3") == 0) {
			// Assumed to be an AC-3 Audio file:
			NEW_SMS("AC-3 Audio");
			sms->addSubsession(AC3AudioFileServerMediaSubsession::createNew(env, fileName, reuseSource));
		}
		else if (strcmp(extension, ".m4e") == 0) {
			// Assumed to be a MPEG-4 Video Elementary Stream file:
			NEW_SMS("MPEG-4 Video");
			sms->addSubsession(MPEG4VideoFileServerMediaSubsession::createNew(env, fileName, reuseSource));
		}
		else if (strcmp(extension, ".264") == 0) {
			// Assumed to be a H.264 Video Elementary Stream file:
			NEW_SMS("H.264 Video");
			OutPacketBuffer::maxSize = MAX_BUFFER_SIZE; // 100000 allow for some possibly large H.264 frames
			sms->addSubsession(H264VideoFileServerMediaSubsession::createNew(env, fileName, reuseSource));
		}
		else if (strcmp(extension, ".265") == 0) {
			// Assumed to be a H.265 Video Elementary Stream file:
			NEW_SMS("H.265 Video");
			OutPacketBuffer::maxSize = MAX_BUFFER_SIZE; // 100000 allow for some possibly large H.265 frames
			sms->addSubsession(H265VideoFileServerMediaSubsession::createNew(env, fileName, reuseSource));
		}
		else if (strcmp(extension, ".mp3") == 0) {
			// Assumed to be a MPEG-1 or 2 Audio file:
			NEW_SMS("MPEG-1 or 2 Audio");
			// To stream using 'ADUs' rather than raw MP3 frames, uncomment the following:
		//#define STREAM_USING_ADUS 1
			// To also reorder ADUs before streaming, uncomment the following:
		//#define INTERLEAVE_ADUS 1
			// (For more information about ADUs and interleaving,
			Boolean useADUs = False;
			Interleaving* interleaving = NULL;
#ifdef STREAM_USING_ADUS
			useADUs = True;
#ifdef INTERLEAVE_ADUS
			unsigned char interleaveCycle[] = { 0,2,1,3 }; // or choose your own...
			unsigned const interleaveCycleSize
				= (sizeof interleaveCycle) / (sizeof(unsigned char));
			interleaving = new Interleaving(interleaveCycleSize, interleaveCycle);
#endif
#endif
			sms->addSubsession(MP3AudioFileServerMediaSubsession::createNew(env, fileName, reuseSource, useADUs, interleaving));
		}
		else if (strcmp(extension, ".mpg") == 0) {
			// Assumed to be a MPEG-1 or 2 Program Stream (audio+video) file:
			NEW_SMS("MPEG-1 or 2 Program Stream");
			MPEG1or2FileServerDemux* demux = MPEG1or2FileServerDemux::createNew(env, fileName, reuseSource);
			sms->addSubsession(demux->newVideoServerMediaSubsession());
			sms->addSubsession(demux->newAudioServerMediaSubsession());
		}
		else if (strcmp(extension, ".vob") == 0) {
			// Assumed to be a VOB (MPEG-2 Program Stream, with AC-3 audio) file:
			NEW_SMS("VOB (MPEG-2 video with AC-3 audio)");
			MPEG1or2FileServerDemux* demux = MPEG1or2FileServerDemux::createNew(env, fileName, reuseSource);
			sms->addSubsession(demux->newVideoServerMediaSubsession());
			sms->addSubsession(demux->newAC3AudioServerMediaSubsession());
		}
		else if (strcmp(extension, ".ts") == 0) {
			// Assumed to be a MPEG Transport Stream file:
			// Use an index file name that's the same as the TS file name, except with ".tsx":
			unsigned indexFileNameLen = strlen(fileName) + 2; // allow for trailing "x\0"
			char* indexFileName = new char[indexFileNameLen];
			sprintf(indexFileName, "%sx", fileName);
			NEW_SMS("MPEG Transport Stream");
			sms->addSubsession(MPEG2TransportFileServerMediaSubsession::createNew(env, fileName, indexFileName, reuseSource));
			delete[] indexFileName;
		}
		else if (strcmp(extension, ".wav") == 0) {
			// Assumed to be a WAV Audio file:
			NEW_SMS("WAV Audio Stream");
			// To convert 16-bit PCM data to 8-bit u-law, prior to streaming,
			// change the following to True:
			Boolean convertToULaw = False;
			sms->addSubsession(WAVAudioFileServerMediaSubsession::createNew(env, fileName, reuseSource, convertToULaw));
		}
		else if (strcmp(extension, ".dv") == 0) {
			// Assumed to be a DV Video file
			// First, make sure that the RTPSinks' buffers will be large enough to handle the huge size of DV frames (as big as 288000).
			OutPacketBuffer::maxSize = 300000;

			NEW_SMS("DV Video");
			sms->addSubsession(DVVideoFileServerMediaSubsession::createNew(env, fileName, reuseSource));
		}
		else if (strcmp(extension, ".mkv") == 0 || strcmp(extension, ".webm") == 0) {
			// Assumed to be a Matroska file (note that WebM ('.webm') files are also Matroska files)
			OutPacketBuffer::maxSize = 300000; // allow for some possibly large VP8 or VP9 frames
			NEW_SMS("Matroska video+audio+(optional)subtitles");

			// Create a Matroska file server demultiplexor for the specified file.
			// (We enter the event loop to wait for this to complete.)
			MatroskaDemuxCreationState creationState;
			creationState.watchVariable = 0;
			MatroskaFileServerDemux::createNew(env, fileName, onMatroskaDemuxCreation, &creationState);
			env.taskScheduler().doEventLoop(&creationState.watchVariable);

			ServerMediaSubsession* smss;
			while ((smss = creationState.demux->newServerMediaSubsession()) != NULL) {
				sms->addSubsession(smss);
			}
		}
		else if (strcmp(extension, ".ogg") == 0 || strcmp(extension, ".ogv") == 0 || strcmp(extension, ".opus") == 0) {
			// Assumed to be an Ogg file
			NEW_SMS("Ogg video and/or audio");

			// Create a Ogg file server demultiplexor for the specified file.
			// (We enter the event loop to wait for this to complete.)
			OggDemuxCreationState creationState;
			creationState.watchVariable = 0;
			OggFileServerDemux::createNew(env, fileName, onOggDemuxCreation, &creationState);
			env.taskScheduler().doEventLoop(&creationState.watchVariable);

			ServerMediaSubsession* smss;
			while ((smss = creationState.demux->newServerMediaSubsession()) != NULL) {
				sms->addSubsession(smss);
			}
		}
		
		return sms;
	}
