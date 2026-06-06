#pragma once 
#include <Windows.h>
#include <stdint.h>

#include "MemoryManipulation.h"

class Bytes
{
public:
	static bool MatchBytes(unsigned char* source1, uint64_t byteLength1, unsigned char* source2);

	static unsigned char* BytesFlipped(const unsigned char* source, uint64_t byteLength);

	static uint64_t BytesFlippedQWord(const unsigned char* source);

	static uint32_t BytesFlippedDWord(const unsigned char* source);

	static uint16_t BytesFlippedWord(const unsigned char* source);
};
