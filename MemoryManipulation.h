#pragma once 
#include <Windows.h>
#include <stdint.h>

static uint64_t totalBytesAllocated;
static uint64_t totalBytesFreed;

class MemoryManipulation
{
public:
	static void MoveBytes(uint64_t sourcePosition, uint64_t destinationPosition, uint64_t totalByteCount);

	static void MoveBytesForward(uint64_t sourcePosition, uint64_t destinationPosition, uint64_t totalByteCount);

	static void MoveBytesReverse(uint64_t sourcePosition, uint64_t destinationPosition, uint64_t totalByteCount);

	static void* MemoryAllocate(uint64_t bytes);

	static void* MemoryReallocate(void* ptr, uint64_t oldSize, uint64_t newSize);

	static void MemoryFree(void* ptr, uint64_t currentSize);

	static uint64_t GetAllocatedMemoryTotal();

	static uint64_t GetFreedMemoryTotal();
};
