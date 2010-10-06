#include <iostream>
#include <string>
 
#include "idline.h"

using namespace std;


int main()
{
	Idline id;
	string pin;
	Placement placement;
	int count = 0;
	int i;

	
	//std::cout << "You are allowed to do this: " << IsIdentity("541","PilotsPass") << std::endl;

	cout << "Enter your PIN: ";
	cin >> pin;

	id = GetIdline(pin);

	if (id.name == std::string("")) {
		cout << "No record found!";
		return 0;
	}

	std::cout << "You are: " << id.rank << " " << id.name << std::endl;

	std::cout << "Callsign: " << id.nick << std::endl;

	std::cout << "ID Line: " << id.idstr << std::endl;

	if (id.placement.squad != std::string(""))
		std::cout <<"Squadron: " << id.placement.squad << std::endl;

	if (id.placement.wing != std::string(""))
		std::cout <<"Wing: " << id.placement.wing << std::endl;

	if (id.placement.ship != std::string(""))
		std::cout <<"Ship: " << id.placement.ship << std::endl;
	
	for(i=0; i<21; i++)
	{
		count += id.medals.type[i];
	}

	std::cout << "You have " << count << " diffrent kinds of medals" << std::endl;
	std::cout << "You have achived " << id.fchg << " in FCHG rank" << std::endl;
	std::cout << "Your quote is \"" << id.quote << "\"" << std::endl;

	std::cout << "Your medals are" << std::endl;
	
	for(i=0; i<21; i++)
	{
		std::cout << "Type " << i << ": " << id.medals.type[i] << std::endl;
	}

	

	return 0;
}