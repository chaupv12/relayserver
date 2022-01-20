#ifndef _IO_HANDLERS_HH
#define _IO_HANDLERS_HH

#ifndef _NET_INTERFACE_HH
#include "NetInterface.hh"
#endif

// Handles incoming data on sockets:
void socketReadHandler(Socket* sock, int mask);

#endif
