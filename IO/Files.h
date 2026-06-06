#pragma once 
#include <Windows.h>
#include <stdio.h>
#include <stdint.h>

#include "../Containers/DBuffer.h"
#include "../Base/Strings.h"

class Files
{
public:
	static bool FileExists(char* fileName); 

	static DBuffer* ReadFile(char* fileName);

    static DBuffer* ReadFile(char* filepath, const char* readmode, size_t limit)
    {
        DBuffer* output = new DBuffer(4096);

        FILE* file;

        fopen_s(&file, filepath, readmode);

        if (file)
        {
            size_t fsize = GetFileSize(file);

            if (limit > fsize)
                ReadFile(file, output);
        }

        fclose(file);

        return output;
    }

	static int ReadFile(FILE* file, DBuffer* buffer);

	static int ReadFile(FILE* file, DBuffer* buffer, uint64_t byteLength, long byteOffset);

	static int WriteFile(char* fileName, struct DBuffer* file); 

	static int WriteFile(FILE* file, DBuffer* buffer);

	static size_t AppendFile(char* filepath, DBuffer* buffer);

	static unsigned long long GetFileSize(FILE* file); 

	static char* GetFileType(const char* path); 
};
