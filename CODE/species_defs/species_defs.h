// Species_Defs.h
// Extended Species Support for FS2 Open
// Derek Meek
// 10-14-2003

/*
 * $Logfile: /Freespace2/code/species_defs/species_defs.h $
 * $Revision: 1.1.1.1 $
 * $Date: 2004/08/13 22:47:43 $
 * $Author: Spearhawk $
 *
 * $Log: species_defs.h,v $
 * Revision 1.1.1.1  2004/08/13 22:47:43  Spearhawk
 * no message
 *
 * Revision 1.1.1.1  2004/08/13 21:34:41  Darkhill
 * no message
 *
 * Revision 1.1  2003/10/15 22:03:27  Kazan
 * Da Species Update :D
 *
 *
 *
 *
 */

#if !defined(_species_defs_h_)
#define _species_defs_h_

extern int True_NumSpecies;

// load up the species_defs.tbl into the correct data areas
// IMPORTANT: If NumSpecies != 3 icons.tbl has to be modified to compensate!
void Init_Species_Definitions();

#endif