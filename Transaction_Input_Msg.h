#pragma once
#ifndef __TRANSACTION_INPUT_MSG__H__
#define __TRANSACTION_INPUT_MSG__H__

#include "types.h"
#include "defs.h"

class Transaction_Input_Msg
{
public:
	Transaction_Input_Msg();
	~Transaction_Input_Msg();
	void Parse(const uint8_t* buffer);
	const uint8_t* Get_Payload() const;
	void Get_Hash( uint8_t * buffer ) const;

private:
	uint8_t hash[HASH_SIZE_BYTES];
	uint32_t index;
	uint64_t script_length;
	uint8_t* signature_script;
	uint32_t sequence;
	const uint8_t* payload;
};

#endif



