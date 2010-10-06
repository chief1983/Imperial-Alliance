/*
 * Copyright (C) Volition, Inc. 1999.  All rights reserved.
 *
 * All source code herein is the property of Volition, Inc. You may not sell 
 * or otherwise commercially exploit the source or things you created based on the 
 * source.
 *
*/

/*
 * $Logfile: /Freespace2/code/Render/3dLaser.cpp $
 * $Revision: 1.1.1.1 $
 * $Date: 2004/08/13 22:47:43 $
 * $Author: Spearhawk $
 *
 * Code to draw 3d looking lasers
 *
 * $Log: 3dlaser.cpp,v $
 * Revision 1.1.1.1  2004/08/13 22:47:43  Spearhawk
 * no message
 *
 * Revision 1.1.1.1  2004/08/13 21:33:27  Darkhill
 * no message
 *
 * Revision 2.11  2004/03/21 09:41:54  randomtiger
 * Fixed a bug that was causing windowed movie playback and a crash.
 * Added some batching redirection.
 *
 * Revision 2.10  2004/03/17 04:07:31  bobboau
 * new fighter beam code
 * fixed old after burner trails
 * had to bump a few limits, working on some dynamic solutions
 * a few fixed to background POF rendering
 * fixing asorted bugs
 *
 * Revision 2.9  2004/03/06 23:28:24  bobboau
 * fixed motion debris
 * animated laser textures
 * and added a new error check called a safepoint, mostly for tracking the 'Y bug'
 *
 * Revision 2.8  2004/03/05 09:01:51  Goober5000
 * Uber pass at reducing #includes
 * --Goober5000
 *
 * Revision 2.7  2004/02/28 14:14:57  randomtiger
 * Removed a few uneeded if DIRECT3D's.
 * Set laser function to only render the effect one sided.
 * Added some stuff to the credits.
 * Set D3D fogging to fall back to vertex fog if table fog not supported.
 *
 * Revision 2.6  2004/02/20 04:29:56  bobboau
 * pluged memory leaks,
 * 3D HTL lasers (they work perfictly)
 * and posably fixed Turnsky's shinemap bug
 *
 * Revision 2.5  2004/02/14 00:18:35  randomtiger
 * Please note that from now on OGL will only run with a registry set by Launcher v4. See forum for details.
 * OK, these changes effect a lot of file, I suggest everyone updates ASAP:
 * Removal of many files from project.
 * Removal of meanless Gr_bitmap_poly variable.
 * Removal of glide, directdraw, software modules all links to them, and all code specific to those paths.
 * Removal of redundant Fred paths that arent needed for Fred OGL.
 * Have seriously tidied the graphics initialisation code and added generic non standard mode functionality.
 * Fixed many D3D non standard mode bugs and brought OGL up to the same level.
 * Removed texture section support for D3D8, voodoo 2 and 3 cards will no longer run under fs2_open in D3D, same goes for any card with a maximum texture size less than 1024.
 *
 * Revision 2.4  2004/02/03 18:29:30  randomtiger
 * Fixed OGL fogging in HTL
 * Changed htl laser function to work in D3D, commented out until function flat bug is fixed
 *
 * Revision 2.3  2003/11/25 15:04:46  fryday
 * Got lasers to work in HT&L OpenGL
 * Messed a bit with opengl_tmapper_internal3d, draw_laser functions, and added draw_laser_htl
 *
 * Revision 2.2  2003/08/21 15:03:43  phreak
 * zeroed out the specular fields since they caused some flickering
 *
 * Revision 2.1  2002/08/01 01:41:09  penguin
 * The big include file move
 *
 * Revision 2.0  2002/06/03 04:02:28  penguin
 * Warpcore CVS sync
 *
 * Revision 1.2  2002/05/04 04:52:22  mharris
 * 1st draft at porting
 *
 * Revision 1.1  2002/05/02 18:03:12  mharris
 * Initial checkin - converted filenames and includes to lower case
 *
 * 
 * 5     7/30/99 7:01p Dave
 * Dogfight escort gauge. Fixed up laser rendering in Glide.
 * 
 * 4     7/27/99 3:09p Dave
 * Made g400 work. Whee.
 * 
 * 3     5/27/99 6:17p Dave
 * Added in laser glows.
 * 
 * 2     10/07/98 10:53a Dave
 * Initial checkin.
 * 
 * 1     10/07/98 10:51a Dave
 * 
 * 26    5/13/98 3:10p John
 * made detail slider for weapon rendering change the distance that lasers
 * become non-textured.  The lowest setting turns off missile trail
 * rendering.
 * 
 * 25    5/05/98 11:15p Lawrance
 * Optimize weapon flyby sound determination
 * 
 * 24    4/10/98 5:20p John
 * Changed RGB in lighting structure to be ubytes.  Removed old
 * not-necessary 24 bpp software stuff.
 * 
 * 23    3/17/98 3:02p John
 * made lasers draw as non-textured only on software.
 * 
 * 22    3/17/98 3:01p John
 * Make thicker lasers not render as polys further away.
 * 
 * 21    2/26/98 3:26p John
 * Added code to turn off laser rendering
 * 
 * 20    1/29/98 9:46a John
 * Capped debris length
 * 
 * 19    1/23/98 5:08p John
 * Took L out of vertex structure used B (blue) instead.   Took all small
 * fireballs out of fireball types and used particles instead.  Fixed some
 * debris explosion things.  Restructured fireball code.   Restructured
 * some lighting code.   Made dynamic lighting on by default. Made groups
 * of lasers only cast one light.  Made fireballs not cast light.
 * 
 * 18    1/19/98 8:51a John
 * Did a quick out if both points of laser off same side of view pyramid.
 * 
 * 17    1/06/98 6:18p John
 * Made debris render as a blur.  Had to make g3_draw_laser take tmap
 * flags.
 * 
 * 16    12/15/97 10:09p John
 * put in some debug laser code.
 * 
 * 15    12/15/97 11:32a John
 * New Laser Code
 * 
 * 14    10/23/97 8:32p John
 * Increased laser to dot distance
 * 
 * 13    9/20/97 9:45a John
 * made lasers not draw as pixels as fast as before if viewing from the
 * side.
 * 
 * 
 * 12    8/19/97 11:42p Lawrance
 * use atan2_safe() instead of atan2()
 * 
 * 11    8/19/97 12:54p Sandeep
 * Fixed lasers to work in optimized build
 * 
 * 10    6/24/97 6:22p John
 * added detail flags.
 * sped up motion debris system a bit.
 * 
 * 9     5/29/97 3:10p John
 * Took out debug menu.  
 * Made software scaler draw larger bitmaps.
 * Optimized Direct3D some.
 * 
 * 8     4/29/97 9:55a John
 * 
 * 7     4/22/97 4:11p John
 * New debug var stuff
 * 
 * 6     3/28/97 6:10p Lawrance
 * draw lasers so end appears at gun mount tip on first frame
 * 
 * 5     3/06/97 8:48a John
 * fixed bug with lasers drawing too close.
 * 
 * 4     2/07/97 9:07a John
 * made lasers not fade by default.
 * 
 * 3     2/03/97 8:01p John
 * Added debug code to fade lasers out with distance.
 * 
 * 2     12/11/96 12:41p John
 * Added new code to draw 3d laser using 2d ellipses.
 * 
 * 1     12/11/96 12:13p John
 *
 * $NoKeywords: $
 */

