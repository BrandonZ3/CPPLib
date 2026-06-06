#include "HTTP.h"  

//Header
Header::Header(char* key)
{
	this->key = key;
	this->value = new PointerList();
}

Header::Header(char* key, char* value)
{
	this->key = key;
	this->value = new PointerList();
	this->value->AddPointer(value);
}

Header::~Header()
{
	free(this->key);
	this->value->FreePointers();
	delete this->value;
}

//Headers
Headers::Headers(unsigned int initialcount)
{
	this->size = initialcount;
	this->items = (Header**)malloc(this->size * sizeof(Header*));
}

void Headers::GetHeaders(const PointerList* headers)
{
	for (int i = 0; i < headers->count; i++)
	{
		PointerList* arr = PointerList::SplitString((const char*)headers->items[i], ":");
		if (arr->count == 2)
		{
			Header* head = new Header(Strings::ToLowerString((char*)arr->items[0]), Strings::Trim((char*)arr->items[1]));
			Add(head);
		}
		arr->FreeEverything();
		delete arr;
	}
}

int Headers::Add(Header* header)
{
	if (this->count + 1 == this->size)
	{
		this->size *= 2;

		Header** test = (Header**)realloc(this->items, this->size * sizeof(Header*));

		if (test)
		{
			this->items = test;
			this->items[this->count] = header;
			this->count += 1;
			return this->count - 2;
		}
		else
			return -1;
	}
	else
	{
		this->items[this->count] = header;
		this->count += 1;
	}
}

void Headers::FreeEverything()
{
	for (int i = 0; i < this->count; i++)
	{
		delete this->items[i];
	}
	free(items);
	items = NULL;
}

void Headers::Remove(int index)
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

void Headers::RemoveAndFree(int index)
{
	if (index <= this->count - 1 && index > -1)
	{
		this->items[index]->~Header();
		delete this->items[index];
		for (int i = 1; i + index < this->count; i++)
		{
			this->items[index + (i - 1)] = this->items[index + i];
		}
		this->count--;
	}
}

Headers::~Headers()
{
	FreeEverything();
}

//HTTPRequest
HTTPRequest::HTTPRequest(char* buffer)
{
	PointerList* myArray = PointerList::SplitString(buffer, "\r\n");
	PointerList* command = PointerList::SplitString((const char*)myArray->items[0], " ");
	if (command->count == 3 && Strings::Contains((char*)command->items[0], "GET") && Strings::Contains((char*)command->items[2], "HTTP/1.1"))
	{
		this->method = (char*)command->items[0];
		this->path = (char*)command->items[1];
		this->versionHTTP = (char*)command->items[2];

		PointerList* headerOnly = myArray->CloneEverything(1, myArray->count - 1);
		headers = new Headers(10);
		headers->GetHeaders(headerOnly);
		headerOnly->FreeEverything();
		delete headerOnly;
	}
	myArray->FreeEverything();
	delete myArray;
	command->FreeListBuffer();
	delete command;
}

/*void FreeResources()
{
	free(this->versionHTTP);
	free(this->method);
	free(this->path);
	delete headers;
}*/

HTTPRequest::~HTTPRequest()
{
	free(this->versionHTTP);
	free(this->method);
	free(this->path);
	delete headers;
}

//HTTPResponse
HTTPResponse::HTTPResponse(const char* protocol)
{
	this->protocol = Strings::Clone((char*)protocol);
}

