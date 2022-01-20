#ifndef _MPEG_1OR2_FILE_SERVER_DEMUX_HH
#define _MPEG_1OR2_FILE_SERVER_DEMUX_HH

#ifndef _SERVER_MEDIA_SESSION_HH
#include "ServerMediaSession.hh"
#endif
#ifndef _MPEG_1OR2_DEMUXED_ELEMENTARY_STREAM_HH
#include "MPEG1or2DemuxedElementaryStream.hh"
#endif

class MPEG1or2FileServerDemux: public Medium {
public:
  static MPEG1or2FileServerDemux*
  createNew(BaseEnv& env, char const* fileName, Boolean reuseFirstSource);

  ServerMediaSubsession* newAudioServerMediaSubsession(); // MPEG-1 or 2 audio
  ServerMediaSubsession* newVideoServerMediaSubsession(Boolean iFramesOnly = False,
						       double vshPeriod = 5.0
		       /* how often (in seconds) to inject a Video_Sequence_Header,
			  if one doesn't already appear in the stream */);
  ServerMediaSubsession* newAC3AudioServerMediaSubsession(); // AC-3 audio (from VOB)

  unsigned fileSize() const { return fFileSize; }
  float fileDuration() const { return fFileDuration; }

private:
  MPEG1or2FileServerDemux(BaseEnv& env, char const* fileName,
			  Boolean reuseFirstSource);
      // called only by createNew();
  virtual ~MPEG1or2FileServerDemux();

private:
  friend class MPEG1or2DemuxedServerMediaSubsession;
  MPEG1or2DemuxedElementaryStream* newElementaryStream(unsigned clientSessionId,
						       u_int8_t streamIdTag);

  static void onDemuxDeletion(void* clientData, MPEG1or2Demux* demuxBeingDeleted);
  void onDemuxDeletion(MPEG1or2Demux* demuxBeingDeleted);

private:
  char const* fFileName;
  unsigned fFileSize;
  float fFileDuration;
  Boolean fReuseFirstSource;
  MPEG1or2Demux* fSession0Demux;
  MPEG1or2Demux* fLastCreatedDemux;
  unsigned fLastClientSessionId;
};

#endif