#include "graphics/2d.h"
#include "render/3dinternal.h"
#include "globalincs/systemvars.h"
#include "io/key.h"
#include "cmdline/cmdline.h"
#include "graphics/grbatch.h"

int Lasers = 1;
DCF_BOOL( lasers, Lasers );
/*
// This works but leaves the effect looking very flat
float g3_draw_laser_htl(vector *p0,float width1,vector *p1,float width2, int r, int g, int b, uint tmap_flags)
{
	vector uvec, fvec, rvec, center;

	vm_vec_sub( &fvec, p0, p1 );
	vm_vec_normalize_safe( &fvec );

	vm_vec_avg( &center, p0, p1 ); //needed for the return value only

	vm_vec_crossprod(&uvec,&fvec,&Eye_matrix.vec.rvec);
	
	if(vm_vec_mag_squared(&uvec)==0) uvec.xyz.y = 1.0f; //in case fvec is exactly equal to matrx.rvec, stick some arbitrary value in uvec
	//normalize new perpendicular vector
	vm_vec_normalize(&uvec);
	 
	//now recompute right vector, in case it wasn't entirely perpendiclar
	vm_vec_crossprod(&rvec,&uvec,&fvec);

	// Now have uvec, which is up vector and rvec which is the normal
	// of the face.

	int i;
	vector vecs[4];
	vertex pts[4];
	vertex *ptlist[8] = 
	{ &pts[3], &pts[2], &pts[1], &pts[0], 
	  &pts[0], &pts[1], &pts[2], &pts[3]};

	vm_vec_scale_add( &vecs[0], p0, &uvec, width1/2.0f );
	vm_vec_scale_add( &vecs[1], p1, &uvec, width2/2.0f );
	vm_vec_scale_add( &vecs[2], p1, &uvec, -width2/2.0f );
	vm_vec_scale_add( &vecs[3], p0, &uvec, -width1/2.0f );

	for (i=0; i<4; i++ )	{
		g3_transfer_vertex( &pts[i], &vecs[i] );
	}
	ptlist[0]->u = 0.0f;
	ptlist[0]->v = 0.0f;
	ptlist[1]->u = 1.0f;
	ptlist[1]->v = 0.0f;
	ptlist[2]->u = 1.0f;
	ptlist[2]->v = 1.0f;
	ptlist[3]->u = 0.0f;
	ptlist[3]->v = 1.0f;
	ptlist[0]->r = (ubyte)r;
	ptlist[0]->g = (ubyte)g;
	ptlist[0]->b = (ubyte)b;
	ptlist[0]->a = 255;
	ptlist[1]->r = (ubyte)r;
	ptlist[1]->g = (ubyte)g;
	ptlist[1]->b = (ubyte)b;
	ptlist[1]->a = 255;
	ptlist[2]->r = (ubyte)r;
	ptlist[2]->g = (ubyte)g;
	ptlist[2]->b = (ubyte)b;
	ptlist[2]->a = 255;
	ptlist[3]->r = (ubyte)r;
	ptlist[3]->g = (ubyte)g;
	ptlist[3]->b = (ubyte)b;
	ptlist[3]->a = 255;

	gr_tmapper(gr_screen.mode == GR_DIRECT3D ? 8 : 4,
		ptlist,tmap_flags | TMAP_FLAG_RGB | TMAP_FLAG_GOURAUD | TMAP_FLAG_CORRECT);
	
	return center.xyz.z;
}
*/

