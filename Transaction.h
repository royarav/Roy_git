#pragma once

#ifndef __TRANSACTION__H__
#define __TRANSACTION__H__

#include "types.h"
#include "Sort_Element.h"
#include "Hash_Element.h"
#include "Transaction_Input_Msg.h"
#include "Transaction_Output_Msg.h"

class Transaction : public Sort_Element, Hash_Element
{
public:
	Transaction(uint32_t block_offset, uint32_t sequence);
	~Transaction();
	void Parse(const uint8_t* buffer);
	uint32_t Get_Length() const;
	void Mark_Large();
	void Calc_Hash(const uint8_t* buffer);
	void Print_Hash() const;
	virtual void Get_Elem(CMP_TYPE_t type, uint8_t** elem_p) const;
	virtual void Print_Elem() const;
	virtual void Print_Hash_Key() const;
	virtual string * Get_Hash_Key() const;

private:
	uint32_t sequence;
	uint32_t block_offset;
	uint32_t version;
	uint64_t trasnaction_input_count;
	Transaction_Input_Msg* input_msgs;
	uint64_t trasnaction_output_count;
	Transaction_Output_Msg* output_msgs;
	uint32_t lock_time;
	int32_t elem_length;
	uint32_t length;
	uint8_t hash[HASH_SIZE_BYTES + 1];
	string * hash_key;
	bool large;

};

#endif



