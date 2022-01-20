#ifndef _STRDUP_HH
#define _STRDUP_HH


// A C++ equivalent to the standard C routine "strdup()".
// This generates a char* that can be deleted using "delete[]"
// Header

#include <string.h>

char* strDup(char const* str);
// Note: strDup(NULL) returns NULL

char* strDupSize(char const* str);
// Like "strDup()", except that it *doesn't* copy the original.
// (Instead, it just allocates a string of the same size as the original.)

char* strDupSize(char const* str, size_t& resultBufSize);
// An alternative form of "strDupSize()" that also returns the size of the allocated buffer.

#endif
