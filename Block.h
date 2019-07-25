#pragma once
#ifndef __BLOCK__H__
#define __BLOCK__H__

#include "types.h"
#include "Sort_Array.h"
#include "Hash_Table.h"

class Block
{
public:

	// Default Constructor 
	Block(const char* block_file_path);
	~Block();

	int16_t Read_Block_To_Mem();
	void Parse();
	void Show_Transactions() const;
	void Show_Largest_Transactions() const;
	void Show_Transaction_By_Hash(uint8_t * hash) const;

private:
	const char* file_path;
	const uint8_t* buffer;
    uint32_t num_transactions;
//	Sort_Array* transactions_arr;
	Hash_Table* transactions_table;
	Sort_Array* largest_transactions_arr;
	uint32_t Get_File_Size();

};

#endif


