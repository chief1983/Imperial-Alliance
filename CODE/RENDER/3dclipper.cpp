/*
 * Copyright (C) Volition, Inc. 1999.  All rights reserved.
 *
 * All source code herein is the property of Volition, Inc. You may not sell 
 * or otherwise commercially exploit the source or things you created based on the 
 * source.
 *
*/

/*
 * $Logfile: /Freespace2/code/Render/3dClipper.cpp $
 * $Revision: 1.1.1.1 $
 * $Date: 2004/08/13 22:47:43 $
 * $Author: Spearhawk $
 *
 * Polygon clipping functions
 *
 * $Log: 3dclipper.cpp,v $
 * Revision 1.1.1.1  2004/08/13 22:47:43  Spearhawk
 * no message
 *
 * Revision 1.1.1.1  2004/08/13 21:33:08  Darkhill
 * no message
 *
 * Revision 2.5  2003/08/30 14:49:01  phreak
 * fixed some random specular lighting bugs
 *
 * Revision 2.4  2003/08/16 03:52:24  bobboau
 * update for the specmapping code includeing
 * suport for seperate specular levels on lights and
 * optional strings for the stars table
 * code has been made more organised,
 * though there seems to be a bug in the state selecting code
 * resulting in the HUD being rendered incorectly
 * and specmapping failing ocasionaly
 *
 * Revision 2.3  2003/08/12 03:18:34  bobboau
 * Specular 'shine' mapping;
 * useing a phong lighting model I have made specular highlights
 * that are mapped to the model,
 * rendering them is still slow, but they look real purdy
 *
 * also 4 new (untested) comand lines, the XX is a floating point value
 * -spec_exp XX
 * the n value, you can set this from 0 to 200 (actualy more than that, but this is the recomended range), it will make the highlights bigger or smaller, defalt is 16.0 so start playing around there
 * -spec_point XX
 * -spec_static XX
 * -spec_tube XX
 * these are factors for the three diferent types of lights that FS uses, defalt is 1.0,
 * static is the local stars,
 * point is weapons/explosions/warp in/outs,
 * tube is beam weapons,
 * for thouse of you who think any of these lights are too bright you can configure them you're self for personal satisfaction
 *
 * Revision 2.2  2002/08/06 01:49:08  penguin
 * Renamed ccode members to cc_or and cc_and
 *
 * Revision 2.1  2002/08/01 01:41:09  penguin
 * The big include file move
 *
 * Revision 2.0  2002/06/03 04:02:27  penguin
 * Warpcore CVS sync
 *
 * Revision 1.1  2002/05/02 18:03:12  mharris
 * Initial checkin - converted filenames and includes to lower case
 *
 * 
 * 2     10/07/98 10:53a Dave
 * Initial checkin.
 * 
 * 1     10/07/98 10:51a Dave
 * 
 * 13    4/10/98 5:20p John
 * Changed RGB in lighting structure to be ubytes.  Removed old
 * not-necessary 24 bpp software stuff.
 * 
 * 12    3/23/98 5:00p John
 * Improved missile trails.  Made smooth alpha under hardware.  Made end
 * taper.  Made trail touch weapon.
 * 
 * 11    3/16/98 4:51p John
 * Added low-level code to clip all polygons against an arbritary plane.
 * Took out all old model_interp_zclip and used this new method instead.  
 * 
 * 10    1/23/98 5:08p John
 * Took L out of vertex structure used B (blue) instead.   Took all small
 * fireballs out of fireball types and used particles instead.  Fixed some
 * debris explosion things.  Restructured fireball code.   Restructured
 * some lighting code.   Made dynamic lighting on by default. Made groups
 * of lasers only cast one light.  Made fireballs not cast light.
 * 
 * 9     9/09/97 3:39p Sandeep
 * warning level 4 bugs
 * 
 * 8     3/10/97 5:20p John
 * Differentiated between Gouraud and Flat shading.  Since we only do flat
 * shading as of now, we don't need to interpolate L in the outer loop.
 * This should save a few percent.
 * 
 * 7     3/10/97 2:25p John
 * Made pofview zbuffer.   Made textest work with new model code.  Took
 * out some unnecessary Asserts in the 3d clipper.
 * 
 * 
 * 6     12/23/96 11:00a John
 * Restructured POF stuff to support LOD in one pof.
 * 
 * 5     11/06/96 2:33p John
 * Added more asserts for checking that non-tiled UV's are between 0 and
 * 1.0.    Put code in the model_init code that checks for polys that have
 * a vertex duplicated and throws them out.
 *
 * $NoKeywords: $
 */

