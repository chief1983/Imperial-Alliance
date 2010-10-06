/*
 * Copyright (C) Volition, Inc. 1999.  All rights reserved.
 *
 * All source code herein is the property of Volition, Inc. You may not sell 
 * or otherwise commercially exploit the source or things you created based on the 
 * source.
 *
*/

/*
 * $Logfile: /Freespace2/code/Fonttool/FontTool.h $
 * $Revision: 2 $
 * $Date: 10/24/98 5:15p $
 * $Author: Dave $
 *
 * Include file for font creating/kerning tools
 *
 * $Log: /Freespace2/code/Fonttool/FontTool.h $
 * 
 * 2     10/24/98 5:15p Dave
 * 
 * 1     10/24/98 4:58p Dave
 * 
 * 2     6/05/97 4:53p John
 * First rev of new antialiased font stuff.
 * 
 * 1     6/02/97 4:04p John
 *
 * $NoKeywords: $
 */

#ifndef _FONTTOOL_H
#define _FONTTOOL_H

// these are define in pstypes.h to alias other functions.  but they make the fonttool crash for some reason
// they aren't needed for this in anyway so we undefine them so that fonttool uses the standard versions of them.
#ifdef malloc
#undef malloc
#endif

#ifdef free
#undef free
#endif

#ifdef strdup
#undef strdup
#endif

#include "graphics/2d.h"
#include "graphics/font.h"

int fonttool_edit_kerning(char *fname1);
void fonttool_kerning_copy( char *fname1, char *fname2 );
void fonttool_create_font(char *pcx_filename, char *font_filename);

void fonttool_read( char *fname2, font *fnt2 );
void fonttool_copy_kern( font *fnt1, font *fnt2 );
void fonttool_dump( char *fname1, font *fnt1 );
void fonttool_remove_kerning( font *fnt );
void fonttool_resync_kerning(font *fnt);

int fonttool_get_kerning( font *fnt, int c1, int c2, int *pairnum );
void fonttool_set_kerning( font *fnt, int c1, int c2, int dist );

void app_init();
void app_shutdown();
void close_graphics();

void print_out(char *string);


#endif
