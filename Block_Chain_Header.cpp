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

	this->magic_id = read_be32(p);
	p += sizeof(uint32_t);
	memcpy(this->command, p, sizeof(this->command));
	this->command[sizeof(this->command) - 1] = '\0';
	p += sizeof(this->command);

	this->length = read_be32(p);
	p += sizeof(uint32_t);
	this->checksum = read_be32(p);
	p += sizeof(uint32_t);

	this->block_chain_header_length = (p - buffer);
}

bool Block_Chain_Header::Check_Header() const
{
	if (this->magic_id != BLOXROUTE_MAGIC_NUM)
	{
		cout << "Unexpected magic num " << this->magic_id << endl;
		return false;
	}
	if (strcmp((const char *)this->command, BLOCKCHAIN_MSG_BLOCK) != 0)
	{
		cout << "Unexpected command " << this->command << endl;
		return false;
	}
	return true;
}

void Block_Chain_Header::Show() const
{
	cout << "magic_id " << this->magic_id << endl;
	cout << "command " << this->command << endl;
	cout << "length " << this->length << endl;
	cout << "checksum " << this->checksum << endl;
}


uint32_t Block_Chain_Header::Get_Block_Chain_Header_Length() const
{
	return Block_Chain_Header::block_chain_header_length;

}
