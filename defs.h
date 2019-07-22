#pragma once

#ifndef __DEFS__H__
#define __DEFS__H__

#define BLOXROUTE_MAGIC_NUM 12345
#define BLOCKCHAIN_MSG_BLOCK "block"
#define HASH_SIZE_BYTES 32

typedef enum
{
	CMP_BUFF = 0,
	CMP_INT = 1
} CMP_TYPE_t;

#define NUM_LARGEST_TRANSACTIONS 100

#endif

