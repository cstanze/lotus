#ifndef LOTUS_TCP_UTILS_H
#define LOTUS_TCP_UTILS_H

#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

typedef struct {
	int fd;
	int sock;
	struct sockaddr_in addr;
} Socket;

static Socket *Tcp_serve(int port) {
	int opt = 1;
	Socket *s = (Socket*)malloc(sizeof(Socket));

	if((s->fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
		perror("socket failed");
		free(s);
		return NULL;
	}

	if(setsockopt(s->fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
		perror("setsockopt");
		free(s);
		return NULL;
	}

	s->addr.sin_family = AF_INET;
	s->addr.sin_addr.s_addr = INADDR_ANY;
	s->addr.sin_port = htons(port);

	if(bind(s->fd, (struct sockaddr *)&s->addr, sizeof(s->addr)) < 0) {
		perror("bind failed");
		free(s);
		return NULL;
	}

	if(listen(s->fd, 3) < 0) {
		perror("listen");
		free(s);
		return NULL;
	}

	socklen_t addrlen = sizeof(struct sockaddr_in);
	if((s->sock = accept(s->fd, (struct sockaddr*)&s->addr, &addrlen)) < 0) {
		perror("accept");
		free(s);
		return NULL;
	}

	return s;
}

static Socket *Tcp_recieve(char *address, int port) {
	Socket *s = (Socket*)malloc(sizeof(Socket));

	if((s->sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket");
		free(s);
		return NULL;
	}

	s->addr.sin_family = AF_INET;
	s->addr.sin_port = htons(port);

	if(inet_pton(AF_INET, address, &s->addr.sin_addr) <= 0) {
		printf("Invalid address\n");
		free(s);
		return NULL;
	}

	if(connect(s->sock, (struct sockaddr*)&s->addr, sizeof(s->addr)) < 0) {
		printf("Connection failed\n");
		perror("connect");
		free(s);
		return NULL;
	}

	return s;
}

#endif
