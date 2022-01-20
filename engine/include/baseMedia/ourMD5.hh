#ifndef _OUR_MD5_HH
#define _OUR_MD5_HH

extern char* our_MD5Data(unsigned char const* data, unsigned dataSize, char* outputDigest);
// "outputDigest" must be either NULL (in which case this function returns a heap-allocated
// buffer, which should be later delete[]d by the caller), or else it must point to
// a (>=)33-byte buffer (which this function will also return).

extern unsigned char* our_MD5DataRaw(unsigned char const* data, unsigned dataSize,
	unsigned char* outputDigest);
// Like "ourMD5Data()", except that it returns the digest in 'raw' binary form, rather than
// as an ASCII hex string.
// "outputDigest" must be either NULL (in which case this function returns a heap-allocated
// buffer, which should be later delete[]d by the caller), or else it must point to
// a (>=)16-byte buffer (which this function will also return).

#endif
