#ifndef __NETWORKING_H
#define __NETWORKING_H

#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>

int _sock;
struct sockaddr_in _sin;

#endif
