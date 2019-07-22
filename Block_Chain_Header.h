#pragma once
#ifndef __BLOCKCHAIN_HEADER__H__
#define __BLOCKCHAIN_HEADER__H__

#include "types.h"

class Block_Chain_Header
{
public:
	Block_Chain_Header();
	void Parse(const char* buffer);

	bool Check_Header() const;
	void Show() const;
	uint32_t Get_Block_Chain_Header_Length() const;

private:
	uint32_t magic_id;
	uint8_t command[12];
	uint32_t length;
	uint32_t checksum;
	uint32_t block_chain_header_length;

};

#endif


