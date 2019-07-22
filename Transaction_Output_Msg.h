#pragma once
#ifndef __TRANSACTION_OUTPUT_MSG__H__
#define __TRANSACTION_OUTPUT_MSG__H__

#include "types.h"

class Transaction_Output_Msg
{
public:
	Transaction_Output_Msg();
	~Transaction_Output_Msg();
	void Parse(const uint8_t* buffer);
	const uint8_t* Get_Payload();


private:

	uint64_t value;
	uint64_t pkt_script_length;
	uint8_t* pkt_script;
	const uint8_t* payload;
};

#endif



