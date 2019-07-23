#include "Transaction_Output_Msg.h"
#include <string.h>

Transaction_Output_Msg::Transaction_Output_Msg()
{
	this->value = 0;
	this->pkt_script_length = 0;
	this->pkt_script = NULL;
	this->payload = NULL;
}

Transaction_Output_Msg::~Transaction_Output_Msg()
{

}

void Transaction_Output_Msg::Parse(const uint8_t* buffer)
{
	const uint8_t* p = buffer;

	this->value = read_be32(p);
	p += sizeof(uint32_t);
	this->value <<= 32;
	this->value |= read_be32(p);
	p += sizeof(uint32_t);

	this->pkt_script_length = parse_varint(&p);
	// just skip
	p += this->pkt_script_length;

	this->payload = p;

}

const uint8_t* Transaction_Output_Msg::Get_Payload()
{
	return this->payload;
}

