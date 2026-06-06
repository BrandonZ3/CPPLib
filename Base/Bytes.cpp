#include "Bytes.h"  

bool Bytes::MatchBytes(unsigned char* source1, uint64_t byteLength1, unsigned char* source2)
{
	for (uint64_t i = 0; i < byteLength1; i++)
	{
		if (source1[i] != source2[i])
			return false;
	}
	return true;
}

unsigned char* Bytes::BytesFlipped(const unsigned char* source, uint64_t byteLength)
{
	unsigned char* output = (unsigned char*)malloc(byteLength);

	if (output != NULL)
	{
		for (uint64_t i = byteLength - 1; i >= 0; i--)
		{
			output[byteLength - (i + 1)] = source[i];
			if (i == 0)
				break;
		}
	}
	else
		return NULL;
	return output;
}

uint64_t Bytes::BytesFlippedQWord(const unsigned char* source)
{
	unsigned char* rawBytes = Bytes::BytesFlipped(source, 8);
	uint64_t data = *((uint64_t*)rawBytes);
	MemoryManipulation::MemoryFree(rawBytes, 8);
	return data;
}

uint32_t Bytes::BytesFlippedDWord(const unsigned char* source)
{
	unsigned char* rawBytes = Bytes::BytesFlipped(source, 4);
	uint32_t data = *((uint32_t*)rawBytes);
	MemoryManipulation::MemoryFree(rawBytes, 4);
	return data;
}

uint16_t Bytes::BytesFlippedWord(const unsigned char* source)
{
	unsigned char* rawBytes = Bytes::BytesFlipped(source, 2);
	uint16_t data = *((uint16_t*)rawBytes);
	MemoryManipulation::MemoryFree(rawBytes, 2);
	return data;
}