#pragma once 
#include <Windows.h>
#include <stdint.h>

#include "DBuffer.h"

class RDBuffer
{
private:
	DBuffer* buffer = NULL;
	RDBuffer(RDBuffer&&) = delete;
	RDBuffer() = delete;
	uint64_t position = 0;
public:
	RDBuffer(DBuffer* buffer);

	bool SetPosition(uint64_t position);

	uint64_t GetPosition();

	bool ShiftPosition(int64_t count);

	bool ReadBytes(unsigned char** output, uint64_t count);

	bool ReadQWord(uint64_t* output);

	bool ReadDWord(uint32_t* output);

	bool ReadWord(uint16_t* output);

	bool ReadByte(uint8_t* output);

	bool ReadString(char** output, int length);
};