#include "render/3dinternal.h"
#include "graphics/tmapper.h"

int free_point_num=0;

vertex temp_points[TMAP_MAX_VERTS];
vertex *free_points[TMAP_MAX_VERTS];

void init_free_points(void)
{
	int i;

	for (i=0;i<TMAP_MAX_VERTS;i++)
		free_points[i] = &temp_points[i];
}


vertex *get_temp_point()
{
	vertex *p;

	p = free_points[free_point_num++];

	p->flags = PF_TEMP_POINT;

	return p;
}

void free_temp_point(vertex *p)
{
	Assert(p->flags & PF_TEMP_POINT);

	free_points[--free_point_num] = p;

	p->flags &= ~PF_TEMP_POINT;
}

//clips an edge against one plane.
vertex *clip_edge(int plane_flag,vertex *on_pnt,vertex *off_pnt, uint flags)
{
	float ratio;
	vertex *tmp;

	tmp = get_temp_point();

	if ( plane_flag & CC_OFF_USER )	{

		// Clip with user-defined plane
		vector w, ray_direction;
		float num,den;

		vm_vec_sub(&ray_direction,(vector *)&off_pnt->x,(vector *)&on_pnt->x);
			
		vm_vec_sub(&w,(vector *)&on_pnt->x,&G3_user_clip_point);
	
		den = -vm_vec_dot(&G3_user_clip_normal,&ray_direction);
		if ( den == 0.0f ) {	// Ray & plane are parallel, so there is no intersection
			Int3();	// Get John
			ratio = 1.0f;
		} else {
			num =  vm_vec_dot(&G3_user_clip_normal,&w);
	
			ratio = num / den;
		}

		tmp->x = on_pnt->x + (off_pnt->x-on_pnt->x) * ratio;
		tmp->y = on_pnt->y + (off_pnt->y-on_pnt->y) * ratio;
		tmp->z = on_pnt->z + (off_pnt->z-on_pnt->z) * ratio;

	} else {
		float a,b,kn,kd;

		//compute clipping value k = (xs-zs) / (xs-xe-zs+ze)
		//use x or y as appropriate, and negate x/y value as appropriate

		if (plane_flag & (CC_OFF_RIGHT | CC_OFF_LEFT)) {
			a = on_pnt->x;
			b = off_pnt->x;
		}
		else {
			a = on_pnt->y;
			b = off_pnt->y;
		}

		if (plane_flag & (CC_OFF_LEFT | CC_OFF_BOT)) {
			a = -a;
			b = -b;
		}

		kn = a - on_pnt->z;						//xs-zs
		kd = kn - b + off_pnt->z;				//xs-zs-xe+ze

		ratio = kn / kd;

		tmp->x = on_pnt->x + (off_pnt->x-on_pnt->x) * ratio;
		tmp->y = on_pnt->y + (off_pnt->y-on_pnt->y) * ratio;

		if (plane_flag & (CC_OFF_TOP|CC_OFF_BOT))	{
			tmp->z = tmp->y;
		} else {
			tmp->z = tmp->x;
		}

		if (plane_flag & (CC_OFF_LEFT|CC_OFF_BOT))
			tmp->z = -tmp->z;

	}

	if (flags & TMAP_FLAG_TEXTURED) {
		tmp->u = on_pnt->u + (off_pnt->u-on_pnt->u) * ratio;
		tmp->v = on_pnt->v + (off_pnt->v-on_pnt->v) * ratio;

		tmp->env_u = on_pnt->env_u + (off_pnt->env_u-on_pnt->env_u) * ratio;
		tmp->env_v = on_pnt->env_v + (off_pnt->env_v-on_pnt->env_v) * ratio;
	}

	if (flags & TMAP_FLAG_GOURAUD ) {
		if (flags & TMAP_FLAG_RAMP) {

			float on_b, off_b;

			on_b = i2fl(on_pnt->b);
			off_b = i2fl(off_pnt->b);

			tmp->b = ubyte(fl2i(on_b + (off_b-on_b) * ratio));
		}
		if (flags & TMAP_FLAG_RGB) {
			float on_r, on_b, on_g, onspec_r, onspec_g, onspec_b;
			float off_r, off_b, off_g, offspec_r, offspec_g, offspec_b;

			on_r = i2fl(on_pnt->r);
			off_r = i2fl(off_pnt->r);

			on_g = i2fl(on_pnt->g);
			off_g = i2fl(off_pnt->g);

			on_b = i2fl(on_pnt->b);
			off_b = i2fl(off_pnt->b);


			onspec_r = i2fl(on_pnt->spec_r);
			offspec_r = i2fl(off_pnt->spec_r);

			onspec_g = i2fl(on_pnt->spec_g);
			offspec_g = i2fl(off_pnt->spec_g);

			onspec_b = i2fl(on_pnt->spec_b);
			offspec_b = i2fl(off_pnt->spec_b);


			tmp->r = ubyte(fl2i(on_r + (off_r-on_r) * ratio));
			tmp->g = ubyte(fl2i(on_g + (off_g-on_g) * ratio));
			tmp->b = ubyte(fl2i(on_b + (off_b-on_b) * ratio));

			tmp->spec_r = ubyte(fl2i(onspec_r + (offspec_r-onspec_r) * ratio));
			tmp->spec_g = ubyte(fl2i(onspec_g + (offspec_g-onspec_g) * ratio));
			tmp->spec_b = ubyte(fl2i(onspec_b + (offspec_b-onspec_b) * ratio));
		}
	}
	else
	{
		tmp->spec_r=tmp->spec_g=tmp->spec_b=0;
	}

	if (flags & TMAP_FLAG_ALPHA) {

		float on_a, off_a;

		on_a = i2fl(on_pnt->a);
		off_a = i2fl(off_pnt->a);

		tmp->a = ubyte(fl2i(on_a + (off_a-on_a) * ratio));
	}

	g3_code_vertex(tmp);

	return tmp;	
}

