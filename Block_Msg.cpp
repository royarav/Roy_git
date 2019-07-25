#include "Block_Msg.h"
#include <string.h>

Block_Msg::Block_Msg()
{
	this->version = 0;
	memset(this->prev_block, 0, sizeof(this->prev_block));
	memset(this->merkle_root, 0, sizeof(this->merkle_root));
	this->timestamp = 0;
	this->bits = 0;
	this->nonce = 0;
}
	
void Block_Msg::Parse(const uint8_t * buffer)
{
	const uint8_t* p = buffer;

	this->version = read_be32(p);
	p += sizeof(uint32_t);
	memcpy(this->prev_block, p, sizeof(this->prev_block));
	p += sizeof(this->prev_block);
	memcpy(this->merkle_root, p, sizeof(this->merkle_root));
	p += sizeof(this->merkle_root);
	this->timestamp = read_be32(p);
	p += sizeof(uint32_t);
	this->bits = read_be32(p);
	p += sizeof(uint32_t);
	this->nonce = read_be32(p);
	p += sizeof(uint32_t);

	this->transaction_count = parse_varint(&p);
	this->block_msg_length = p - buffer;
}

uint16_t Block_Msg::Get_Transactions_Count() const
{
	return (uint16_t)(this->transaction_count);
}

uint32_t Block_Msg::Get_Block_Msg_Length()
{
	return this->block_msg_length;
}


