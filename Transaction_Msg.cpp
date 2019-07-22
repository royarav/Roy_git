#include "Transaction_Msg.h"
#include "Sha256.h"
#include <iostream>

using namespace std;

Transaction_Msg::Transaction_Msg(uint32_t block_offset, uint32_t sequence)
{
	Transaction_Msg::sequence = sequence;
	Transaction_Msg::block_offset = block_offset;
	Transaction_Msg::trasnaction_input_count = 0;
	Transaction_Msg::input_msgs = NULL;
	Transaction_Msg::trasnaction_output_count = 0;
	Transaction_Msg::output_msgs = NULL;
	Transaction_Msg::lock_time = 0;
	Transaction_Msg::length = 0;
	Transaction_Msg::large = 0;
}

void Transaction_Msg::Parse(const uint8_t* buffer)
{
	const uint8_t* p = buffer;

	Transaction_Msg::version = read_be32(p);
	p += sizeof(uint32_t);

	Transaction_Msg::trasnaction_input_count = parse_varint(&p);

  	Transaction_Msg::input_msgs = new Transaction_Input_Msg[(uint16_t)Transaction_Msg::trasnaction_input_count];
	for (uint16_t i = 0; i < Transaction_Msg::trasnaction_input_count; i++)
	{
		Transaction_Msg::input_msgs[i].Parse(p);
//		Transaction_Msg::input_msgs[i].Get_Hash(Transaction_Msg::hash);
		p = Transaction_Msg::input_msgs[i].Get_Payload();
	}

	Transaction_Msg::trasnaction_output_count = parse_varint(&p);

	Transaction_Msg::output_msgs = new Transaction_Output_Msg[(uint16_t)Transaction_Msg::trasnaction_output_count];
	for (uint16_t i = 0; i < Transaction_Msg::trasnaction_output_count; i++)
	{
		Transaction_Msg::output_msgs[i].Parse(p);
		p = Transaction_Msg::output_msgs[i].Get_Payload();
	}

	Transaction_Msg::lock_time = read_be32(p);
	p += sizeof(uint32_t);
	Transaction_Msg::length = p - buffer;
	Transaction_Msg::large = false;
		
//	delete Transaction_Msg::input_msgs;
//	delete Transaction_Msg::output_msgs;
}

void Transaction_Msg::Calc_Hash(const uint8_t* buffer)
{
	uint8_t first_sha[HASH_SIZE_BYTES];
	SHA256(buffer, Transaction_Msg::length, first_sha);
	SHA256(first_sha, sizeof(first_sha), Transaction_Msg::hash);
}

uint32_t Transaction_Msg::Get_Length() const
{
	return Transaction_Msg::length;
}

void Transaction_Msg::Print_Hash() const
{
	for (uint32_t i = 0; i < sizeof(Transaction_Msg::hash); i++)
	{
		cout << hex << int(Transaction_Msg::hash[i])  << " ";
	}
	cout << endl;
}

void Transaction_Msg::Get_Elem(CMP_TYPE_t type, uint8_t** elem_p) const
{
		if (type == CMP_BUFF)
		{
			*elem_p = (uint8_t *)(Transaction_Msg::hash);
	    }
		else
		{
			*elem_p = (uint8_t*)&(Transaction_Msg::length);
		}
}

void Transaction_Msg::Print_Elem() const
{
	cout << "sequence "<< Transaction_Msg::sequence << " Block offset " << dec << Transaction_Msg::block_offset 
		<< " Transaction length " << Transaction_Msg::length << " Large = " << Transaction_Msg::large << endl;
	Transaction_Msg::Print_Hash();
}

void Transaction_Msg::Mark_Large()
{
	Transaction_Msg::large = true;
}
