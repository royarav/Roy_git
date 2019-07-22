#include "Block_Chain_Header.h"
#include "defs.h"
#include <string.h>
#include <iostream>

using namespace std;

Block_Chain_Header::Block_Chain_Header()
{

}

void Block_Chain_Header::Parse(const char* buffer)
{
//	memcpy(buffer)
	const char* p = buffer;

	Block_Chain_Header::magic_id = read_be32(p);
	p += sizeof(uint32_t);
	memcpy(Block_Chain_Header::command, p, sizeof(Block_Chain_Header::command));
	Block_Chain_Header::command[sizeof(Block_Chain_Header::command) - 1] = '\0';
	p += sizeof(Block_Chain_Header::command);

	Block_Chain_Header::length = read_be32(p);
	p += sizeof(uint32_t);
	Block_Chain_Header::checksum = read_be32(p);
	p += sizeof(uint32_t);

	Block_Chain_Header::block_chain_header_length = (p - buffer);
}

bool Block_Chain_Header::Check_Header() const
{
	if (Block_Chain_Header::magic_id != BLOXROUTE_MAGIC_NUM)
	{
		cout << "Unexpected magic num " << Block_Chain_Header::magic_id << endl;
		return false;
	}
	if (strcmp((const char *)Block_Chain_Header::command, BLOCKCHAIN_MSG_BLOCK) != 0)
	{
		cout << "Unexpected command " << Block_Chain_Header::command << endl;
		return false;
	}
	return true;
}

void Block_Chain_Header::Show() const
{
	cout << "magic_id " << Block_Chain_Header::magic_id << endl;
	cout << "command " << Block_Chain_Header::command << endl;
	cout << "length " << Block_Chain_Header::length << endl;
	cout << "checksum " << Block_Chain_Header::checksum << endl;
}


uint32_t Block_Chain_Header::Get_Block_Chain_Header_Length() const
{
	return Block_Chain_Header::block_chain_header_length;

}
