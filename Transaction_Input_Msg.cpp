#include "Transaction_Input_Msg.h"
#include <string.h>

Transaction_Input_Msg::Transaction_Input_Msg()
{
	memset(this->hash, 0, sizeof(this->hash));
	this->index = 0;
	this->script_length = 0;
	memset(this->signature_script, 0, (size_t)this->script_length);
	this->sequence = 0;
	this->payload = NULL;
}

Transaction_Input_Msg::~Transaction_Input_Msg()
{

}

void Transaction_Input_Msg::Parse(const uint8_t* buffer)
{
	const uint8_t* p = buffer;

	memcpy((void *)this->hash, p, sizeof(this->hash));
	p += sizeof(this->hash);
	this->index = read_be32(p);
	p += sizeof(uint32_t);

	this->script_length = parse_varint(&p);
	// just skip
	p += this->script_length;

	this->sequence = read_be32(p);
	p += sizeof(uint32_t);
	this->payload = p;

}

const uint8_t* Transaction_Input_Msg::Get_Payload() const
{
	return this->payload;
}

void Transaction_Input_Msg::Get_Hash(uint8_t* buffer) const
{
	memcpy(buffer, this->hash, sizeof(this->hash));
}

