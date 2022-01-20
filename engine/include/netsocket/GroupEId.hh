#ifndef _GROUPEID_HH
#define _GROUPEID_HH

#ifndef _BOOLEAN_HH
#include "Boolean.hh"
#endif

#ifndef _NET_ADDRESS_HH
#include "NetAddress.hh"
#endif

class GroupEId {
public:
	GroupEId(struct sockaddr_storage const& groupAddr, portNumBits portNum, u_int8_t ttl);
	// used for a 'source-independent multicast' group

	GroupEId(struct sockaddr_storage const& groupAddr, struct sockaddr_storage const& sourceFilterAddr, portNumBits portNum);
	// used for a 'source-specific multicast' group
	
	GroupEId(); // tmp default constructor, until "Groupsock" interface uses "sockaddr_storage"

	struct sockaddr_storage const& groupAddress() const { return fGroupAddress; }
	struct sockaddr_storage const& sourceFilterAddress() const { return fSourceFilterAddress; }

	Boolean isSSM() const;

	portNumBits portNum() const;

	u_int8_t ttl() const { return fTTL; }

private:
	void init(struct sockaddr_storage const& groupAddr, struct sockaddr_storage const& sourceFilterAddr, portNumBits portNum, u_int8_t ttl);

private:
	struct sockaddr_storage fGroupAddress; // also includes port number (in network byte order)
	struct sockaddr_storage fSourceFilterAddress;
	u_int8_t fTTL;
};

#endif
