#include <fstream>
#include <sstream>
#include <algorithm>
#include <cassert>

#include "EH_Medals/stringfuncs.h"

using namespace std;


//////////////////////////////////////////////////////////////////////

std::string IntToString(int num)
{
	stringstream intStr;

	intStr << num;

	return intStr.str();
}

//////////////////////////////////////////////////////////////////////////////////////////////////

int StringToInt(std::string str)
{
	return atoi(str.c_str());
}

//////////////////////////////////////////////////////////////////////////////////////////////////

std::string CleanIncomingText(std::string text)
{
	/* Replace all ASCII values with the corresponding characters */

	text = SearchReplace(text, "+", " ");
	text = SearchReplace(text, "%25", "%");
	text = SearchReplace(text, "%0D", "");
	text = SearchReplace(text, "%09", "\t");
	text = SearchReplace(text, "%0A", "\xA");
	text = SearchReplace(text, "%20", " ");
	text = SearchReplace(text, "%2B", "+");
	text = SearchReplace(text, "%3B", ";");
	text = SearchReplace(text, "%2C", ",");
	text = SearchReplace(text, "%3D", "=");
	text = SearchReplace(text, "%26", "&");
	text = SearchReplace(text, "%3A", ":");
	text = SearchReplace(text, "%3F", "?");
	text = SearchReplace(text, "%21", "!");
	text = SearchReplace(text, "%22", "\"");
	text = SearchReplace(text, "%23", "#");
	text = SearchReplace(text, "%24", "$");
	text = SearchReplace(text, "%27", "'");
	text = SearchReplace(text, "%28", "(");
	text = SearchReplace(text, "%29", ")");
	text = SearchReplace(text, "%2A", "*");
	text = SearchReplace(text, "%2D", "-");
	text = SearchReplace(text, "%2E", ".");
	text = SearchReplace(text, "%2F", "/");
	text = SearchReplace(text, "%3C", "<");
	text = SearchReplace(text, "%3E", ">");
	text = SearchReplace(text, "%40", "@");
	text = SearchReplace(text, "%5B", "[");
	text = SearchReplace(text, "%5C", "\\");
	text = SearchReplace(text, "%5D", "]");
	text = SearchReplace(text, "%5E", "^");
	text = SearchReplace(text, "%5F", "_");
	text = SearchReplace(text, "%60", "`");
	text = SearchReplace(text, "%7B", "{");
	text = SearchReplace(text, "%7C", "|");
	text = SearchReplace(text, "%7D", "}");
	text = SearchReplace(text, "%7E", "~");
	text = SearchReplace(text, "%A1", "¡");
	text = SearchReplace(text, "%A2", "¢");
	text = SearchReplace(text, "%A3", "£");
	text = SearchReplace(text, "%A4", "¤");
	text = SearchReplace(text, "%A5", "¥");
	text = SearchReplace(text, "%A6", "¦");
	text = SearchReplace(text, "%A7", "§");
	text = SearchReplace(text, "%A8", "¨");
	text = SearchReplace(text, "%A9", "©");
	text = SearchReplace(text, "%AA", "ª");
	text = SearchReplace(text, "%AB", "«");
	text = SearchReplace(text, "%AC", "¬");	
	text = SearchReplace(text, "%AD", "­");
	text = SearchReplace(text, "%AE", "®");	
	text = SearchReplace(text, "%AF", "¯");
	text = SearchReplace(text, "%B0", "°");	
	text = SearchReplace(text, "%B1", "±");
	text = SearchReplace(text, "%B2", "²");	
	text = SearchReplace(text, "%B3", "³");
	text = SearchReplace(text, "%B4", "´");	
	text = SearchReplace(text, "%B5", "µ");
	text = SearchReplace(text, "%B6", "¶");	
	text = SearchReplace(text, "%B7", "·");
	text = SearchReplace(text, "%B8", "¸");	
	text = SearchReplace(text, "%B9", "¹");
	text = SearchReplace(text, "%BA", "º");	
	text = SearchReplace(text, "%BB", "»");
	text = SearchReplace(text, "%BC", "¼");	
	text = SearchReplace(text, "%BD", "½");
	text = SearchReplace(text, "%BE", "¾");	
	text = SearchReplace(text, "%BF", "¿");
	text = SearchReplace(text, "%C0", "À");
	text = SearchReplace(text, "%C1", "Á");
	text = SearchReplace(text, "%C2", "Â");
	text = SearchReplace(text, "%C3", "Ã");
	text = SearchReplace(text, "%C4", "Ä");
	text = SearchReplace(text, "%C5", "Å");
	text = SearchReplace(text, "%C6", "Æ");
	text = SearchReplace(text, "%C7", "Ç");
	text = SearchReplace(text, "%C8", "È");
	text = SearchReplace(text, "%C9", "É");
	text = SearchReplace(text, "%CA", "Ê");
	text = SearchReplace(text, "%CB", "Ë");
	text = SearchReplace(text, "%CC", "Ì");
	text = SearchReplace(text, "%CD", "Í");
	text = SearchReplace(text, "%CE", "Î");
	text = SearchReplace(text, "%CF", "Ï");
	text = SearchReplace(text, "%D0", "Ð");
	text = SearchReplace(text, "%D1", "Ñ");
	text = SearchReplace(text, "%D2", "Ò");
	text = SearchReplace(text, "%D3", "Ó");
	text = SearchReplace(text, "%D4", "Ô");
	text = SearchReplace(text, "%D5", "Õ");
	text = SearchReplace(text, "%D6", "Ö");
	text = SearchReplace(text, "%D7", "×");
	text = SearchReplace(text, "%D8", "Ø");
	text = SearchReplace(text, "%D9", "Ù");
	text = SearchReplace(text, "%DA", "Ú");
	text = SearchReplace(text, "%DB", "Û");
	text = SearchReplace(text, "%DC", "Ü");
	text = SearchReplace(text, "%DD", "Ý");
	text = SearchReplace(text, "%DE", "Þ");
	text = SearchReplace(text, "%DF", "ß");
	text = SearchReplace(text, "%E0", "à");
	text = SearchReplace(text, "%E1", "á");
	text = SearchReplace(text, "%E2", "â");
	text = SearchReplace(text, "%E3", "ã");
	text = SearchReplace(text, "%E4", "ä");
	text = SearchReplace(text, "%E5", "å");
	text = SearchReplace(text, "%E6", "æ");
	text = SearchReplace(text, "%E7", "ç");
	text = SearchReplace(text, "%E8", "è");
	text = SearchReplace(text, "%E9", "é");
	text = SearchReplace(text, "%EA", "ê");
	text = SearchReplace(text, "%EB", "ë");
	text = SearchReplace(text, "%EC", "ì");
	text = SearchReplace(text, "%ED", "í");
	text = SearchReplace(text, "%EE", "î");
	text = SearchReplace(text, "%EF", "ï");
	text = SearchReplace(text, "%F0", "ð");
	text = SearchReplace(text, "%F1", "ñ");
	text = SearchReplace(text, "%F2", "ò");
	text = SearchReplace(text, "%F3", "ó");
	text = SearchReplace(text, "%F4", "ô");
	text = SearchReplace(text, "%F5", "õ");
	text = SearchReplace(text, "%F6", "ö");
	text = SearchReplace(text, "%F7", "÷");
	text = SearchReplace(text, "%F8", "ø");
	text = SearchReplace(text, "%F9", "ù");
	text = SearchReplace(text, "%FA", "ú");
	text = SearchReplace(text, "%FB", "û");
	text = SearchReplace(text, "%FC", "ü");
	text = SearchReplace(text, "%FD", "ý");
	text = SearchReplace(text, "%FE", "þ");
	text = SearchReplace(text, "%FF", "ÿ");

	return text;
}

