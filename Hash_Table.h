#pragma once


#ifndef __HASH_TABLE_H__
#define __HASH_TABLE_H__

#include "types.h"
#include "Hash_Element.h"
#include <string>

using namespace std;

class Hash_Table {

public:
	Hash_Table(uint32_t size_max);
	~Hash_Table();

	Hash_Element * Find(const string* element);
	void Insert(const Hash_Element * element);
	int32_t Remove(const Hash_Element* element);
	Hash_Element * Get(uint32_t index);

	void Print();
protected:
	uint32_t hash(const string & key);

	int32_t find_index(const string & key, bool override_duplicated_key);

	Hash_Element** elements;
private:
	uint32_t size_max;
};

#endif
