#include "Hash_Table.h"
#include <iostream>
#include <string>
#include <queue>
using namespace std;


Hash_Table::Hash_Table(uint32_t size_max) {
	elements = new Hash_Element *[size_max];

	for (uint32_t i = 0; i < size_max; i++) {
		elements[i] = NULL;
	}
	this->size_max = size_max;
}

Hash_Table::~Hash_Table()
{
	delete[]elements;
}

Hash_Element * Hash_Table::Get(uint32_t index)
{
	if (index >= size_max)
	{
		cout << " Index to big " << index;
		return NULL;
	}
	return elements[index];
}

unsigned int Hash_Table::hash(const string& k)
{
	uint32_t value = 0;
	for (uint32_t i = 0; i < k.length(); i++)
		value = 37 * value + k[i];
	return value;
}

void Hash_Table::Print() {
	for (uint32_t i = 0; i < this->size_max; i++)
		if (!(this->elements[i] == NULL))
		{
//			cout << this->elements[i]->Get_Hash_Key() << endl;
			this->elements[i]->Print_Hash_Key();
		}
}

int Hash_Table::find_index(const string& key, bool override_duplicate_key = true) {
	unsigned int h = hash(key) % size_max, offset = 0, index;

	while (offset < size_max) {
		index = (h + offset) % size_max;

		// empty index for new entry with key `key`
		// or find the index of key `key` in hash table
		// if `override_duplicate_key` is `false`, return a new, unused index, used in DictionaryADT
		if (this->elements[index] == NULL)
		{
			return index;
		}
		if ((override_duplicate_key && *(this->elements[index]->Get_Hash_Key()) == key))
			return index;

		offset++;
	}
	return -1;
}

void Hash_Table::Insert(const Hash_Element * element) {
	string * key = element->Get_Hash_Key();
	int index = find_index(*key);
	if (index == -1) {
		cerr << "Table is full!" << endl;
		return;
	}

	(this->elements[index]) = (Hash_Element *)element;
}

Hash_Element* Hash_Table::Find(const string* key) {
	int32_t index = find_index(*key);

	return (this->elements[index]);
}

int32_t Hash_Table::Remove(const Hash_Element * element) {
	int index = find_index(*(element->Get_Hash_Key()));
	if (index == -1)
	{
		return index;
	}

	this->elements[index] = NULL;

	return index;
}
