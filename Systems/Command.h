#pragma once 
#include <Windows.h>

#include "../Containers/PointerList.h"
#include "../Base/Bytes.h"
#include "../Containers/IntegerList.h"

class CommandFlag
{
public:
	char* key = NULL;
	char* value = NULL;

	CommandFlag(const CommandFlag&) = delete;

	CommandFlag(char* key);

	CommandFlag(char* key, char* value);

	~CommandFlag();
};

class CommandFlags
{
public:
	CommandFlag** items = NULL;
	int count = 0;
	int size = 0;

	CommandFlags(const CommandFlags&) = delete;

	CommandFlags(unsigned int initialcount);

	int Add(CommandFlag* flag);

	void FreeEverything();

	void Remove(int index);

	void RemoveAndFree(int index);

	~CommandFlags();
};

class Command
{
public:
	char* command = NULL;
	CommandFlags* flags = NULL;
	PointerList* arguments = NULL;

	Command(const Command&) = delete;

	Command(char* commandRaw);

	~Command();
};
