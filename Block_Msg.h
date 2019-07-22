#pragma once
#ifndef __BLOCK_MSG__H__
#define __BLOCK_MSG__H__

#include "types.h"

class Block_Msg
{
public:
	Block_Msg();
	void Parse(const uint8_t* buffer);

	uint16_t Get_Transactions_Count() const;
	uint32_t Get_Block_Msg_Length();

private:
	uint32_t version;
	uint8_t prev_block[32];
	uint8_t merkle_root[32];
	uint32_t timestamp;
	uint32_t bits;
	uint32_t nonce;
	uint64_t transaction_count;
	uint32_t block_msg_length;
};

#endif

