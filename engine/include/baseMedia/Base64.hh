#ifndef _BASE64_HH
#define _BASE64_HH

#ifndef _BOOLEAN_HH
#include "Boolean.hh"
#endif

unsigned char* base64Decode(char const* in, unsigned& resultSize,
			    Boolean trimTrailingZeros = True);
    // returns a newly allocated array - of size "resultSize" - that
    // the caller is responsible for delete[]ing.

unsigned char* base64Decode(char const* in, unsigned inSize,
			    unsigned& resultSize,
			    Boolean trimTrailingZeros = True);
    // As above, but includes the size of the input string (i.e., the number of bytes to decode) as a parameter.
    // This saves an extra call to "strlen()" if we already know the length of the input string.

char* base64Encode(char const* orig, unsigned origLength);
    // returns a 0-terminated string that
    // the caller is responsible for delete[]ing.

#endif