//////////////////////////////////////////////////////////////////////////////////////////////////

std::string StripLinks(std::string html)
{
	int begin = html.find("<a");
	int end   = html.find(">",begin);
	
	// Strip away the opening link tag
	while(begin != html.npos)
	{
		html = html.substr(0,begin) + html.substr(end + 1, html.size());

		begin = html.find("<a");
		end   = html.find(">",begin);
	}

	// Strip away the closing link tag
	begin = html.find("</a");
	end   = html.find(">",begin);
	
	while(begin != html.npos)
	{
		html = html.substr(0,begin) + html.substr(end + 1, html.size());

		begin = html.find("</a");
		end   = html.find(">",begin);
	}

	return html;
}

//////////////////////////////////////////////////////////////////////////////////////////////////

std::string Strip(std::string str, std::string from, std::string to, bool once)
{
	/* Strip away all strings begining with from and ending with to */

	int begin = str.find(from);
	int end   = str.find(to,begin);
	
	while((begin != str.npos) && (end != str.npos))
	{
		str = str.substr(0,begin) + str.substr(end + to.size(), str.size());

		begin = str.find(from);
		end   = str.find(to,begin);

		if(once == true) {
			break;
		}
	}

	return str;
}

//////////////////////////////////////////////////////////////////////////////////////////////////

