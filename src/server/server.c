#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "lotus/tcp.h"
#include "lotus/protocol.h"

#define sock_chk                           \
	if (vread == 0) {                        \
		struct sockaddr_in addr;               \
		socklen_t addrlen = sizeof(addr);      \
		getpeername(sock->sock,                \
								(struct sockaddr*)&addr,   \
								(socklen_t*)&addrlen       \
		);                                     \
		printf("Client disconnected: %s:%d\n", \
					inet_ntoa(addr.sin_addr),        \
					ntohs(addr.sin_port)             \
		);                                     \
		close(sock->sock);                     \
		exit(-1);                              \
	}

int main(int argc, char **argv) {
	ssize_t vread;
	Socket *sock = Tcp_serve(8080);
	if(sock == NULL)
		return -1;

	printf("Lotus Example Server accepting on port 8080\n");

	while(true) {
		// read opcode
		uint8_t op;
		vread = read(sock->sock, &op, sizeof(uint8_t));

		sock_chk

		switch(op) {
		case OpCode_Hello: {
			char header[headerSizeForOpcode(op)];
			read(sock->sock, &header, headerSizeForOpcode(op));

			uint32_t len = _load32(uint32_t, header);

			char identity[len];
			read(sock->sock, &identity, len);

			printf("connection with identity: %s\n", identity);

			uint8_t response = OpCode_HelloAck;
			send(sock->sock, &response, sizeof(uint8_t), 0);

			break;
		}
		case OpCode_Ping:
		case OpCode_Pong:
		default:
			printf("Unknown Opcode (%d)\n", op);
			return -1;
		}
	}

	return 0;
}