void HTTPResponse::SetStatus(unsigned short statusCode)
{
	switch (statusCode)
	{
	case(100):
	{
		this->statusDescription = "Continue";
		break;
	}
	case(101):
	{
		this->statusDescription = "Switching Protocols";
		break;
	}
	case(102):
	{
		this->statusDescription = "Processing";
		break;
	}
	case(103):
	{
		this->statusDescription = "Early Hints";
		break;
	}
	case(200):
	{
		this->statusDescription = "OK";
		break;
	}
	case(201):
	{
		this->statusDescription = "Created";
		break;
	}
	case(202):
	{
		this->statusDescription = "Accepted";
		break;
	}
	case(203):
	{
		this->statusDescription = "Non-Authoritative Information";
		break;
	}
	case(204):
	{
		this->statusDescription = "No Content";
		break;
	}
	case(205):
	{
		this->statusDescription = "Reset Content";
		break;
	}
	case(206):
	{
		this->statusDescription = "Partial Content";
		break;
	}
	case(207):
	{
		this->statusDescription = "Multi-Status";
		break;
	}
	case(208):
	{
		this->statusDescription = "Already Reported";
		break;
	}
	case(226):
	{
		this->statusDescription = "IM Used";
		break;
	}
	case(300):
	{
		this->statusDescription = "Multiple Choices";
		break;
	}
	case(301):
	{
		this->statusDescription = "Moved Permanently";
		break;
	}
	case(302):
	{
		this->statusDescription = "Found";
		break;
	}
	case(303):
	{
		this->statusDescription = "See Other";
		break;
	}
	case(304):
	{
		this->statusDescription = "Not Modified";
		break;
	}
	case(305):
	{
		this->statusDescription = "Use Proxy";
		break;
	}
	case(307):
	{
		this->statusDescription = "Temporary Redirect";
		break;
	}
	case(308):
	{
		this->statusDescription = "Permanent Redirect";
		break;
	}
	case(400):
	{
		this->statusDescription = "Bad Request";
		break;
	}
	case(401):
	{
		this->statusDescription = "Unauthorized";
		break;
	}
	case(402):
	{
		this->statusDescription = "Payment Required";
		break;
	}
	case(403):
	{
		this->statusDescription = "Forbidden";
		break;
	}
	case(404):
	{
		this->statusDescription = "Not Found";
		break;
	}
	case(405):
	{
		this->statusDescription = "Method Not Allowed";
		break;
	}
	case(406):
	{
		this->statusDescription = "Not Acceptable";
		break;
	}
	case(407):
	{
		this->statusDescription = "Proxy Authentication Required";
		break;
	}
	case(408):
	{
		this->statusDescription = "Request Timeout";
		break;
	}
	case(409):
	{
		this->statusDescription = "Conflict";
		break;
	}
	case(410):
	{
		this->statusDescription = "Gone";
		break;
	}
	case(411):
	{
		this->statusDescription = "Length Required";
		break;
	}
	case(412):
	{
		this->statusDescription = "Precondition Failed";
		break;
	}
	case(413):
	{
		this->statusDescription = "Content Too Large";
		break;
	}
	case(414):
	{
		this->statusDescription = "URI Too Long";
		break;
	}
	case(415):
	{
		this->statusDescription = "Unsupported Media Type";
		break;
	}
	case(416):
	{
		this->statusDescription = "Range Not Satisfiable";
		break;
	}
	case(417):
	{
		this->statusDescription = "Expectation Failed";
		break;
	}
	case(418):
	{
		this->statusDescription = "I'm a teapot";
		break;
	}
	case(421):
	{
		this->statusDescription = "Misdirected Request";
		break;
	}
	case(422):
	{
		this->statusDescription = "Unprocessable Content";
		break;
	}
	case(423):
	{
		this->statusDescription = "Locked";
		break;
	}
	case(424):
	{
		this->statusDescription = "Failed Dependancy";
		break;
	}
	case(425):
	{
		this->statusDescription = "Too Early";
		break;
	}
	case(426):
	{
		this->statusDescription = "Upgrade Required";
		break;
	}
	case(428):
	{
		this->statusDescription = "Precondition Required";
		break;
	}
	case(429):
	{
		this->statusDescription = "Too Many Requests";
		break;
	}
	case(431):
	{
		this->statusDescription = "Request Header Fields Too Large";
		break;
	}
	case(451):
	{
		this->statusDescription = "Unavailable For Legal Reasons";
		break;
	}
	}

	if (this->statusDescription)
		this->status = statusCode;

}

void HTTPResponse::AddHeader(const char* headerName, const char* value)
{
	Header* newHeader = new Header(Strings::Clone((char*)headerName), Strings::Clone((char*)value));
	this->headers->Add(newHeader);
}

char* HTTPResponse::GetResponse()
{
	char* output = NULL;

	if (this->headers->count > 0 && this->protocol && this->status && this->statusDescription)
	{
		char* statusConverted = Strings::UintToString(this->status);
		char* temp = Strings::Concat(protocol, " ");
		output = Strings::Concat(temp, statusConverted);
		free(statusConverted);
		free(temp);

		temp = Strings::Concat(output, " ");
		free(output);
		output = Strings::Concat(temp, statusDescription);
		free(temp);

		temp = output;
		output = Strings::Concat(output, "\r\n");
		free(temp);

		for (size_t i = 0; i < headers->count; i++)
		{
			Header* header = headers->items[i];

			if (header->key && header->value->items[0])
			{
				temp = Strings::Concat(output, header->key);
				free(output);
				output = Strings::Concat(temp, ": ");
				free(temp);
				temp = Strings::Concat(output, (char*)header->value->items[0]);
				free(output);
				output = Strings::Concat(temp, "\r\n");
				free(temp);
			}
		}

		temp = output;
		output = Strings::Concat(temp, "\r\n");
		free(temp);

		return output;
	}
	else
	{
		throw "Invalid Response Parameters";
	}
	return output;
}

HTTPResponse::~HTTPResponse()
{
	if (protocol)
		free(protocol);
	delete this->headers;
}
