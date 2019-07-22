#ifndef __SORT_ELEMENT__H__
#define __SORT_ELEMENT__H__
#pragma once

#include "types.h"
#include "defs.h"

class Sort_Element
{
public:
	virtual void Get_Elem(CMP_TYPE_t type, uint8_t** elem_p) const = 0;
	virtual void Print_Elem() const = 0;
};

#endif


