#ifndef _DEBUG_HH_
#define _DEBUG_HH_

#include <iostream>
#include <string>

#define Message(title, body) \
{ \
	PrintMessage(title, body, __FILE__, __LINE__); \
}

void PrintMessage(std::string title, std::string body, char *file, int line);


#endif