float g3_draw_laser_htl_batched(vector *p0,float width1,vector *p1,float width2, int r, int g, int b, uint tmap_flags)
{
	width1 *= 0.5f;
	width2 *= 0.5f;
	vector uvec, fvec, rvec, center, reye;

	vm_vec_sub( &fvec, p0, p1 );
	vm_vec_normalize_safe( &fvec );

	vm_vec_avg( &center, p0, p1 ); //needed for the return value only
	vm_vec_sub(&reye, &Eye_position, &center);
	vm_vec_normalize(&reye);

	vm_vec_crossprod(&uvec,&fvec,&reye);
	vm_vec_normalize(&uvec);
	vm_vec_crossprod(&fvec,&uvec,&reye);
	vm_vec_normalize(&fvec);
	
//	if(vm_vec_mag_squared(&uvec)==0) uvec.xyz.y = 1.0f; //in case fvec is exactly equal to matrx.rvec, stick some arbitrary value in uvec
	//normalize new perpendicular vector
//	vm_vec_normalize(&uvec);
	 
	//now recompute right vector, in case it wasn't entirely perpendiclar
	vm_vec_crossprod(&rvec,&uvec,&fvec);

	// Now have uvec, which is up vector and rvec which is the normal
	// of the face.

	int i;
	vector start, end;
	vm_vec_scale_add(&start, p0, &fvec, -width1);
	vm_vec_scale_add(&end, p1, &fvec, width2);
	vector vecs[6];

	vm_vec_scale_add( &vecs[0], &start, &uvec, width1 );
	vm_vec_scale_add( &vecs[1], &end, &uvec, width2 );
	vm_vec_scale_add( &vecs[2], &end, &uvec, -width2 );
	vm_vec_scale_add( &vecs[3], &start, &uvec, -width1 );

	vertex *pts = batch_get_block(6, tmap_flags | TMAP_FLAG_RGB | TMAP_FLAG_GOURAUD | TMAP_FLAG_CORRECT);

	for (i=0; i<4; i++ )	{
		g3_transfer_vertex( &pts[i], &vecs[i] );
	}

	pts[0].u = 0.0f;
	pts[0].v = 1.0f;
	pts[0].r = (ubyte)r;
	pts[0].g = (ubyte)g;
	pts[0].b = (ubyte)b;
	pts[0].a = 255;

	pts[1].u = 1.0f;
	pts[1].v = 1.0f;
	pts[1].r = (ubyte)r;
	pts[1].g = (ubyte)g;
	pts[1].b = (ubyte)b;
	pts[1].a = 255;

	pts[2].u = 1.0f;
	pts[2].v = 0.0f;
	pts[2].r = (ubyte)r;
	pts[2].g = (ubyte)g;
	pts[2].b = (ubyte)b;
	pts[2].a = 255;

	pts[3].u = 0.0f;
	pts[3].v = 0.0f;
	pts[3].r = (ubyte)r;
	pts[3].g = (ubyte)g;
	pts[3].b = (ubyte)b;
	pts[3].a = 255;
 
	// 302
	memcpy(&pts[4], &pts[2], sizeof(vertex)); 
	memcpy(&pts[5], &pts[0], sizeof(vertex)); 

	return center.xyz.z;
}

