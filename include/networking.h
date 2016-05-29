#ifndef __NETWORKING_H
#define __NETWORKING_H

#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>

int _sock;
struct sockaddr_in _sin;

int setup_sock (const char *host, int port);
int tcp_connect (void);
int tcp_send (const char *msg, size_t nb);
int tcp_recv (char *buffer);

#endif
