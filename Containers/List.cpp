#include "List.h"  

List::List(uint64_t variableSize)
{
	this->count = 0;
	this->size = variableSize * 40;
	this->variableSize = variableSize;
	this->items = MemoryManipulation::MemoryAllocate(this->size);
}

bool List::AddListItem(void* data)  // this creates a copy of what you supply
{
	if ((this->count * this->variableSize) == this->size)
	{
		void* newmem = MemoryManipulation::MemoryReallocate(this->items, this->size, this->size * 2);

		if (newmem == NULL)
		{
			return false;
		}
		this->items = newmem;
	}
	MemoryManipulation::MoveBytes((uint64_t)(data), (uint64_t)((uint64_t)this->items + (this->count * this->variableSize)), this->variableSize);
	this->count++;
	return true;
}

bool List::RemoveListItem(uint64_t index)
{
	if (index > -1 && index < this->count)
	{
		uint64_t bytesToMove = (this->count - (index + 1)) * this->variableSize;

		uint64_t startPosition = ((uint64_t)this->items) + ((index + 1) * this->variableSize);

		uint64_t endPosition = ((uint64_t)this->items) + (index * this->variableSize);

		MemoryManipulation::MoveBytes((uint64_t)startPosition, (uint64_t)endPosition, bytesToMove);

		this->count--;
		return true;
	}
	return false;
}

void* List::GetListItemPointer(uint64_t index)
{
	if (index < this->count)
	{
		return (void*)(((uint64_t)this->items) + (index * this->variableSize));
	}
	return NULL;
}

void List::GetListItemCopy(void* destinationOfData, uint64_t index)       // this creates a copy for you
{
	if (index > -1 && index < this->count)
	{
		uint64_t copyFromPosition = ((uint64_t)this->items) + (index * this->variableSize);

		MemoryManipulation::MoveBytes((uint64_t)copyFromPosition, (uint64_t)destinationOfData, this->variableSize);
	}
}

List::~List()
{
	MemoryManipulation::MemoryFree(this->items, this->size);
}