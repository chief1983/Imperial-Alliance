#ifndef _MISC_H_
#define _MISC_H_

#include <iostream>
#include <string>

// Transform a into to a std::string
std::string IntToString(int num);

int StringToInt(std::string str);

// Translate the incoming text to real text
std::string CleanIncomingText(std::string text);

// Strip the links out
std::string StripLinks(std::string html);

// Will remove the substrings that begins with from and ends with to
std::string Strip(std::string str, std::string from, std::string to, bool once = true);

// Fix the std::string so that ' becomes ''
std::string FixApostrophe(std::string str);

// Read a file to a std::string
std::string FileToString(std::string fileName);

// Search and replace in a std::string
std::string SearchReplace(std::string str, std::string search, std::string replace, bool oneReplace = false, int pos = 0);

// Make a std::string lowercase
std::string StringToLower(std::string str);

// Print a std::string to a file
void StringToFile(std::string str, std::string file);

// Is str2 a substr for str1
bool IsSubstring(std::string str1, std::string str2);

// Checks if the std::string only consists of the english letters, the numbers 0-9 and _
bool ConsistsOnlyOf(std::string str);

// Get the std::string betwen the two positions/substrings
std::string GetString(std::string str, std::string sub1, std::string sub2);
std::string GetString(std::string str, int pos1, int pos2);

// Returns the position of the std::string in the page, if none is found -1
int FindString(std::string str, std::string search);
int FindString(std::string str, std::string search, int fromPos);

// Translate html character codes to real characters
std::string TranslateHTML(std::string str);


#endif