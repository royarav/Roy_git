#include "Block.h"
#include "Block_Chain_Header.h"
#include "Block_Msg.h"
#include "Transaction_Msg.h"
#include <fstream>
#include <iterator>
#include <algorithm>
#include <iostream>
#include <sys/stat.h>

using namespace std;

Block::Block(const char* block_file_path)
{
	this->file_path = block_file_path;

	this->transactions_arr = NULL;
	this->largest_transactions_arr = NULL;
	this->buffer = NULL;

}

Block::~Block()
{
	if (this->transactions_arr)
	{
		delete this->transactions_arr;
	}
	if (this->largest_transactions_arr)
	{
		delete this->largest_transactions_arr;
	}
	if (this->buffer)
	{
		delete this->buffer;
	}
}

// Read the file to the memory - assuming that the file is not huge
int16_t Block::Read_Block_To_Mem()
{
	std::ifstream in(this->file_path, std::ifstream::ate | std::ifstream::binary);
	long file_size = this->Get_File_Size();

	if (file_size < 0)
	{
		cout << "Invalid file size " << this->file_path;
		return -1;
	}

	// allocate buffer - assumption, I have enough memory for that
	this->buffer = new uint8_t[file_size];
	if (this->buffer == NULL)
	{
		cout << "Fail to allocate memory. size " << file_size;
		return -2;
	}
	in.seekg(0, std::ios::beg);
	in.read((char *)this->buffer, file_size);

	return 0;
}

uint32_t Block::Get_File_Size()
{
	struct stat stat_buf;
	int rc = stat(this->file_path, &stat_buf);
	return rc == 0 ? stat_buf.st_size : -1;
}

void  Block::Parse()
{
	const uint8_t* position = this->buffer;
	uint32_t block_offset = 0;
	Block_Chain_Header* bch = new Block_Chain_Header();
	
	// parse block chain header
	bch->Parse((const char*)position);
//	bch->Show();
	if (bch->Check_Header() != true)
	{
		cout << "Invalid blockchain header " << endl;
		return;
	}

	// parse the block data
	block_offset += bch->Get_Block_Chain_Header_Length();
	Block_Msg* block_msg = new Block_Msg();
	block_msg->Parse(position + block_offset);

	// allocate sort arrays for the transactions:
	// 1. holds transactions - key = hash
	// 2. holds transaction - key = transaction length
	uint16_t num_transactions = block_msg->Get_Transactions_Count();
	this->transactions_arr = new Sort_Array(CMP_BUFF, false, num_transactions, HASH_SIZE_BYTES);
	this->largest_transactions_arr = new Sort_Array(CMP_INT, true, num_transactions, sizeof(uint32_t));

	block_offset += block_msg->Get_Block_Msg_Length();
	// parse all transactions in the block
	for (uint32_t i = 0; i < num_transactions; i++)
	{
	        // parse transaction calculate hash value and length and insert to sort arrays
		Transaction_Msg* transaction = new Transaction_Msg(block_offset, i);
		transaction->Parse(position + block_offset);
		transaction->Calc_Hash(position + block_offset);
		this->transactions_arr->Insert(transaction);
		uint32_t transaction_len = transaction->Get_Length();
		this->largest_transactions_arr->Insert(transaction);
		block_offset += transaction_len;
	}

	// mark largest 100 transactions
	int32_t num_elements = this->largest_transactions_arr->Get_Num_Elems();
	int32_t i = num_elements - 1;
	uint32_t count = 0;
	while (i >= 0)
	{
		Sort_Element* elem = this->largest_transactions_arr->Get_Elem((uint16_t(i)));
		Transaction_Msg* transaction = (Transaction_Msg*)elem;
		transaction->Mark_Large();
		count++;
		if (count >= NUM_LARGEST_TRANSACTIONS)
		{
			break;
		}
		i--;
	}

	return;
}

void  Block::Show_Transactions() const
{
	this->transactions_arr->Print();
}

void  Block::Show_Largest_Transactions() const
{
	int32_t num_elements = this->largest_transactions_arr->Get_Num_Elems();
	int32_t i = num_elements - 1;
	uint32_t count = 0;
	while (i >= 0)
	{
		Sort_Element* elem = this->largest_transactions_arr->Get_Elem((uint16_t(i)));
		Transaction_Msg* transaction = (Transaction_Msg*)elem;
		transaction->Print_Elem();
		count++;
		if (count >= NUM_LARGEST_TRANSACTIONS)
		{
			break;
		}
		i--;
	}

}

void  Block::Show_Transaction_By_Hash(uint8_t * hash) const
{
	int32_t res = this->transactions_arr->Search(hash);
	if (res < 0)
	{
		cout << "Hash not found" << endl;
		return;
	}
	Sort_Element* elem = this->transactions_arr->Get_Elem((uint16_t(res)));
	elem->Print_Elem();
}

void  Block::Show_Transaction_By_Index( uint16_t index ) const
{
	Sort_Element* elem = this->transactions_arr->Get_Elem((uint16_t(index)));
	Transaction_Msg* transaction = (Transaction_Msg*)elem;
	transaction->Print_Elem();
}

