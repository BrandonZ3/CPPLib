#pragma once 
#include <Windows.h>

#include "PointerList.h"
#include "Strings.h"

class Header
{
public:
	char* key = NULL;
	PointerList* value = NULL;

	Header(const Header&) = delete;
	Header(char* key);

	Header(char* key, char* value);

	~Header();
};

struct Headers
{
public:
	Header** items = NULL;
	int count = 0;
	int size = 0;

	Headers(const Headers&) = delete;

	Headers(unsigned int initialcount);

	void GetHeaders(const PointerList* headers);

	int Add(Header* header);

	void FreeEverything();

	void Remove(int index);

	void RemoveAndFree(int index);

	~Headers();
};

struct HTTPRequest
{
public:
	char* versionHTTP = NULL;
	char* method = NULL;
	char* path = NULL;
	Headers* headers = NULL;

	HTTPRequest(const HTTPRequest&) = delete;

	HTTPRequest(char* buffer);

	/*void FreeResources()
	{
		free(this->versionHTTP);
		free(this->method);
		free(this->path);
		delete headers;
	}*/

	~HTTPRequest();
};

class HTTPResponse
{
private:
	char* protocol;
	unsigned short status = 400;
	const char* statusDescription = NULL;
	Headers* headers = new Headers(10);

public:

	HTTPResponse(const HTTPResponse&) = delete;

	HTTPResponse(const char* protocol);

	void SetStatus(unsigned short statusCode);

	void AddHeader(const char* headerName, const char* value);

	char* GetResponse();

	~HTTPResponse();
};
