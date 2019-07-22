// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include "Block.h"

using namespace std;

int main()
{
	string command;
	//    std::cout << "Start block!\n";
//	"F:\\Roy\\code\\ConsoleApplication1\\sample_block_bin"

	cout << "Welcome to bloxroute" << endl;
	cout << "Please enter full path of binary block file" << endl;
	getline(cin, command);
	Block* block = new Block(command.c_str());
	int res = block->Read_Block_To_Mem();
	if (res != 0)
	{
		return res;
	}


	cout << "Parsing the block. Please wait a minute..." << endl << endl;
	block->Parse();

	while (true)
	{
		cout << "Choose from the following options:" << endl << endl << endl;
		cout << "show_transactions - prints all transactions" << endl;
		cout << "show_largest - prints 100 largest transactions" << endl;
		cout << "show_transaction_by_hash - prints a transaction by its hash value" << endl;
		cout << "exit" << endl;
		getline(cin, command);

		if (command.compare("show_transactions") == 0)
		{
			block->Show_Transactions();
		}
		else if (command.compare("show_largest") == 0)
		{
			block->Show_Largest_Transactions();
		}
		else if (command.compare("show_transaction_by_hash") == 0)
		{
			cout << "enter 32 Numbers Here:" << endl;
			uint8_t hash[32];

			for (int i = 0; i < 32; i++)
			{
				int tmp;
				cout << "Enter num" << i << endl;
				if (cin >> hex >> tmp)
				{
					hash[i] = tmp;
				}
			}
			block->Show_Transaction_By_Hash(hash);
		}
		else if (command.compare("exit") == 0)
		{
			break;
		}

	}
	delete block;
	return 0;
}