std::string FixApostrophe(std::string str)
{
	/* Change all ' to '' for compability with the mysql database */
	
	int index = str.find("'");

	while(index != str.npos)
	{
		str = str.substr(0,index) + "'" + str.substr(index,str.size());

		index = str.find("'", index + 2);
	}

	str = SearchReplace(str, "\\'", "'");
	
	return str;
}

//////////////////////////////////////////////////////////////////////////////////////////////////

std::string FileToString(std::string fileName)
{
	std::string temp = "";
	std::string str = "";
	ifstream fin(fileName.c_str());

	// Check for error in opening file
	if(!fin) {
		//Message("Error", "Couldn't open \"" + fileName + "\" for input");
		return false;
	}
	
	// Read the page from the file to the page std::string
	while(getline(fin, temp))
	{
		str += temp += " ";
	}

	// Close the stream
	fin.close();

	return str;
}

//////////////////////////////////////////////////////////////////////////////////////////////////

std::string SearchReplace(std::string str, std::string search, std::string replace, bool one, int pos)
{
	// Find the position of search
	int index = str.find(search, pos);

	// Replace only the first?
	if(one == true)
	{
		str = str.substr(0,index) + replace + str.substr(index + search.size(), str.size());
	}
	else
	{
		// Replace all
		while(index != str.npos)
		{
			str = str.substr(0,index) + replace + str.substr(index + search.size(), str.size());

			index = str.find(search, index);
		}
	}

	return str;
}

//////////////////////////////////////////////////////////////////////////////////////////////////

std::string StringToLower(std::string str)
{
	std::string temp = str;
	transform(temp.begin(), temp.end(), temp.begin(), tolower);

	return temp;
}

//////////////////////////////////////////////////////////////////////////////////////////////////

void StringToFile(std::string str, std::string file)
{
	ofstream fout(file.c_str());

	// Check for error in opening file
	if(!fout) {
//		Message("Error", "Couldn't open \"" + file + "\" for input");
		return;
	}

	fout << str;

	fout.close();
}

//////////////////////////////////////////////////////////////////////////////////////////////////