float g3_draw_laser_htl(vector *p0,float width1,vector *p1,float width2, int r, int g, int b, uint tmap_flags)
{
	// Redirect for batching!
	if(Cmdline_batch_3dunlit && tmap_flags & TMAP_HTL_3DU_BATCH)
	{
		return g3_draw_laser_htl_batched(p0,width1,p1,width2, r, g, b, tmap_flags);

	}

	width1 *= 0.5f;
	width2 *= 0.5f;
	vector uvec, fvec, rvec, center, reye;

	vm_vec_sub( &fvec, p0, p1 );
	vm_vec_normalize_safe( &fvec );

	vm_vec_avg( &center, p0, p1 ); //needed for the return value only
	vm_vec_sub(&reye, &Eye_position, &center);
	vm_vec_normalize(&reye);

	vm_vec_crossprod(&uvec,&fvec,&reye);
	vm_vec_normalize(&uvec);
	vm_vec_crossprod(&fvec,&uvec,&reye);
	vm_vec_normalize(&fvec);
	
//	if(vm_vec_mag_squared(&uvec)==0) uvec.xyz.y = 1.0f; //in case fvec is exactly equal to matrx.rvec, stick some arbitrary value in uvec
	//normalize new perpendicular vector
//	vm_vec_normalize(&uvec);
	 
	//now recompute right vector, in case it wasn't entirely perpendiclar
	vm_vec_crossprod(&rvec,&uvec,&fvec);

	// Now have uvec, which is up vector and rvec which is the normal
	// of the face.

	int i;
	vector start, end;
	vm_vec_scale_add(&start, p0, &fvec, -width1);
	vm_vec_scale_add(&end, p1, &fvec, width2);
	vector vecs[4];
	vertex pts[4];
	vertex *ptlist[8] = 
	{ &pts[3], &pts[2], &pts[1], &pts[0], 
	  &pts[0], &pts[1], &pts[2], &pts[3]};

	vm_vec_scale_add( &vecs[0], &start, &uvec, width1 );
	vm_vec_scale_add( &vecs[1], &end, &uvec, width2 );
	vm_vec_scale_add( &vecs[2], &end, &uvec, -width2 );
	vm_vec_scale_add( &vecs[3], &start, &uvec, -width1 );

	for (i=0; i<4; i++ )	{
		g3_transfer_vertex( &pts[i], &vecs[i] );
	}
	ptlist[0]->u = 0.0f;
	ptlist[0]->v = 0.0f;
	ptlist[1]->u = 1.0f;
	ptlist[1]->v = 0.0f;
	ptlist[2]->u = 1.0f;
	ptlist[2]->v = 1.0f;
	ptlist[3]->u = 0.0f;
	ptlist[3]->v = 1.0f;
	ptlist[0]->r = (ubyte)r;
	ptlist[0]->g = (ubyte)g;
	ptlist[0]->b = (ubyte)b;
	ptlist[0]->a = 255;
	ptlist[1]->r = (ubyte)r;
	ptlist[1]->g = (ubyte)g;
	ptlist[1]->b = (ubyte)b;
	ptlist[1]->a = 255;
	ptlist[2]->r = (ubyte)r;
	ptlist[2]->g = (ubyte)g;
	ptlist[2]->b = (ubyte)b;
	ptlist[2]->a = 255;
	ptlist[3]->r = (ubyte)r;
	ptlist[3]->g = (ubyte)g;
	ptlist[3]->b = (ubyte)b;
	ptlist[3]->a = 255;

	gr_tmapper(4, ptlist,tmap_flags | TMAP_FLAG_RGB | TMAP_FLAG_GOURAUD | TMAP_FLAG_CORRECT);
	
	return center.xyz.z;
}


