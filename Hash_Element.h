#pragma once

#ifndef __HASH_ELEMENT_H__
#define __HASH_ELEMENT_H__

#include "types.h"
#include <string>

using namespace std;

class Hash_Element
{
public:
	virtual string* Get_Hash_Key() const = 0;
	virtual void Print_Hash_Key() const = 0;
};

#endif

