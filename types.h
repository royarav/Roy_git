#pragma once
#ifndef __TYPES__H__
#define __TYPES__H__

#include <cstdint>

#define read_be16( buff ) (((uint16_t)buff[0]) | ((uint16_t)buff[1]) << 8 )
#define read_be32( buff ) (((uint8_t *)buff)[0] | ((((uint8_t *)buff)[1]) << 8) | ((((uint8_t *)buff)[2]) << 16) | ((((uint8_t*)buff)[3]) << 24 ))

typedef uint8_t hash_t[32];

inline uint64_t parse_varint( const uint8_t ** p)
{
	uint64_t result = 0;
	switch (**p)
	{
	case 0xff:
		(*p)++;
		result = read_be32((*p));
		(*p) += sizeof(uint32_t);
		result <<= 32;
		result |= read_be32((*p));
		(*p) += sizeof(uint32_t);
		break;

	case 0xfe:
		(*p)++;
		result = read_be32((*p));
		(*p) += sizeof(uint32_t);
		break;

	case 0xfd:
		(*p)++;
		result = read_be16((*p));
		(*p) += sizeof(uint16_t);
		break;

	default:
		result = **p;
		(*p)++;
		break;
	}

	return result;
}

#endif



