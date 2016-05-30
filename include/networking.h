#ifndef __NETWORKING_H
#define __NETWORKING_H

#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>

int setup_sock (const char *host, int port, struct sockaddr_in *sin);
int tcp_connect (int sock, struct sockaddr_in *sin);
int tcp_send (int sock, const char *msg, size_t nb);
int tcp_recv (int sock, char *buffer);

#endif
