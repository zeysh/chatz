#ifndef __NETWORKING_H
#define __NETWORKING_H

#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>
#include <pthread.h>

int sock_open(const char *host, int port);
void sock_close(int fd);
ssize_t sock_send(int fd, const char *buff);
ssize_t sock_recv(int fd, char *buff);

#endif