bool IsSubstring(std::string str1, std::string str2)
{
	int i = str1.find(str2);

	if(i == str1.npos) {
		return false;
	}
	else {
		return true;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////

bool ConsistsOnlyOf(std::string str)
{
	/* Checks if the std::string only consists of english letters, the numbers and _ */

	// Make the std::string lowercase
	str = StringToLower(str);

	// Go through the std::string and check if any of the characters is ilegal
	for(int i = str.size() - 1; i > 0; i--)
	{	
		switch(str[i])
		{
			case 'a': break;
			case 'b': break;
			case 'c': break;
			case 'd': break;
			case 'e': break;
			case 'f': break;
			case 'g': break;
			case 'h': break;
			case 'i': break;
			case 'j': break;
			case 'k': break;
			case 'l': break;
			case 'm': break;
			case 'n': break;
			case 'o': break;
			case 'p': break;
			case 'q': break;
			case 'r': break;
			case 's': break;
			case 't': break;
			case 'u': break;
			case 'v': break;
			case 'w': break;
			case 'x': break;
			case 'y': break;
			case 'z': break;
			case '1': break;
			case '2': break;
			case '3': break;
			case '4': break;
			case '5': break;
			case '6': break;
			case '7': break;
			case '8': break;
			case '9': break;
			case '0': break;
			case '_': break;
			default: return false;
		}
	}

	return true;
}

///////////////////////////////////////////////////////////////////////////////

std::string GetString(std::string str, std::string sub1, std::string sub2)
{
	int pos1, pos2;
	
	if((pos1 = FindString(str,sub1)) < 0 ) {
		return std::string("");
	}


	if((pos2 = FindString(str,sub2, pos1)) < (pos1 + sub1.size()) || pos2 == -1) {
		return std::string("");
	}

	pos1 += sub1.size();

	return GetString(str, pos1, pos2 - pos1);
}

///////////////////////////////////////////////////////////////////////////////

std::string GetString(std::string str, int pos1, int pos2)
{
	return str.substr(pos1, pos2);
}

///////////////////////////////////////////////////////////////////////////////

int FindString(std::string str, std::string search)
{
	int index = str.find(search);

	// Check to see if the std::string wasn't found
	if(index == str.npos) {
		return -1;
	}

	return index;
}

///////////////////////////////////////////////////////////////////////////////

int FindString(std::string str, std::string search, int pos)
{
	assert(pos >= 0);

	int index = str.find(search, pos);

	// Check to see if the std::string wasn't found
	if(index == str.npos) {
		return -1;
	}

	return index;
}

///////////////////////////////////////////////////////////////////////////////

std::string TranslateHTML(std::string text)
{
	text = SearchReplace(text, "&nbsp;", " ");
	text = SearchReplace(text, "&lsquo;", "‘");
	text = SearchReplace(text, "&rsquo;", "’");
	text = SearchReplace(text, "&sbquo;", "‚");
	text = SearchReplace(text, "&ldquo;", "“");
	text = SearchReplace(text, "&rdquo;", "”");
	text = SearchReplace(text, "&bdquo;", "„");
	text = SearchReplace(text, "&dagger;", "†");
	text = SearchReplace(text, "&Dagger;", "‡");
	text = SearchReplace(text, "&permil;", "‰");
	text = SearchReplace(text, "&lsaquo;", "‹");
	text = SearchReplace(text, "&rsaquo;", "›");
	text = SearchReplace(text, "&trade;", "™");
	text = SearchReplace(text, "&quot;", "\"");
	text = SearchReplace(text, "&amp;", "&");
	text = SearchReplace(text, "&frasl;", "/");
	text = SearchReplace(text, "&ndash;", "–");
	text = SearchReplace(text, "&mdash;", "—");
	text = SearchReplace(text, "&iexcl;", "¡");
	text = SearchReplace(text, "&cent;", "¢");
	text = SearchReplace(text, "&pound;", "£");
	text = SearchReplace(text, "&curren;", "¤");
	text = SearchReplace(text, "&yen;", "¥");
	text = SearchReplace(text, "&brvbar;", "¦");
	text = SearchReplace(text, "&brkbar;", "¦");
	text = SearchReplace(text, "&sect;", "§");
	text = SearchReplace(text, "&uml;", "¨");
	text = SearchReplace(text, "&die;", "¨");
	text = SearchReplace(text, "&copy;", "©");
	text = SearchReplace(text, "&ordf;", "ª");
	text = SearchReplace(text, "&laquo;", "«");
	text = SearchReplace(text, "&not;", "¬");
	text = SearchReplace(text, "&shy;", "­");
	text = SearchReplace(text, "&reg;", "®");
	text = SearchReplace(text, "&macr;", "¯");
	text = SearchReplace(text, "&hibar;", "¯");
	text = SearchReplace(text, "&deg;", "°");
	text = SearchReplace(text, "&plusmn;", "±");
	text = SearchReplace(text, "&sup2;", "²");
	text = SearchReplace(text, "&sup3;", "³");
	text = SearchReplace(text, "&acute;", "´");
	text = SearchReplace(text, "&micro;", "µ");
	text = SearchReplace(text, "&para;", "¶");
	text = SearchReplace(text, "&middot;", "·");
	text = SearchReplace(text, "&cedil;", "¸");
	text = SearchReplace(text, "&sup1;", "¹");
	text = SearchReplace(text, "&ordm;", "º");
	text = SearchReplace(text, "&raquo;", "»");
	text = SearchReplace(text, "&frac14;", "¼");	
	text = SearchReplace(text, "&frac12;", "½");
	text = SearchReplace(text, "&frac34;", "¾");	
	text = SearchReplace(text, "&iquest;", "¿");
	text = SearchReplace(text, "&Agrave;", "À");	
	text = SearchReplace(text, "&Aacute;", "Á");
	text = SearchReplace(text, "&Acirc;", "Â");	
	text = SearchReplace(text, "&Atilde;", "Ã");
	text = SearchReplace(text, "&Auml;", "Ä");	
	text = SearchReplace(text, "&Aring;", "Å");
	text = SearchReplace(text, "&AElig;", "Æ");	
	text = SearchReplace(text, "&Ccedil;", "Ç");
	text = SearchReplace(text, "&Egrave;", "È");	
	text = SearchReplace(text, "&Eacute;", "É");
	text = SearchReplace(text, "&Ecirc;", "Ê");	
	text = SearchReplace(text, "&Euml;", "Ë");
	text = SearchReplace(text, "&Igrave;", "Ì");	
	text = SearchReplace(text, "&Iacute;", "Í");
	text = SearchReplace(text, "&Icirc;", "Î");	
	text = SearchReplace(text, "&Iuml;", "Ï");
	text = SearchReplace(text, "&ETH;", "Ð");
	text = SearchReplace(text, "&Ntilde;", "Ñ");
	text = SearchReplace(text, "&Ograve;", "Ò");
	text = SearchReplace(text, "&Oacute;", "Ó");
	text = SearchReplace(text, "&Ocirc;", "Ô");
	text = SearchReplace(text, "&Otilde;", "Õ");
	text = SearchReplace(text, "&Ouml;", "Ö");
	text = SearchReplace(text, "&times;", "×");
	text = SearchReplace(text, "&Oslash;", "Ø");
	text = SearchReplace(text, "&Ugrave;", "Ù");
	text = SearchReplace(text, "&Uacute;", "Ú");
	text = SearchReplace(text, "&Ucirc;", "Û");
	text = SearchReplace(text, "&Uuml;", "Ü");
	text = SearchReplace(text, "&Yacute;", "Ý");
	text = SearchReplace(text, "&THORN;", "Þ");
	text = SearchReplace(text, "&szlig;", "ß");
	text = SearchReplace(text, "&agrave;", "à");
	text = SearchReplace(text, "&aacute;", "á");
	text = SearchReplace(text, "&acirc;", "â");
	text = SearchReplace(text, "&atilde;", "ã");
	text = SearchReplace(text, "&auml;", "ä");
	text = SearchReplace(text, "&aring;", "å");
	text = SearchReplace(text, "&aelig;", "æ");
	text = SearchReplace(text, "&ccedil;", "ç");
	text = SearchReplace(text, "&egrave;", "è");
	text = SearchReplace(text, "&eacute;", "é");
	text = SearchReplace(text, "&ecirc;", "ê");
	text = SearchReplace(text, "&euml;", "ë");
	text = SearchReplace(text, "&igrave;", "ì");
	text = SearchReplace(text, "&iacute;", "í");
	text = SearchReplace(text, "&icirc;", "î");
	text = SearchReplace(text, "&iuml;", "ï");
	text = SearchReplace(text, "&eth;", "ð");
	text = SearchReplace(text, "&ntilde;", "ñ");
	text = SearchReplace(text, "&ograve;", "ò");
	text = SearchReplace(text, "&oacute;", "ó");
	text = SearchReplace(text, "&ocirc;", "ô");
	text = SearchReplace(text, "&otilde;", "õ");
	text = SearchReplace(text, "&ouml;", "ö");
	text = SearchReplace(text, "&divide;", "÷");
	text = SearchReplace(text, "&oslash;", "ø");
	text = SearchReplace(text, "&ugrave;", "ù");
	text = SearchReplace(text, "&uacute;", "ú");
	text = SearchReplace(text, "&ucirc;", "û");
	text = SearchReplace(text, "&uuml;", "ü");
	text = SearchReplace(text, "&yacute;", "ý");
	text = SearchReplace(text, "&thorn;", "þ");
	text = SearchReplace(text, "&yuml;", "ÿ");


	return text;
}

///////////////////////////////////////////////////////////////////////////////