// This assumes you have already set a color with gr_set_color or gr_set_color_fast
// and a bitmap with gr_set_bitmap.  If it is very far away, it draws the laser
// as flat-shaded using current color, else textured using current texture.
// If max_len is > 1.0, then this caps the length to be no longer than max_len pixels.
float g3_draw_laser(vector *headp, float head_width, vector *tailp, float tail_width, uint tmap_flags, float max_len )
{
	if (!Lasers){
		return 0.0f;
	}
	if((!Cmdline_nohtl) && tmap_flags & TMAP_HTL_3D_UNLIT
		){
		//&&(gr_screen.mode == GR_OPENGL)) {
		return 
		g3_draw_laser_htl(headp, head_width, tailp, tail_width, 255,255,255, tmap_flags | TMAP_HTL_3D_UNLIT);
	}
	float headx, heady, headr, tailx, taily, tailr;
	vertex pt1, pt2;
	float depth;
	int head_on = 0;

	Assert( G3_count == 1 );

	g3_rotate_vertex(&pt1,headp);

	g3_project_vertex(&pt1);
	if (pt1.flags & PF_OVERFLOW) 
		return 0.0f;

	g3_rotate_vertex(&pt2,tailp);

	g3_project_vertex(&pt2);
	if (pt2.flags & PF_OVERFLOW) 
		return 0.0f;

	if ( (pt1.codes & pt2.codes) != 0 )	{
		// Both off the same side
		return 0.0f;
	}

	headx = pt1.sx;
	heady = pt1.sy;
	headr = (head_width*Matrix_scale.xyz.x*Canv_w2*pt1.sw);

	tailx = pt2.sx;
	taily = pt2.sy;
	tailr = (tail_width*Matrix_scale.xyz.x*Canv_w2*pt2.sw);

	float len_2d = fl_sqrt( (tailx-headx)*(tailx-headx) + (taily-heady)*(taily-heady) );

	// Cap the length if needed.
	if ( (max_len > 1.0f) && (len_2d > max_len) )	{
		float ratio = max_len / len_2d;
	
		tailx = headx + ( tailx - headx ) * ratio;
		taily = heady + ( taily - heady ) * ratio;
		tailr = headr + ( tailr - headr ) * ratio;

		len_2d = fl_sqrt( (tailx-headx)*(tailx-headx) + (taily-heady)*(taily-heady) );
	}

	depth = (pt1.z+pt2.z)*0.5f;

	float max_r  = headr;
	float a;
	if ( tailr > max_r ) 
		max_r = tailr;

	if ( max_r < 1.0f )
		max_r = 1.0f;

	float mx, my, w, h1,h2;

	if ( len_2d < max_r ) {

		h1 = headr + (max_r-len_2d);
		if ( h1 > max_r ) h1 = max_r;
		h2 = tailr + (max_r-len_2d);
		if ( h2 > max_r ) h2 = max_r;

		len_2d = max_r;
		if ( fl_abs(tailx - headx) > 0.01f )	{
			a = (float)atan2( taily-heady, tailx-headx );
		} else {
			a = 0.0f;
		}

		w = len_2d;
		head_on = 1;

	} else {
		a = atan2_safe( taily-heady, tailx-headx );

		w = len_2d;

		h1 = headr;
		h2 = tailr;
		head_on = 0;
	}
	
	mx = (tailx+headx)/2.0f;
	my = (taily+heady)/2.0f;

//	gr_set_color(255,0,0);
//	g3_draw_line( &pt1, &pt2 );

//	gr_set_color( 255, 0, 0 );
//	gr_pixel( fl2i(mx),fl2i(my) );

	// Draw box with width 'w' and height 'h' at angle 'a' from horizontal
	// centered around mx, my

	if ( h1 < 1.0f ) h1 = 1.0f;
	if ( h2 < 1.0f ) h2 = 1.0f;

	float sa, ca;

	sa = (float)sin(a);
	ca = (float)cos(a);

	vertex v[4];
	vertex *vertlist[4] = { &v[3], &v[2], &v[1], &v[0] };
	memset(v,0,sizeof(vertex)*4);

	float sw;
	if ( depth < 0.0f ) depth = 0.0f;
	sw = 1.0f / depth;
	
	v[0].sx = (-w/2.0f)*ca + (-h1/2.0f)*sa + mx;
	v[0].sy = (-w/2.0f)*sa - (-h1/2.0f)*ca + my;
	v[0].z = pt1.z;
	v[0].sw = pt1.sw;
	v[0].u = 0.0f;
	v[0].v = 0.0f;
	v[0].b = 191;

	v[1].sx = (w/2.0f)*ca + (-h2/2.0f)*sa + mx;
	v[1].sy = (w/2.0f)*sa - (-h2/2.0f)*ca + my;
	v[1].z = pt2.z;
	v[1].sw = pt2.sw;
	v[1].u = 1.0f;
	v[1].v = 0.0f;
	v[1].b = 191;

	v[2].sx = (w/2.0f)*ca + (h2/2.0f)*sa + mx;
	v[2].sy = (w/2.0f)*sa - (h2/2.0f)*ca + my;
	v[2].z = pt2.z;
	v[2].sw = pt2.sw;
	v[2].u = 1.0f;
	v[2].v = 1.0f;
	v[2].b = 191;

	v[3].sx = (-w/2.0f)*ca + (h1/2.0f)*sa + mx;
	v[3].sy = (-w/2.0f)*sa - (h1/2.0f)*ca + my;
	v[3].z = pt1.z;
	v[3].sw = pt1.sw;
	v[3].u = 0.0f;
	v[3].v = 1.0f;
	v[3].b = 191;

	gr_tmapper(4, vertlist, tmap_flags | TMAP_FLAG_CORRECT);	

	return depth;
}


