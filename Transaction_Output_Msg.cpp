#include "Transaction_Output_Msg.h"
#include <string.h>

Transaction_Output_Msg::Transaction_Output_Msg()
{
	Transaction_Output_Msg::value = 0;
	Transaction_Output_Msg::pkt_script_length = 0;
	Transaction_Output_Msg::pkt_script = NULL;
	Transaction_Output_Msg::payload = NULL;
}

Transaction_Output_Msg::~Transaction_Output_Msg()
{

}

void Transaction_Output_Msg::Parse(const uint8_t* buffer)
{
	const uint8_t* p = buffer;

	Transaction_Output_Msg::value = read_be32(p);
	p += sizeof(uint32_t);
	Transaction_Output_Msg::value <<= 32;
	Transaction_Output_Msg::value |= read_be32(p);
	p += sizeof(uint32_t);

	Transaction_Output_Msg::pkt_script_length = parse_varint(&p);
	// just skip
	p += Transaction_Output_Msg::pkt_script_length;

	Transaction_Output_Msg::payload = p;

}

const uint8_t* Transaction_Output_Msg::Get_Payload()
{
	return Transaction_Output_Msg::payload;
}

