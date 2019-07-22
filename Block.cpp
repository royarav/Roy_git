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
	Block::file_path = block_file_path;

	Block::transactions_arr = NULL;
	Block::largest_transactions_arr = NULL;

}

Block::~Block()
{
	if (Block::transactions_arr)
	{
		delete Block::transactions_arr;
	}
	if (Block::largest_transactions_arr)
	{
		delete Block::largest_transactions_arr;
	}
}

int16_t Block::Read_Block_To_Mem()
{
	std::ifstream in(Block::file_path, std::ifstream::ate | std::ifstream::binary);
	long file_size = Block::Get_File_Size();

	if (file_size < 0)
	{
		cout << "Invalid file size " << Block::file_path;
		return -1;
	}

	// allocate buffer - assumption, I have enough memory for that
	Block::buffer = new uint8_t[file_size];
	if (Block::buffer == NULL)
	{
		cout << "Fail to allocate memory. size " << file_size;
		return -2;
	}
	in.seekg(0, std::ios::beg);
	in.read((char *)Block::buffer, file_size);

	return 0;
}

uint32_t Block::Get_File_Size()
{
	struct stat stat_buf;
	int rc = stat(Block::file_path, &stat_buf);
	return rc == 0 ? stat_buf.st_size : -1;
}

void  Block::Parse()
{
	const uint8_t* position = Block::buffer;
	uint32_t block_offset = 0;
	Block_Chain_Header* bch = new Block_Chain_Header();
	bch->Parse((const char*)position);
//	bch->Show();
	if (bch->Check_Header() != true)
	{
		cout << "Invalid blockchain header " << endl;
		return;
	}

	block_offset += bch->Get_Block_Chain_Header_Length();
	Block_Msg* block_msg = new Block_Msg();
	block_msg->Parse(position + block_offset);

	uint16_t num_transactions = block_msg->Get_Transactions_Count();
	Block::transactions_arr = new Sort_Array(CMP_BUFF, false, num_transactions, HASH_SIZE_BYTES);
	Block::largest_transactions_arr = new Sort_Array(CMP_INT, true, num_transactions, sizeof(uint32_t));

	block_offset += block_msg->Get_Block_Msg_Length();
	for (uint32_t i = 0; i < num_transactions; i++)
	{
		Transaction_Msg* transaction = new Transaction_Msg(block_offset, i);
		transaction->Parse(position + block_offset);
		transaction->Calc_Hash(position + block_offset);
		Block::transactions_arr->Insert(transaction);
		uint32_t transaction_len = transaction->Get_Length();
		Block::largest_transactions_arr->Insert(transaction);
		block_offset += transaction_len;
	}

	// mark largest 100 transactions
	int32_t num_elements = Block::largest_transactions_arr->Get_Num_Elems();
	int32_t i = num_elements - 1;
	uint32_t count = 0;
	while (i >= 0)
	{
		Sort_Element* elem = Block::largest_transactions_arr->Get_Elem((uint16_t(i)));
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
	Block::transactions_arr->Print();
}

void  Block::Show_Largest_Transactions() const
{
	int32_t num_elements = Block::largest_transactions_arr->Get_Num_Elems();
	int32_t i = num_elements - 1;
	uint32_t count = 0;
	while (i >= 0)
	{
		Sort_Element* elem = Block::largest_transactions_arr->Get_Elem((uint16_t(i)));
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
	int32_t res = Block::transactions_arr->Search(hash);
	if (res < 0)
	{
		cout << "Hash not found" << endl;
		return;
	}
	Sort_Element* elem = Block::transactions_arr->Get_Elem((uint16_t(res)));
	elem->Print_Elem();
		/*
		Sort_Element* elem = Block::transactions_arr->Get_Elem(0);
	uint8_t* p;
	elem->Get_Elem(CMP_BUFF, &p);
	INT32 res = Block::transactions_arr->Search(p);
	*/
}

void  Block::Show_Transaction_By_Index( uint16_t index ) const
{
	Sort_Element* elem = Block::transactions_arr->Get_Elem((uint16_t(index)));
	Transaction_Msg* transaction = (Transaction_Msg*)elem;
	transaction->Print_Elem();
}

