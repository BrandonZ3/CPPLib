#include "SMTP.h"  

//SMTPRequest
SMTPRequest::SMTPRequest(char* buffer)
{
	PointerList* myArray = PointerList::SplitString(buffer, "\r\n");
	PointerList* command = PointerList::SplitString((char*)myArray->items[0], " ");
	if (
		Strings::Contains((char*)command->items[0], "HELO") ||
		Strings::Contains((char*)command->items[0], "MAIL") ||
		Strings::Contains((char*)command->items[0], "RCPT") ||
		Strings::Contains((char*)command->items[0], "DATA") ||
		Strings::Contains((char*)command->items[0], "SEND") ||
		Strings::Contains((char*)command->items[0], "SOML") ||
		Strings::Contains((char*)command->items[0], "SAML") ||
		Strings::Contains((char*)command->items[0], "RSET") ||
		Strings::Contains((char*)command->items[0], "VRFY") ||
		Strings::Contains((char*)command->items[0], "EXPN") ||
		Strings::Contains((char*)command->items[0], "HELP") ||
		Strings::Contains((char*)command->items[0], "NOOP") ||
		Strings::Contains((char*)command->items[0], "QUIT") ||
		Strings::Contains((char*)command->items[0], "TURN"))
	{
		this->method = (char*)command->items[0];
	}
	myArray->FreeEverything();
	delete myArray;
	command->FreeListBuffer();
	delete command;
}

SMTPRequest::~SMTPRequest()
{
	free(this->method);
}
