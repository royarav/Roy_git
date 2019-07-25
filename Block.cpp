#include "Block.h"
#include "Block_Chain_Header.h"
#include "Block_Msg.h"
#include "Transaction.h"
#include <fstream>
#include <iterator>
#include <algorithm>
#include <iostream>
#include <sys/stat.h>

using namespace std;

Block::Block(const char* block_file_path)
{
	this->file_path = block_file_path;

	this->transactions_table = NULL;
	this->largest_transactions_arr = NULL;
        this->num_transactions = 0;     
}

Block::~Block()
{
	if (this->transactions_table)
	{
		uint32_t i;
        for( i = 0; i < this->num_transactions; i++ )
		{
			Transaction* transaction = (Transaction*)this->transactions_table->Get(i);
			if(transaction)
			{
				delete transaction;
			}
        }
		delete this->transactions_table;
	}

	if (this->largest_transactions_arr)
	{
		delete this->largest_transactions_arr;
	}
	if (this->buffer)
	{
		delete []this->buffer;
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
    delete bch;
	Block_Msg* block_msg = new Block_Msg();
	block_msg->Parse(position + block_offset);
	// allocate hash sort arrays for the transactions:
	// 1. hash table. key = hash
	// 2. sort array. key = transaction length
	this->num_transactions = block_msg->Get_Transactions_Count();
	this->transactions_table = new Hash_Table(this->num_transactions);
	this->largest_transactions_arr = new Sort_Array(CMP_INT, true, NUM_LARGEST_TRANSACTIONS, sizeof(uint32_t));
	block_offset += block_msg->Get_Block_Msg_Length();
    delete block_msg;
	// parse all transactions in the block
	for (uint32_t i = 0; i < this->num_transactions; i++)
	{
	     // parse transaction calculate hash value and length and insert to sort arrays
		Transaction* transaction = new Transaction(block_offset, i);
		transaction->Parse(position + block_offset);
		transaction->Calc_Hash(position + block_offset);
		this->transactions_table->Insert((const  Hash_Element *)(transaction));
		uint32_t transaction_len = transaction->Get_Length();
		uint16_t num_elems = this->largest_transactions_arr->Get_Num_Elems();
		if (num_elems < NUM_LARGEST_TRANSACTIONS)
		{
			this->largest_transactions_arr->Insert(transaction);
		}
		else
		{
			Transaction* elem = (Transaction* )(this->largest_transactions_arr->Get_Elem(num_elems - 1));
			uint32_t transaction_length = elem->Get_Length();
			if (transaction_length < transaction_len)
			{
				this->largest_transactions_arr->Delete_last();
				this->largest_transactions_arr->Insert(transaction);
			}
		}
		block_offset += transaction_len;
	}

	// mark largest 100 transactions
	int32_t num_elements = this->largest_transactions_arr->Get_Num_Elems();
	int32_t i = num_elements - 1;
	while (i >= 0)
	{
		Sort_Element* elem = this->largest_transactions_arr->Get_Elem((uint16_t(i)));
		Transaction* transaction = (Transaction*)elem;
		transaction->Mark_Large();
		i--;
	}
	return;
}

void  Block::Show_Transactions() const
{
	this->transactions_table->Print();
}

void  Block::Show_Largest_Transactions() const
{
	int32_t num_elements = this->largest_transactions_arr->Get_Num_Elems();
	int32_t i = num_elements - 1;
	uint32_t count = 0;
	while (i >= 0)
	{
		Sort_Element* elem = this->largest_transactions_arr->Get_Elem((uint16_t(i)));
		Transaction* transaction = (Transaction*)elem;
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
	string hash_str = string((const char*)hash, HASH_SIZE_BYTES);
	Hash_Element* elem = this->transactions_table->Find(&hash_str);
	if (elem == NULL)
	{
		cout << "Hash not found" << endl;
		return;
	}

	elem->Print_Hash_Key();
}

