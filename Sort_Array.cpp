#include "Sort_Array.h"
#include <string.h>

#include <iostream> 
using namespace std;

int32_t Sort_Array::search(int32_t low, int32_t high, uint8_t* key) const
{
	uint8_t* elem_key = NULL;

	if (high < low)
		return -1;

	int32_t mid = (low + high) / 2; /*low + (high - low)/2;*/
	Sort_Array::arr[mid]->Get_Elem(Sort_Array::type, &elem_key);
	int res = memcmp(elem_key, key, Sort_Array::elem_size);
	if (res == 0)
	{
		return mid;
	}
	if (res < 0)
	{
		return Sort_Array::search((mid + 1), high, key);
	}
	return Sort_Array::search(low, (mid - 1), key);
}

int32_t Sort_Array::Search(uint8_t* key) const
{
	return Sort_Array::search(0, Sort_Array::cur_element_num - 1, key);
}

int16_t Sort_Array::Insert(Sort_Element* elem)
{
	if (Sort_Array::cur_element_num >= Sort_Array::max_elements)
		return -1;

	uint8_t* key = NULL;
	elem->Get_Elem(Sort_Array::type, &key);
	int res = Sort_Array::search(0, Sort_Array::cur_element_num - 1, key);
	if ((res != -1) && (Sort_Array::allow_duplicate == false) )
	{
		return 0;
	}

	int i;
	for (i = Sort_Array::cur_element_num - 1; i >= 0; i--)
	{
		uint8_t* elem_key = NULL;
		Sort_Array::arr[i]->Get_Elem(Sort_Array::type, &elem_key);
		res = memcmp(key, elem_key, Sort_Array::elem_size);
		if (res <= 0)
		{
			Sort_Array::arr[i + 1] = Sort_Array::arr[i];
		}
		else
		{
			break;
		}
	}
	Sort_Array::arr[i + 1] = elem;
	Sort_Array::cur_element_num++;

	return 0;
}

/* Function to delete an element */
int16_t Sort_Array::Delete(uint8_t* key)
{
	// Find position of element to be deleted 
	int pos = search( 0, Sort_Array::cur_element_num - 1, key);

	if (pos == -1)
	{
		printf("Element not found");
		return -1;
	}

	// Deleting element 
	int i;
	for (i = pos; i < Sort_Array::cur_element_num; i++)
		Sort_Array::arr[i] = Sort_Array::arr[i + 1];

	Sort_Array::cur_element_num--;
	return 0;
}

void Sort_Array::Print() const
{
	for (int i = 0; i < Sort_Array::cur_element_num; i++)
	{
		Sort_Array::arr[i]->Print_Elem();
	}

}

Sort_Array::Sort_Array(CMP_TYPE_t type, bool allow_duplicate, uint16_t arr_size, uint16_t elem_size)
{
	Sort_Array::type = type;
	Sort_Array::allow_duplicate = allow_duplicate;
	Sort_Array::max_elements = arr_size;
	Sort_Array::cur_element_num = 0;
	Sort_Array::arr = new Sort_Element *[arr_size];
	Sort_Array::elem_size = elem_size;
}

Sort_Array::~Sort_Array()
{
	delete Sort_Array::arr;
}

uint16_t Sort_Array::Get_Num_Elems() const
{
	return Sort_Array::cur_element_num;
}

Sort_Element* Sort_Array::Get_Elem(uint16_t index) const
{
	if (index >= Sort_Array::cur_element_num)
	{
		cout << "Invalid index\n";
		return NULL;
	}
	return Sort_Array::arr[index];
}
