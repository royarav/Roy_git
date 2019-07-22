#include "Transaction_Input_Msg.h"
#include <string.h>

Transaction_Input_Msg::Transaction_Input_Msg()
{
	memset(Transaction_Input_Msg::hash, 0, sizeof(Transaction_Input_Msg::hash));
	Transaction_Input_Msg::index = 0;
	Transaction_Input_Msg::script_length = 0;
	memset(Transaction_Input_Msg::signature_script, 0, (size_t)Transaction_Input_Msg::script_length);
	Transaction_Input_Msg::sequence = 0;
	Transaction_Input_Msg::payload = NULL;
}

Transaction_Input_Msg::~Transaction_Input_Msg()
{

}

void Transaction_Input_Msg::Parse(const uint8_t* buffer)
{
	const uint8_t* p = buffer;

	memcpy((void *)Transaction_Input_Msg::hash, p, sizeof(Transaction_Input_Msg::hash));
	p += sizeof(Transaction_Input_Msg::hash);
	Transaction_Input_Msg::index = read_be32(p);
	p += sizeof(uint32_t);

	Transaction_Input_Msg::script_length = parse_varint(&p);
	// just skip
	p += Transaction_Input_Msg::script_length;

	Transaction_Input_Msg::sequence = read_be32(p);
	p += sizeof(uint32_t);
	Transaction_Input_Msg::payload = p;

}

const uint8_t* Transaction_Input_Msg::Get_Payload() const
{
	return Transaction_Input_Msg::payload;
}

void Transaction_Input_Msg::Get_Hash(uint8_t* buffer) const
{
	memcpy(buffer, Transaction_Input_Msg::hash, sizeof(Transaction_Input_Msg::hash));
}

