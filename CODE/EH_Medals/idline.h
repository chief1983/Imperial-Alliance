#ifndef _IDLINE_H_
#define _IDLINE_H_

#include <string>

using namespace std;

///////////////////////////////////////////////////////////////////////////////////////////////////

struct EH_Medals
{
	union
	{
		struct  
		{
			unsigned char	MoH;
			unsigned char	IC;
			unsigned char	OoR;
			unsigned char	GOE;
			unsigned char	GS;
			unsigned char	SS;
			unsigned char	BS;
			unsigned char	PC;
			unsigned char	ISM;
			unsigned char	MoI;
			unsigned char	MoT;
			unsigned char	IS;
			unsigned char	LoC;
			unsigned char	DFC;
			unsigned char	MoC;
			unsigned char	CoS;
			unsigned char	CoE;
			unsigned char	CoL;
			unsigned char	CoB;
			unsigned char	LoA;
			unsigned char	OV;
		};

		unsigned char type[21];
	};
} ;

struct Placement
{
	std::string ship;
	std::string wing;
	std::string squad;
};


///////////////////////////////////////////////////////////////////////////////////////////////////

struct Idline
{
	EH_Medals medals;
	Placement placement;
	std::string nick;
	std::string rank;
	std::string name;
	std::string idstr;
	std::string medalString;
	std::string quote;
	std::string fchg;
	std::string squad;
};

///////////////////////////////////////////////////////////////////////////////////////////////////

Idline GetIdline(std::string pin);

bool IsIdentity(std::string pin, std::string password);

Placement GetPlacement(std::string id);

///////////////////////////////////////////////////////////////////////////////////////////////////


#endif