#ifndef __SORT_ARRAY__H__
#define __SORT_ARRAY__H__
#pragma once
#include "types.h"
#include "defs.h"
#include "Sort_Element.h"

class Sort_Array
{
public:
	Sort_Array(CMP_TYPE_t type, bool allow_duplicate, uint16_t arr_size, uint16_t elem_size);
	~Sort_Array();

	int32_t Search(uint8_t * key) const;
	int16_t Insert(const Sort_Element* elem);
	int16_t Delete(uint8_t* key);
	void Delete_last();
	void Print() const;
	uint16_t Get_Num_Elems() const;
	Sort_Element* Get_Elem(uint16_t index) const;

private:
	CMP_TYPE_t type;
	uint16_t elem_size;
	uint16_t max_elements;
	uint16_t cur_element_num;
	Sort_Element** arr;
	bool allow_duplicate;

	int32_t search(int32_t low, int32_t high, uint8_t* key) const;

};

#endif


