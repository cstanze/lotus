#include "client/args.h"
#include "lotus/tcp.h"
#include "lotus/protocol.h"

int main(int argc, char **argv) {
	Arguments *args = Args_parse(argc, argv);

	if(args == NULL) {
		Args_printUsage();
		return -1;
	}

	Socket *sock = Tcp_recieve(args->addr, args->port);
	if(sock == NULL)
		return -1;

	char buf[sizeof(uint8_t) + headerSizeForOpcode(OpCode_Hello) + (strlen(args->identity) + 1)];
	char hBuf[sizeof(uint8_t) + headerSizeForOpcode(OpCode_Hello)];
	hBuf[0] = (uint8_t)OpCode_Hello;
	_store32(hBuf + sizeof(uint8_t), strlen(args->identity) + 1);
	memcpy(buf, hBuf, sizeof(hBuf));
	memcpy(buf + sizeof(hBuf), args->identity, strlen(args->identity) + 1);

	send(sock->sock, &buf, sizeof(buf), 0);

	while(true) {
		uint8_t op;
		read(sock->sock, &op, sizeof(uint8_t));

		switch(op) {
		case OpCode_HelloAck: {
			// char header[headerSizeForOpcode(op)];
			// read(sock->sock, header, headerSizeForOpcode(op));
			printf("recieved hello ack!\n");
			break;
		}
		default:
			printf("Unknown Opcode (%d)\n", op);
			return -1;
		}
	}

	return 0;
}

