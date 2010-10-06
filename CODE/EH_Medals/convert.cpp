/*  convert.cpp
	Handle converting strings into usable numbers for the rest of the engine
*/
#include <string>

#include "stats/scoring.h"
#include "stats/medals.h"
#include "EH_Medals/idline.h"

// converts rank string into the number value of the rank
int get_rank(string rank)
{
	char Rank[20];
	strcpy(Rank, rank.c_str());

	if ( !stricmp("sub-lieutenant", Rank) )
		return RANK_SL;
	if ( !stricmp("lieutenant", Rank) )
		return RANK_LT;
	if ( !stricmp("lieutenant commander", Rank) )
		return RANK_LCM;
	if ( !stricmp("commander", Rank) )
		return RANK_CM;
	if ( !stricmp("captain", Rank) )
		return RANK_CPT;
	if ( !stricmp("major", Rank) )
		return RANK_MAJ;
	if ( !stricmp("lieutenant colonel", Rank) )
		return RANK_LC;
	if ( !stricmp("colonel", Rank) )
		return RANK_COL;
	if ( !stricmp("general", Rank) )
		return RANK_GN;
	if ( !stricmp("rear admiral", Rank) )
		return RANK_RA;
	if ( !stricmp("vice admiral", Rank) )
		return RANK_VA;
	if ( !stricmp("admiral", Rank) )
		return RANK_AD;
	if ( !stricmp("fleet admiral", Rank) )
		return RANK_FA;
	if ( !stricmp("high admiral", Rank) )
		return RANK_HA;

	return RANK_CT;
}

// converts fchg string into the number value of the string
int get_fchg(string fchg)
{
	char Fchg[5];
	strcpy(Fchg, fchg.c_str());

	if ( !stricmp("gren", Fchg) )
		return RANK_GREN;
	if ( !stricmp("lanc", Fchg) )
		return RANK_LANC;
	if ( !stricmp("huss", Fchg) )
		return RANK_HUSS;
	if ( !stricmp("fusl", Fchg) )
		return RANK_FUSL;
	if ( !stricmp("drag", Fchg) )
		return RANK_DRAG;
	if ( !stricmp("cavl", Fchg) )
		return RANK_CAVL;
	if ( !stricmp("gall", Fchg) )
		return RANK_GALL;
	if ( !stricmp("kngt", Fchg) )
		return RANK_KNGT;
	if ( !stricmp("pldn", Fchg) )
		return RANK_PLDN;
	if ( !stricmp("cntr", Fchg) )
		return RANK_CNTR;
	if ( !stricmp("lgnr", Fchg) )
		return RANK_LGNR;
	if ( !stricmp("excr", Fchg) )
		return RANK_EXCR;
	if ( !stricmp("gldr", Fchg) )
		return RANK_GLDR;
	if ( !stricmp("arch", Fchg) )
		return RANK_ARCH;
	if ( !stricmp("tmpr", Fchg) )
		return RANK_TMPR;
	if ( !stricmp("impr", Fchg) )
		return RANK_IMPR;

	return RANK_NONE;
}

// checks if medal was awarded and sets the correct medal in the scoring_struct array
void make_medals(scoring_struct *stats, EH_Medals medals)
{
	if (medals.MoH)
		stats->medals[MEDAL_MOH] = 1;
	if (medals.IC)
		stats->medals[MEDAL_IC] = 1;
	if (medals.OoR)
		stats->medals[MEDAL_OOR] = 1;
	if (medals.GOE)
		stats->medals[MEDAL_GOE] = 1;
	if (medals.GS)
		stats->medals[MEDAL_GS] = 1;
	if (medals.SS)
		stats->medals[MEDAL_SS] = 1;
	if (medals.BS)
		stats->medals[MEDAL_BS] = 1;
	if (medals.PC)
		stats->medals[MEDAL_PC] = 1;
	if (medals.ISM)
		stats->medals[MEDAL_ISM] = 1;
	if (medals.IS)
		stats->medals[MEDAL_IS] = 1;
	if (medals.LoC)
		stats->medals[MEDAL_LOC] = 1;
	if (medals.DFC)
		stats->medals[MEDAL_DFC] = 1;

	// give pilot their wings if they are SL or above
	if (stats->rank != RANK_CT)
		stats->medals[MEDAL_WINGS] = 1;
}