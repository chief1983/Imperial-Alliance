#include <windows.h>
#include <iostream>
#include <cstdio>
#include "debug.h"
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////

void PrintMessage(string title, string body, char *file, int line)
{
	//char buffer[512];

	// Prepare the message for the web
	//sprintf(buffer, "Content-type: text/html\n\n Title: %s\nLine: %d\nFile: %s\nMessage: %s", 
	//	    title, line, file, body);

	// Show the message box
	//cout << buffer << endl;;

	cout << "Content-type: text/html\n" << endl;
	cout << "Title: " << title << "<br>" << endl;
	cout << "Line: " << line << "<br>" <<  endl;
	cout << "File: " << file << "<br>" <<  endl;
	cout << "Message: " << body << "<br>" <<  endl;
}

////////////////////////////////////////////////////////////////////////////////////////