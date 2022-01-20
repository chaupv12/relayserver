#ifndef _NET_INTERFACE_HH
#define _NET_INTERFACE_HH

#ifndef _NET_ADDRESS_HH
#include "NetAddress.hh"
#endif

class NetInterface {
public:
	virtual ~NetInterface();

	static BaseEnv* DefaultUsageEnvironment;
	// if non-NULL, used for each new interface

protected:
	NetInterface(); // virtual base class
};

class Socket : public NetInterface {
public:
	virtual ~Socket();
	void reset(); // closes the socket, and sets "fSocketNum" to -1

	virtual Boolean handleRead(unsigned char* buffer, unsigned bufferMaxSize, unsigned& bytesRead, struct sockaddr_storage& fromAddress) = 0;
	// Returns False on error; resultData == NULL if data ignored

	int socketNum() const { return fSocketNum; }

	Port port() const {
		return fPort;
	}

	BaseEnv& env() const { return fEnv; }

	static int DebugLevel;

protected:
	Socket(BaseEnv& env, Port port, int family); // virtual base class

	Boolean changePort(Port newPort); // will also cause socketNum() to change

private:
	int fSocketNum;
	BaseEnv& fEnv;
	Port fPort;
	int fFamily;
};

BaseEnv& operator<<(BaseEnv& s, const Socket& sock);

// A data structure for looking up a Socket by port:

class SocketLookupTable {
public:
	virtual ~SocketLookupTable();

	Socket* Fetch(BaseEnv& env, Port port, Boolean& isNew);
	// Creates a new Socket if none already exists
	Boolean Remove(Socket const* sock);

protected:
	SocketLookupTable(); // abstract base class
	virtual Socket* CreateNew(BaseEnv& env, Port port) = 0;

private:
	HashTable* fTable;
};

// A data structure for counting traffic:

class NetInterfaceTrafficStats {
public:
	NetInterfaceTrafficStats();

	void countPacket(unsigned packetSize);

	float totNumPackets() const { return fTotNumPackets; }
	float totNumBytes() const { return fTotNumBytes; }

	Boolean haveSeenTraffic() const;

private:
	float fTotNumPackets;
	float fTotNumBytes;
};

#endif
