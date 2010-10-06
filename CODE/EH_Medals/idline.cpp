#include "EH_Medals\idline.h"
#include "EH_Medals\webget.h"
#include "EH_Medals\stringfuncs.h"
#include "cfile\cfile.h"

#include <iostream>
using namespace std;

EH_Medals FillInMedals(std::string idstr)
{
	/* Find out if a pilot has a certain medal */

	EH_Medals medals;

	if(FindString(idstr,"MoH") != -1) {
		medals.MoH = 1;
	}
	else {
		medals.MoH = 0;
	}

	if(FindString(idstr,"IC") != -1) {
		medals.IC = 1;
	}
	else {
		medals.IC = 0;
	}

	if(FindString(idstr,"OoR") != -1) {
		medals.OoR = 1;
	}
	else {
		medals.OoR = 0;
	}

	if(FindString(idstr,"GOE") != -1) {
		medals.GOE = 1;
	}
	else {
		medals.GOE = 0;
	}

	if(FindString(idstr,"GS") != -1) {
		medals.GS = 1;
	}
	else {
		medals.GS = 0;
	}

	if(FindString(idstr,"SS") != -1) {
		medals.SS = 1;
	}
	else {
		medals.SS = 0;
	}

	if(FindString(idstr,"BS") != -1) {
		medals.BS = 1;
	}
	else {
		medals.BS = 0;
	}

	if(FindString(idstr,"PC") != -1) {
		medals.PC = 1;
	}
	else {
		medals.PC = 0;
	}

	if(FindString(idstr,"ISM") != -1) {
		medals.ISM = 1;
	}
	else {
		medals.ISM = 0;
	}

	if(FindString(idstr,"MoI") != -1) {
		medals.MoI = 1;
	}
	else {
		medals.MoI = 0;
	}

	if(FindString(idstr,"MoT") != -1) {
		medals.MoT = 1;
	}
	else {
		medals.MoT = 0;
	}

	if(FindString(idstr,"IS") != -1) {
		medals.IS = 1;
	}
	else {
		medals.IS = 0;
	}

	if(FindString(idstr,"LoC") != -1) {
		medals.LoC = 1;
	}
	else {
		medals.LoC = 0;
	}

	if(FindString(idstr,"DFC") != -1) {
		medals.DFC = 1;
	}
	else {
		medals.DFC = 0;
	}

	if(FindString(idstr,"MoC") != -1) {
		medals.MoC = 1;
	}
	else {
		medals.MoC = 0;
	}

	if(FindString(idstr,"CoS") != -1) {
		medals.CoS = 1;
	}
	else {
		medals.CoS = 0;
	}

	if(FindString(idstr,"CoE") != -1) {
		medals.CoE = 1;
	}
	else {
		medals.CoE = 0;
	}

	if(FindString(idstr,"CoL") != -1) {
		medals.CoL = 1;
	}
	else {
		medals.CoL = 0;
	}

	if(FindString(idstr,"CoB") != -1) {
		medals.CoB = 1;
	}
	else {
		medals.CoB = 0;
	}

	if(FindString(idstr,"LoA") != -1) {
		medals.LoA = 1;
	}
	else {
		medals.LoA = 0;
	}

	if(FindString(idstr,"OV") != -1) {
		medals.OV = 1;
	}
	else {
		medals.OV = 0;
	}



	return medals;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

Idline GetIdline(std::string pin)
{
	CGetWebpage get;
	Idline		id;
	std::string full_idstr;
	std::string page;
	std::string url;// = "http://www.ehtiecorps.org/rosters/personnel.asp?record=";
	char str[512];
	CFILE *in;

	// open the cfg file in the \data folder to get the current url
	in = cfopen("pin.cfg", "rt", CFILE_NORMAL, CF_TYPE_DATA);
	
	// if we failed to open the config file, user default settings
	if(in == NULL){
		id.name = std::string("NoCFG");		
		return id;
	}

	while(!cfeof(in)){
		// read in the game info
		memset(str,0,512);
		cfgets(str,512,in);
	}

	cfclose(in);

	url = str;

	url += pin;

	// Get the entier profile
	page = get.SendRequest(false, url.c_str(), std::string(""));
	if (page == std::string("error")) {
		id.name = std::string("");
		return id;
	}

	// Check to see if the record excists
	if(FindString(page, "TIE Corps Personnel Record ") == -1) {
		id.name = std::string("PIN Error");
 		return id;
 	}

	// Get nick
    id.nick = GetString(page, "- \"", "\"</font>");

	// Get rank
	id.rank = GetString(GetString(page, "<img src=\"/images/ranks", "&"), "alt=\"", "\">");

	// Get the name
	id.name = GetString(GetString(page, "<font face=\"Arial\" size=\"+2\" color=\"#FFFFFF\">", "</font>"), id.rank + " ", "</b>");

	// Get quote
	id.quote = SearchReplace(GetString(page, "<font face=\"Arial\" size=\"-1\"><i>", "</i>"), "&quot;", "\"");
	
	// Get the idline, all medals and iwats courses
	full_idstr = GetString(page, "<font face=\"Arial\" size=\"-2\">", "</font>");
	
	// Get the medal string
	id.medalString = GetString(full_idstr,"<br>","[");

	if (id.medalString == "") {
		id.medalString = GetString(full_idstr,"<br>","{");
	}

	// Get the FCHG rank
	id.fchg = GetString(full_idstr, "[","]");

	// Get only the ID line
	full_idstr = full_idstr.substr(0, FindString(full_idstr,"<br>"));
	id.idstr = Strip(full_idstr, "<", ">", false);

	// Get placment
	id.placement = GetPlacement(id.idstr);

	// Get the medals
	id.medals = FillInMedals(id.medalString);
	
	return id;

}

///////////////////////////////////////////////////////////////////////////////////////////////////

bool IsIdentity(std::string pin, std::string password)
{
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
 
Placement GetPlacement(std::string id)
{
	Placement place;
	std::string pilottype = id.substr(0,FindString(id,"/"));

	if(pilottype == "FM" || pilottype == "FL" || pilottype == "CMDR")
	{
		place.ship = id.substr(id.find_last_of("/") + 1,id.length() - id.find_last_of("/") - 1);
		id = id.substr(0, id.find_last_of("/"));
		place.wing = id.substr(id.find_last_of("/") + 1,id.length() - id.find_last_of("/") - 1);
		id = id.substr(0, id.find_last_of("/"));
		//if (pilottype == "CMDR")
		//	place.squad = id.substr(id.find_last_of("/") + 1,id.length() - id.find_last_of("/") - 1);
		//else
			place.squad = id.substr(id.find_last_of("/") + 1,id.length() - id.find_last_of("/") - 4);
	}
	else if(pilottype == "WC")
	{
		place.ship = id.substr(id.find_last_of("/") + 1,id.length() - id.find_last_of("/") - 1);
		id = id.substr(0, id.find_last_of("/"));
		place.wing = id.substr(id.find_last_of("/") + 1,id.length() - id.find_last_of("/") - 1);
		place.squad = "";
	}
	else
	{
		place.ship = id.substr(id.find_last_of("/") + 1,id.length() - id.find_last_of("/") - 1);
		place.wing = "";
		place.squad = "";
	}

	return place;
}
