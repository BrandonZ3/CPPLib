#include "Command.h"  


//CommandFlag
CommandFlag::CommandFlag(char* key)
{
	this->key = key;
	this->value = NULL;
}

CommandFlag::CommandFlag(char* key, char* value)
{
	this->key = key;
	this->value = value;
}

CommandFlag::~CommandFlag()
{
	free(this->key);
	if (this->value)
	{
		free(this->value);
	}
}

//CommandFlags
CommandFlags::CommandFlags(unsigned int initialcount)
{
	this->size = initialcount;
	this->items = (CommandFlag**)malloc(this->size * sizeof(CommandFlag*));
}

int CommandFlags::Add(CommandFlag* flag)
{
	if (this->count + 1 == this->size)
	{
		this->size *= 2;

		CommandFlag** test = (CommandFlag**)realloc(this->items, this->size * sizeof(CommandFlag*));

		if (test)
		{
			this->items = test;
			this->items[this->count] = flag;
			this->count += 1;
			return this->count - 2;
		}
		else
			return -1;
	}
	else
	{
		this->items[this->count] = flag;
		this->count += 1;
	}
}

void CommandFlags::FreeEverything()
{
	for (int i = 0; i < this->count; i++)
	{
		delete this->items[i];
	}
	free(items);
	items = NULL;
}

void CommandFlags::Remove(int index)
{
	if (index <= this->count - 1 && index > -1)
	{
		for (int i = 1; i + index < this->count; i++)
		{
			this->items[index + (i - 1)] = this->items[index + i];
		}
		this->count--;
	}
}

void CommandFlags::RemoveAndFree(int index)
{
	if (index <= this->count - 1 && index > -1)
	{
		this->items[index]->~CommandFlag();
		delete this->items[index];
		for (int i = 1; i + index < this->count; i++)
		{
			this->items[index + (i - 1)] = this->items[index + i];
		}
		this->count--;
	}
}

CommandFlags::~CommandFlags()
{
	FreeEverything();
}

//Command
Command::Command(char* commandRaw)
{
	flags = new CommandFlags(10);
	arguments = new PointerList();
	IntegerList* locations = new IntegerList(100);

	size_t stringLen = strlen(commandRaw);

	size_t start = -1;
	size_t end = -1;
	bool isString = false;

	for (size_t i = 0; i < stringLen; i++)
	{
		bool whitespace = (commandRaw[i] == 0x09 || commandRaw[i] == 0x0A || commandRaw[i] == 0x0D || commandRaw[i] == 0x20);

		if (start == -1 && !whitespace)
		{
			if ((commandRaw[i] == 0x22 || commandRaw[i] == 0x27))
			{
				start = i + 1;
				isString = true;
			}
			else
			{
				start = i;
			}
		}

		if (start != -1 && (whitespace || i == stringLen - 1))
		{
			if (isString)
			{
				if (i == stringLen - 1 && !whitespace)
					i++;
				if ((commandRaw[i - 1] == 0x22 || commandRaw[i - 1] == 0x27) && commandRaw[i - 2] != '\\')
				{
					end = i - 2;
				}
			}
			else
			{
				if (i == stringLen - 1)
				{
					if (whitespace)
						end = i - 1;
					else
						end = i;
				}
				else
					end = i - 1;
			}
		}

		if (start != -1 && end != -1)
		{
			locations->Add(start);
			locations->Add(end);
			start = -1;
			end = -1;
			isString = false;
		}
	}

	size_t flagstofill = 0;

	if (locations->count % 2 == 0)
		for (size_t i = 0; i < locations->count; i += 2)
		{
			int length = locations->buffer[i + 1] - locations->buffer[i];
			length++;

			char* newString = (char*)malloc(length + 1);
			newString[length] = 0;
			size_t pos = 0;

			for (size_t x = locations->buffer[i]; x < (locations->buffer[i + 1] + 1); x++)
			{
				newString[pos] = commandRaw[x];
				pos++;
			}

			if (command == NULL)
			{
				command = newString;
			}
			else
			{
				if (newString[0] == 0x2D)
				{
					for (int i = 1; i < length; i++)
					{
						char* nnS = (char*)malloc(3);
						nnS[0] = '-';
						nnS[1] = newString[i];
						nnS[2] = 0;

						flags->Add(new CommandFlag(nnS));
						flagstofill++;
					}

					free(newString);
				}
				else if (flagstofill > 0)
				{
					for (size_t x = 0; x < flags->count; x++)
					{
						if (flags->items[x]->value == NULL)
						{
							flags->items[x]->value = newString;
							flagstofill--;
							break;
						}
					}
				}
				else
				{
					arguments->AddPointer(newString);
				}
			}
		}

	delete locations;
}

Command::~Command()
{
	if (command)
		free(command);

	if (arguments)
	{
		arguments->FreeEverything();
		delete arguments;
	}

	if (flags)
	{
		delete flags;
	}
}
