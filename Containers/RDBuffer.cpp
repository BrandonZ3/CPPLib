#include "RDBuffer.h"  

RDBuffer::RDBuffer(DBuffer* buffer)
{
	this->buffer = buffer;
}

bool RDBuffer::SetPosition(uint64_t position)
{
	if (position >= 0 && position < this->buffer->count)
	{
		this->position = position;
		return true;
	}
	return false;
}

uint64_t RDBuffer::GetPosition()
{
	return this->position;
}

bool RDBuffer::ShiftPosition(int64_t count)
{
	if (this->position + count < this->buffer->count && this->position + count > 0)
	{
		this->position += count;
		return true;
	}
	return false;
}

bool RDBuffer::ReadBytes(unsigned char** output, uint64_t count)
{
	if (output != NULL)
		if (*output == NULL)
		{
			if (this->position + count < this->buffer->count)
				*output = this->buffer->BufferOut(position, count);

			bool result = output != NULL;
			if (result)
				this->position += count;
			return result;
		}
	return false;
}

bool RDBuffer::ReadQWord(uint64_t* output)
{
	*output = *((uint64_t*)this->buffer->DataPointer(this->position));
	bool result = output != NULL;

	if (result)
		this->position += 8;
	return result;
}

bool RDBuffer::ReadDWord(uint32_t* output)
{
	*output = *((uint32_t*)this->buffer->DataPointer(this->position));
	bool result = output != NULL;

	if (result)
		this->position += 4;
	return result;
}

bool RDBuffer::ReadWord(uint16_t* output)
{
	*output = *((uint16_t*)this->buffer->DataPointer(this->position));
	bool result = output != NULL;

	if (result)
		this->position += 2;
	return result;
}

bool RDBuffer::ReadByte(uint8_t* output)
{
	*output = *((uint8_t*)this->buffer->DataPointer(this->position));
	bool result = output != NULL;

	if (result)
		this->position++;
	return result;
}

bool RDBuffer::ReadString(char** output, int length)
{
	char* string = (char*)malloc(length + 1);

	if (string != NULL)
	{
		unsigned char* stringstart = this->buffer->DataPointer(this->position);

		for (int i = 0; i < length; i++)
		{
			string[i] = stringstart[i];
		}
		string[length] = 0;

		this->position += length;
		*output = string;

		return true;
	}

	return false;
}