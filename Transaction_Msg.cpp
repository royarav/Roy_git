#include "Transaction_Msg.h"
#include "Sha256.h"
#include <iostream>

using namespace std;

Transaction_Msg::Transaction_Msg(uint32_t block_offset, uint32_t sequence)
{
	this->sequence = sequence;
	this->block_offset = block_offset;
	this->trasnaction_input_count = 0;
	this->input_msgs = NULL;
	this->trasnaction_output_count = 0;
	this->output_msgs = NULL;
	this->lock_time = 0;
	this->length = 0;
	this->elem_length = 0;
	this->large = 0;
}

void Transaction_Msg::Parse(const uint8_t* buffer)
{
	const uint8_t* p = buffer;

	this->version = read_be32(p);
	p += sizeof(uint32_t);

	this->trasnaction_input_count = parse_varint(&p);

  	this->input_msgs = new Transaction_Input_Msg[(uint16_t)this->trasnaction_input_count];
	for (uint16_t i = 0; i < this->trasnaction_input_count; i++)
	{
		this->input_msgs[i].Parse(p);
//		this->input_msgs[i].Get_Hash(this->hash);
		p = this->input_msgs[i].Get_Payload();
	}

	this->trasnaction_output_count = parse_varint(&p);

	this->output_msgs = new Transaction_Output_Msg[(uint16_t)this->trasnaction_output_count];
	for (uint16_t i = 0; i < this->trasnaction_output_count; i++)
	{
		this->output_msgs[i].Parse(p);
		p = this->output_msgs[i].Get_Payload();
	}

	this->lock_time = read_be32(p);
	p += sizeof(uint32_t);
	this->length = p - buffer;
	this->elem_length = this->length * -1;
	this->large = false;
		
//	delete this->input_msgs;
//	delete this->output_msgs;
}

void Transaction_Msg::Calc_Hash(const uint8_t* buffer)
{
	uint8_t first_sha[HASH_SIZE_BYTES];
	SHA256(buffer, this->length, first_sha);
	SHA256(first_sha, sizeof(first_sha), this->hash);
}

uint32_t Transaction_Msg::Get_Length() const
{
	return this->length;
}

void Transaction_Msg::Print_Hash() const
{
	for (uint32_t i = 0; i < sizeof(this->hash); i++)
	{
		cout << hex << int(this->hash[i])  << " ";
	}
	cout << endl;
}

void Transaction_Msg::Get_Elem(CMP_TYPE_t type, uint8_t** elem_p) const
{
		if (type == CMP_BUFF)
		{
			*elem_p = (uint8_t *)(this->hash);
	    }
		else
		{
			*elem_p = (uint8_t*)&(this->elem_length);
		}
}

void Transaction_Msg::Print_Elem() const
{
	cout << "sequence "<< this->sequence << " Block offset " << dec << this->block_offset 
		<< " Transaction length " << this->length << " Large = " << this->large << endl;
	this->Print_Hash();
}

void Transaction_Msg::Mark_Large()
{
	this->large = true;
}