//clips a line to the viewing pyramid.
void clip_line(vertex **p0,vertex **p1,ubyte codes_or, uint flags)
{
	int plane_flag;
	vertex *old_p1;

	for (plane_flag=1;plane_flag<=CC_OFF_USER;plane_flag<<=1)
		if (codes_or & plane_flag) {

			if ((*p0)->codes & plane_flag)
				{vertex *t=*p0; *p0=*p1; *p1=t;}	//swap!

			old_p1 = *p1;

			*p1 = clip_edge(plane_flag,*p0,*p1,flags);
			codes_or = (unsigned char)((*p0)->codes | (*p1)->codes);	//get new codes

			if (old_p1->flags & PF_TEMP_POINT)
				free_temp_point(old_p1);
		}

}

int clip_plane(int plane_flag,vertex **src,vertex **dest,int *nv,ccodes *cc,uint flags)
{
	int i;
	vertex **save_dest=dest;

	//copy first two verts to end
	src[*nv] = src[0];
	src[*nv+1] = src[1];

	cc->cc_and = 0xff;
	cc->cc_or = 0;

	for (i=1;i<=*nv;i++) {

		if (src[i]->codes & plane_flag) {				//cur point off?

			if (! (src[i-1]->codes & plane_flag)) {	//prev not off?

				*dest = clip_edge(plane_flag,src[i-1],src[i],flags);
				cc->cc_or  |= (*dest)->codes;
				cc->cc_and &= (*dest)->codes;
				dest++;
			}

			if (! (src[i+1]->codes & plane_flag)) {

				*dest = clip_edge(plane_flag,src[i+1],src[i],flags);
				cc->cc_or  |= (*dest)->codes;
				cc->cc_and &= (*dest)->codes;
				dest++;
			}

			//see if must free discarded point

			if (src[i]->flags & PF_TEMP_POINT)
				free_temp_point(src[i]);
		}
		else {			//cur not off, copy to dest buffer

			*dest++ = src[i];

			cc->cc_or  |= src[i]->codes;
			cc->cc_and &= src[i]->codes;
		}
	}

	return (dest-save_dest);
}


vertex **clip_polygon(vertex **src,vertex **dest,int *nv,ccodes *cc,uint flags)
{
	int plane_flag;
	vertex **t;

	for (plane_flag=1;plane_flag<=CC_OFF_USER;plane_flag<<=1)

		if (cc->cc_or & plane_flag) {

			*nv = clip_plane(plane_flag,src,dest,nv,cc,flags);

			if (cc->cc_and)		//clipped away
				return dest;

			t = src; src = dest; dest = t;

		}

	return src;		//we swapped after we copied
}








