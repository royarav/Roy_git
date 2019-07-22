#include "Block_Msg.h"
#include <string.h>

Block_Msg::Block_Msg()
{
	Block_Msg::version = 0;
	memset(Block_Msg::prev_block, 0, sizeof(Block_Msg::prev_block));
	memset(Block_Msg::merkle_root, 0, sizeof(Block_Msg::merkle_root));
	Block_Msg::timestamp = 0;
	Block_Msg::bits = 0;
	Block_Msg::nonce = 0;
}
	
void Block_Msg::Parse(const uint8_t * buffer)
{
		//	memcpy(buffer)
	const uint8_t* p = buffer;

	Block_Msg::version = read_be32(p);
	p += sizeof(uint32_t);
	memcpy(Block_Msg::prev_block, p, sizeof(Block_Msg::prev_block));
	p += sizeof(Block_Msg::prev_block);
	memcpy(Block_Msg::merkle_root, p, sizeof(Block_Msg::merkle_root));
	p += sizeof(Block_Msg::merkle_root);
	Block_Msg::timestamp = read_be32(p);
	p += sizeof(uint32_t);
	Block_Msg::bits = read_be32(p);
	p += sizeof(uint32_t);
	Block_Msg::nonce = read_be32(p);
	p += sizeof(uint32_t);

	Block_Msg::transaction_count = parse_varint(&p);
	Block_Msg::block_msg_length = p - buffer;
}

uint16_t Block_Msg::Get_Transactions_Count() const
{
	return (uint16_t)(Block_Msg::transaction_count);
}

uint32_t Block_Msg::Get_Block_Msg_Length()
{
	return Block_Msg::block_msg_length;
}


