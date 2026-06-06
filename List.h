#pragma once 
#include <stdint.h>

#include "MemoryManipulation.h"

class List
{
private:
	void* items;
	uint64_t count;
	uint64_t size;
	uint64_t variableSize;
public:
	List(List&&) = delete;
	List(uint64_t variableSize);

	bool AddListItem(void* data);  // this creates a copy of what you supply

	bool RemoveListItem(uint64_t index);

	void* GetListItemPointer(uint64_t index);

	void GetListItemCopy(void* destinationOfData, uint64_t index);

	~List();
};
