#include "MemoryManipulation.h"  


void MemoryManipulation::MoveBytes(uint64_t sourcePosition, uint64_t destinationPosition, uint64_t totalByteCount)
{
	if (destinationPosition < sourcePosition)
	{
		MoveBytesForward(sourcePosition, destinationPosition, totalByteCount);
	}
	else
	{
		MoveBytesReverse(sourcePosition, destinationPosition, totalByteCount);
	}
}

void MemoryManipulation::MoveBytesForward(uint64_t sourcePosition, uint64_t destinationPosition, uint64_t totalByteCount)
{
	while (totalByteCount != 0)
	{
		if (totalByteCount % 8 == 0)
		{
			*(uint64_t*)destinationPosition = *(uint64_t*)sourcePosition;
			sourcePosition += 8;
			destinationPosition += 8;
			totalByteCount -= 8;
		}
		else if (totalByteCount % 4 == 0)
		{
			*(uint32_t*)destinationPosition = *(uint32_t*)sourcePosition;
			sourcePosition += 4;
			destinationPosition += 4;
			totalByteCount -= 4;
		}
		else if (totalByteCount % 2 == 0)
		{
			*(uint16_t*)destinationPosition = *(uint16_t*)sourcePosition;
			sourcePosition += 2;
			destinationPosition += 2;
			totalByteCount -= 2;
		}
		else if (totalByteCount % 1 == 0)
		{
			*(uint8_t*)destinationPosition = *(uint8_t*)sourcePosition;
			sourcePosition += 1;
			destinationPosition += 1;
			totalByteCount -= 1;
		}
	}
}

void MemoryManipulation::MoveBytesReverse(uint64_t sourcePosition, uint64_t destinationPosition, uint64_t totalByteCount)
{
	sourcePosition += totalByteCount;
	destinationPosition += totalByteCount;
	while (totalByteCount != 0)
	{
		if (totalByteCount % 8 == 0)
		{
			sourcePosition -= 8;
			destinationPosition -= 8;
			*(uint64_t*)destinationPosition = *(uint64_t*)sourcePosition;
			totalByteCount -= 8;
		}
		else if (totalByteCount % 4 == 0)
		{
			sourcePosition -= 4;
			destinationPosition -= 4;
			*(uint32_t*)destinationPosition = *(uint32_t*)sourcePosition;
			totalByteCount -= 4;
		}
		else if (totalByteCount % 2 == 0)
		{
			sourcePosition -= 2;
			destinationPosition -= 2;
			*(uint16_t*)destinationPosition = *(uint16_t*)sourcePosition;
			totalByteCount -= 2;
		}
		else if (totalByteCount % 1 == 0)
		{
			sourcePosition -= 1;
			destinationPosition -= 1;
			*(uint8_t*)destinationPosition = *(uint8_t*)sourcePosition;
			totalByteCount -= 1;
		}
	}
}

void* MemoryManipulation::MemoryAllocate(uint64_t bytes)
{
	void* result;

	result = malloc(bytes);

	if (result != NULL)
		totalBytesAllocated += bytes;

	return result;
}

void* MemoryManipulation::MemoryReallocate(void* ptr, uint64_t oldSize, uint64_t newSize)
{
	void* result;

	result = realloc(ptr, newSize);

	if (result != NULL)
	{
		totalBytesAllocated -= oldSize;
		totalBytesAllocated += newSize;
	}

	return result;
}

void MemoryManipulation::MemoryFree(void* ptr, uint64_t currentSize)
{
	free(ptr);

	totalBytesFreed += currentSize;
}

uint64_t MemoryManipulation::GetAllocatedMemoryTotal()
{
	return totalBytesAllocated;
}

uint64_t MemoryManipulation::GetFreedMemoryTotal()
{
	return totalBytesFreed;
}