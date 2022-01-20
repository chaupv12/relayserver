#ifndef _RTSP_COMMON_HH
#define _RTSP_COMMON_HH

#ifndef _BOOLEAN_HH
#include "Boolean.hh"
#endif

#ifndef _MEDIA_HH
#include <Media.hh> // includes some definitions perhaps needed for Borland compilers?
#endif

#if defined(__WIN32__) || defined(_WIN32) || defined(_QNX4)
#define _strncasecmp _strnicmp
#define snprintf _snprintf
#else
#define _strncasecmp strncasecmp
#endif

#define RTSP_PARAM_STRING_MAX 200

Boolean parseRTSPRequestString(char const* reqStr, unsigned reqStrSize,
	char* resultCmdName,
	unsigned resultCmdNameMaxSize,
	char* resultURLPreSuffix,
	unsigned resultURLPreSuffixMaxSize,
	char* resultURLSuffix,
	unsigned resultURLSuffixMaxSize,
	char* resultCSeq,
	unsigned resultCSeqMaxSize,
	char* resultSessionId,
	unsigned resultSessionIdMaxSize,
	unsigned& contentLength);

Boolean parseRangeParam(char const* paramStr, double& rangeStart, double& rangeEnd, char*& absStartTime, char*& absEndTime, Boolean& startTimeIsNow);
Boolean parseRangeHeader(char const* buf, double& rangeStart, double& rangeEnd, char*& absStartTime, char*& absEndTime, Boolean& startTimeIsNow);

Boolean parseScaleHeader(char const* buf, float& scale);

Boolean RTSPOptionIsSupported(char const* commandName, char const* optionsResponseString);
// Returns True iff the RTSP command "commandName" is mentioned as one of the commands supported in "optionsResponseString"
// (which should be the 'resultString' from a previous RTSP "OPTIONS" request).

char const* dateHeader(); // A "Date:" header that can be used in a RTSP (or HTTP) response 

#endif