// Draw a laser shaped 3d looking thing using vertex coloring (useful for things like colored laser glows)
// If max_len is > 1.0, then this caps the length to be no longer than max_len pixels
float g3_draw_laser_rgb(vector *headp, float head_width, vector *tailp, float tail_width, int r, int g, int b, uint tmap_flags, float max_len )
{
	if (!Lasers){
		return 0.0f;
	}
	if((!Cmdline_nohtl)  && tmap_flags & TMAP_HTL_3D_UNLIT
		){
	  //	&&(gr_screen.mode==GR_OPENGL)) {
		return 
		g3_draw_laser_htl(headp,head_width,tailp,tail_width,r,g,b,tmap_flags | TMAP_HTL_3D_UNLIT);
	}
	float headx, heady, headr, tailx, taily, tailr;
	vertex pt1, pt2;
	float depth;
	int head_on = 0;

	Assert( G3_count == 1 );

	g3_rotate_vertex(&pt1,headp);

	g3_project_vertex(&pt1);
	if (pt1.flags & PF_OVERFLOW) 
		return 0.0f;

	g3_rotate_vertex(&pt2,tailp);

	g3_project_vertex(&pt2);
	if (pt2.flags & PF_OVERFLOW) 
		return 0.0f;

	if ( (pt1.codes & pt2.codes) != 0 )	{
		// Both off the same side
		return 0.0f;
	}

	headx = pt1.sx;
	heady = pt1.sy;
	headr = (head_width*Matrix_scale.xyz.x*Canv_w2*pt1.sw);

	tailx = pt2.sx;
	taily = pt2.sy;
	tailr = (tail_width*Matrix_scale.xyz.x*Canv_w2*pt2.sw);

	float len_2d = fl_sqrt( (tailx-headx)*(tailx-headx) + (taily-heady)*(taily-heady) );

	// Cap the length if needed.
	if ( (max_len > 1.0f) && (len_2d > max_len) )	{
		float ratio = max_len / len_2d;
	
		tailx = headx + ( tailx - headx ) * ratio;
		taily = heady + ( taily - heady ) * ratio;
		tailr = headr + ( tailr - headr ) * ratio;

		len_2d = fl_sqrt( (tailx-headx)*(tailx-headx) + (taily-heady)*(taily-heady) );
	}

	depth = (pt1.z+pt2.z)*0.5f;

	float max_r  = headr;
	float a;
	if ( tailr > max_r ) 
		max_r = tailr;

	if ( max_r < 1.0f )
		max_r = 1.0f;

	float mx, my, w, h1,h2;

	if ( len_2d < max_r ) {

		h1 = headr + (max_r-len_2d);
		if ( h1 > max_r ) h1 = max_r;
		h2 = tailr + (max_r-len_2d);
		if ( h2 > max_r ) h2 = max_r;

		len_2d = max_r;
		if ( fl_abs(tailx - headx) > 0.01f )	{
			a = (float)atan2( taily-heady, tailx-headx );
		} else {
			a = 0.0f;
		}

		w = len_2d;
		head_on = 1;

	} else {
		a = atan2_safe( taily-heady, tailx-headx );

		w = len_2d;

		h1 = headr;
		h2 = tailr;
		head_on = 0;
	}
	
	mx = (tailx+headx)/2.0f;
	my = (taily+heady)/2.0f;

//	gr_set_color(255,0,0);
//	g3_draw_line( &pt1, &pt2 );

//	gr_set_color( 255, 0, 0 );
//	gr_pixel( fl2i(mx),fl2i(my) );

	// Draw box with width 'w' and height 'h' at angle 'a' from horizontal
	// centered around mx, my

	if ( h1 < 1.0f ) h1 = 1.0f;
	if ( h2 < 1.0f ) h2 = 1.0f;

	float sa, ca;

	sa = (float)sin(a);
	ca = (float)cos(a);

	vertex v[4];
	vertex *vertlist[4] = { &v[3], &v[2], &v[1], &v[0] };
	memset(v,0,sizeof(vertex)*4);

	float sw;
	if ( depth < 0.0f ) depth = 0.0f;
	sw = 1.0f / depth;
	
	v[0].sx = (-w/2.0f)*ca + (-h1/2.0f)*sa + mx;
	v[0].sy = (-w/2.0f)*sa - (-h1/2.0f)*ca + my;
	v[0].z = pt1.z;
	v[0].sw = pt1.sw;
	v[0].u = 0.0f;
	v[0].v = 0.0f;
	v[0].r = (ubyte)r;
	v[0].g = (ubyte)g;
	v[0].b = (ubyte)b;
	v[0].a = 255;

	v[1].sx = (w/2.0f)*ca + (-h2/2.0f)*sa + mx;
	v[1].sy = (w/2.0f)*sa - (-h2/2.0f)*ca + my;
	v[1].z = pt2.z;
	v[1].sw = pt2.sw;
	v[1].u = 1.0f;
	v[1].v = 0.0f;
	v[1].r = (ubyte)r;
	v[1].g = (ubyte)g;
	v[1].b = (ubyte)b;
	v[1].a = 255;

	v[2].sx = (w/2.0f)*ca + (h2/2.0f)*sa + mx;
	v[2].sy = (w/2.0f)*sa - (h2/2.0f)*ca + my;
	v[2].z = pt2.z;
	v[2].sw = pt2.sw;
	v[2].u = 1.0f;
	v[2].v = 1.0f;
	v[2].r = (ubyte)r;
	v[2].g = (ubyte)g;
	v[2].b = (ubyte)b;
	v[2].a = 255;

	v[3].sx = (-w/2.0f)*ca + (h1/2.0f)*sa + mx;
	v[3].sy = (-w/2.0f)*sa - (h1/2.0f)*ca + my;
	v[3].z = pt1.z;
	v[3].sw = pt1.sw;
	v[3].u = 0.0f;
	v[3].v = 1.0f;
	v[3].r = (ubyte)r;
	v[3].g = (ubyte)g;
	v[3].b = (ubyte)b;
	v[3].a = 255;
	
	gr_tmapper(4, vertlist, tmap_flags | TMAP_FLAG_RGB | TMAP_FLAG_GOURAUD | TMAP_FLAG_CORRECT);

	return depth;
}

