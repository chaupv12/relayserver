#ifndef _GROUPSOCK_HELPER_HH
#define _GROUPSOCK_HELPER_HH

#ifndef _NET_ADDRESS_HH
#include "NetAddress.hh"
#endif

int setupDatagramSocket(BaseEnv& env, Port port, int domain);
int setupStreamSocket(BaseEnv& env, Port port, int domain, Boolean makeNonBlocking = True, Boolean setKeepAlive = False);

int readSocket(BaseEnv& env, int socket, unsigned char* buffer, unsigned bufferSize, struct sockaddr_storage& fromAddress /*set only if we're a datagram socket*/);

Boolean writeSocket(BaseEnv& env, int socket, struct sockaddr_storage const& addressAndPort, u_int8_t ttlArg, unsigned char* buffer, unsigned bufferSize);

Boolean writeSocket(BaseEnv& env, int socket, struct sockaddr_storage const& addressAndPort, unsigned char* buffer, unsigned bufferSize);
// An optimized version of "writeSocket" that omits the "setsockopt()" call to set the TTL.

void ignoreSigPipeOnSocket(int socketNum);

unsigned getSendBufferSize(BaseEnv& env, int socket);
unsigned getReceiveBufferSize(BaseEnv& env, int socket);
unsigned setSendBufferTo(BaseEnv& env, int socket, unsigned requestedSize);
unsigned setReceiveBufferTo(BaseEnv& env, int socket, unsigned requestedSize);
unsigned increaseSendBufferTo(BaseEnv& env, int socket, unsigned requestedSize);
unsigned increaseReceiveBufferTo(BaseEnv& env, int socket, unsigned requestedSize);

Boolean makeSocketNonBlocking(int sock);
Boolean makeSocketBlocking(int sock, unsigned writeTimeoutInMilliseconds = 0);
// A "writeTimeoutInMilliseconds" value of 0 means: Don't timeout
Boolean setSocketKeepAlive(int sock);

Boolean socketJoinGroup(BaseEnv& env, int socket, struct sockaddr_storage const& groupAddress);
Boolean socketLeaveGroup(BaseEnv&, int socket, struct sockaddr_storage const& groupAddress);

// source-specific multicast join/leave
Boolean socketJoinGroupSSM(BaseEnv& env, int socket, struct sockaddr_storage const& groupAddress, struct sockaddr_storage const& sourceFilterAddr);
Boolean socketLeaveGroupSSM(BaseEnv&, int socket, struct sockaddr_storage const& groupAddress, struct sockaddr_storage const& sourceFilterAddr);

Boolean getSourcePort(BaseEnv& env, int socket, int domain, Port& port);

ipv4AddressBits ourIPv4Address(BaseEnv& env); // in network order
ipv6AddressBits const& ourIPv6Address(BaseEnv& env);

Boolean weHaveAnIPv4Address(BaseEnv& env);
Boolean weHaveAnIPv6Address(BaseEnv& env);
Boolean weHaveAnIPAddress(BaseEnv& env);
// returns True if we have either an IPv4 or an IPv6 address

// IPv4 addresses of our sending and receiving interfaces.  (By default, these
// are INADDR_ANY (i.e., 0), specifying the default interface.)
extern ipv4AddressBits SendingInterfaceAddr;
extern ipv4AddressBits ReceivingInterfaceAddr;

// Allocates a randomly-chosen IPv4 SSM (multicast) address:
ipv4AddressBits chooseRandomIPv4SSMAddress(BaseEnv& env);

// Returns a simple "hh:mm:ss" string, for use in debugging output (e.g.)
char const* timestampString();


#ifdef HAVE_SOCKADDR_LEN
#define SET_SOCKADDR_SIN_LEN(var) var.sin_len = sizeof var
#define SET_SOCKADDR_SIN6_LEN(var) var.sin6_len = sizeof var
#else
#define SET_SOCKADDR_SIN_LEN(var)
#define SET_SOCKADDR_SIN6_LEN(var)
#endif

#define MAKE_SOCKADDR_IN(var,adr,prt) /*adr,prt must be in network order*/\
    struct sockaddr_in var;\
    var.sin_family = AF_INET;\
    var.sin_addr.s_addr = (adr);\
    var.sin_port = (prt);\
    SET_SOCKADDR_SIN_LEN(var);
#define MAKE_SOCKADDR_IN6(var,prt) /*adr,prt must be in network order*/\
    struct sockaddr_in6 var;\
    memset(&var, 0, sizeof var);\
    var.sin6_family = AF_INET6;\
    var.sin6_port = (prt);\
    SET_SOCKADDR_SIN6_LEN(var);


class NoReuse {
public:
	NoReuse(BaseEnv& env);
	~NoReuse();

private:
	BaseEnv& fEnv;
};


// Define the "UsageEnvironment"-specific "groupsockPriv" structure:

struct _groupsockPriv { // There should be only one of these allocated
	HashTable* socketTable;
	int reuseFlag;
};
_groupsockPriv* groupsockPriv(BaseEnv& env); // allocates it if necessary
void reclaimGroupsockPriv(BaseEnv& env);


#if (defined(__WIN32__) || defined(_WIN32)) && !defined(__MINGW32__)
// For Windoze, we need to implement our own gettimeofday()
extern int gettimeofday(struct timeval*, int*);
#else
#include <sys/time.h>
#endif

// The following are implemented in inet.c:
extern "C" void our_srandom(int x);
extern "C" long our_random();
extern "C" u_int32_t our_random32(); // because "our_random()" returns a 31-bit number

#endif
