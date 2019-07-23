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
	this->arr[mid]->Get_Elem(this->type, &elem_key);
	int res = memcmp(elem_key, key, this->elem_size);
	if (res == 0)
	{
		return mid;
	}
	if (res < 0)
	{
		return this->search((mid + 1), high, key);
	}
	return this->search(low, (mid - 1), key);
}

int32_t Sort_Array::Search(uint8_t* key) const
{
	return this->search(0, this->cur_element_num - 1, key);
}

int16_t Sort_Array::Insert(Sort_Element* elem)
{
	if (this->cur_element_num >= this->max_elements)
		return -1;

	uint8_t* key = NULL;
	elem->Get_Elem(this->type, &key);
	int res = this->search(0, this->cur_element_num - 1, key);
	if ((res != -1) && (this->allow_duplicate == false) )
	{
		return 0;
	}

	int i;
	for (i = this->cur_element_num - 1; i >= 0; i--)
	{
		uint8_t* elem_key = NULL;
		this->arr[i]->Get_Elem(this->type, &elem_key);
		res = memcmp(key, elem_key, this->elem_size);
		if (res <= 0)
		{
			this->arr[i + 1] = this->arr[i];
		}
		else
		{
			break;
		}
	}
	this->arr[i + 1] = elem;
	this->cur_element_num++;

	return 0;
}

/* Function to delete an element */
int16_t Sort_Array::Delete(uint8_t* key)
{
	// Find position of element to be deleted 
	int pos = search( 0, this->cur_element_num - 1, key);

	if (pos == -1)
	{
		printf("Element not found");
		return -1;
	}

	// Deleting element 
	int i;
	for (i = pos; i < this->cur_element_num; i++)
		this->arr[i] = this->arr[i + 1];

	this->cur_element_num--;
	return 0;
}

void Sort_Array::Print() const
{
	for (int i = 0; i < this->cur_element_num; i++)
	{
		this->arr[i]->Print_Elem();
	}

}

Sort_Array::Sort_Array(CMP_TYPE_t type, bool allow_duplicate, uint16_t arr_size, uint16_t elem_size)
{
	this->type = type;
	this->allow_duplicate = allow_duplicate;
	this->max_elements = arr_size;
	this->cur_element_num = 0;
	this->arr = new Sort_Element *[arr_size];
	this->elem_size = elem_size;
}

Sort_Array::~Sort_Array()
{
	delete this->arr;
}

uint16_t Sort_Array::Get_Num_Elems() const
{
	return this->cur_element_num;
}

Sort_Element* Sort_Array::Get_Elem(uint16_t index) const
{
	if (index >= this->cur_element_num)
	{
		cout << "Invalid index\n";
		return NULL;
	}
	return this->arr[index];
}
