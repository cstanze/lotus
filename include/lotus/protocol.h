#ifndef LOTUS_PROTOCOL_H
#define LOTUS_PROTOCOL_H

#include <ctype.h>
#include <stdint.h>
#include <string.h>

#define _be16(x) ( \
  ((((uint16_t)x) << 8) ) | \
  ((((uint16_t)x) >> 8) ) )

#define _be32(x) ( \
  ((((uint32_t)x) << 24)               ) | \
  ((((uint32_t)x) <<  8) & 0x00ff0000U ) | \
  ((((uint32_t)x) >>  8) & 0x0000ff00U ) | \
  ((((uint32_t)x) >> 24)               ) )

#define _load16(cast, from) ((cast)( \
  (((uint16_t)((uint8_t*)(from))[0]) << 8) | \
  (((uint16_t)((uint8_t*)(from))[1])     ) ))

#define _load32(cast, from) ((cast)( \
  (((uint32_t)((uint8_t*)(from))[0]) << 24) | \
  (((uint32_t)((uint8_t*)(from))[1]) << 16) | \
  (((uint32_t)((uint8_t*)(from))[2]) <<  8) | \
  (((uint32_t)((uint8_t*)(from))[3])      ) ))

#define _store16(to, num)      \
  do                           \
  {                            \
    uint16_t val = _be16(num); \
    memcpy(to, &val, 2);       \
  } while (0)

#define _store32(to, num)      \
  do                           \
  {                            \
    uint32_t val = _be32(num); \
    memcpy(to, &val, 4);       \
  } while (0)

typedef enum {
	OpCode_Hello    = 1 << 0,
	OpCode_HelloAck = 1 << 1,
	OpCode_Ping     = 1 << 2,
	OpCode_Pong     = 1 << 3
} OpCode;

// Payload header size for OpCode, Not including opcode
static size_t headerSizeForOpcode(OpCode opcode) {
	switch(opcode) {
	case OpCode_Hello:
		return sizeof(uint32_t);
	case OpCode_HelloAck:
	case OpCode_Ping:
	case OpCode_Pong:
	default:
		return 0;
	}
}

#endif
