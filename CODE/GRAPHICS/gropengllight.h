/*
 * Copyright (C) Volition, Inc. 1999.  All rights reserved.
 *
 * All source code herein is the property of Volition, Inc. You may not sell 
 * or otherwise commercially exploit the source or things you created based on the 
 * source.
 *
*/


/*
 * $Logfile: /Freespace2/code/Graphics/GrOpenGLLight.h $
 * $Revision: 1.1.1.1 $
 * $Date: 2004/08/13 22:47:41 $
 * $Author: Spearhawk $
 *
 * header file containing definitions for HT&L lighting in OpenGL
 *
 * $Log: gropengllight.h,v $
 * Revision 1.1.1.1  2004/08/13 22:47:41  Spearhawk
 * no message
 *
 * Revision 1.1.1.1  2004/08/13 20:47:09  Darkhill
 * no message
 *
 * Revision 1.1  2004/05/24 07:25:32  taylor
 * filename case change
 *
 * Revision 2.4  2004/04/26 13:02:27  taylor
 * light setup changes, support cmdline ambient value
 *
 * Revision 2.3  2004/04/13 01:55:41  phreak
 * put in the correct fields for the CVS comments to register
 * fixed a glowmap problem that occured when rendering glowmapped and non-glowmapped ships
 *
 *
 * $NoKeywords: $
 */

#ifndef _GROPENGLLIGHT_H
#define _GROPENGLLIGHT_H

#define MAX_LIGHTS 256

//Constants
const int MAX_OPENGL_LIGHTS = 8; //temporary - will change to dynamic allocation and get rid of this later -Fry_Day

enum
{
	LT_DIRECTIONAL,		// A light like a sun
	LT_POINT,			// A point light, like an explosion
	LT_TUBE,			// A tube light, like a fluorescent light
};

//Variables
extern struct opengl_light opengl_lights[MAX_LIGHTS];
extern bool active_light_list[MAX_LIGHTS];
extern int currently_enabled_lights[MAX_OPENGL_LIGHTS];
extern bool lighting_is_enabled;
extern int max_gl_lights;
extern int active_gl_lights;
extern int n_active_gl_lights;

struct ogl_light_struct_col
{
		float r,g,b,a;
};

struct ogl_light_struct_pos 
{
		float x,y,z,w;
};

// Structures
struct opengl_light{
	opengl_light():occupied(false), priority(1){};
	ogl_light_struct_col Diffuse, Specular, Ambient;
	ogl_light_struct_pos Position;
	float ConstantAtten, LinearAtten, QuadraticAtten;
	bool occupied;
	int priority;
};

struct light_data;


//Functions
void FSLight2GLLight(opengl_light *GLLight, light_data *FSLight);
int	gr_opengl_make_light(light_data* light, int idx, int priority);		//unused -- stub function
void gr_opengl_modify_light(light_data* light, int idx, int priority);	//unused -- stub function
void gr_opengl_destroy_light(int idx);									//unused -- stub function
void gr_opengl_set_light(light_data *light);
void gr_opengl_reset_lighting();
void gr_opengl_set_lighting(bool set, bool state);
void opengl_pre_render_init_lights();
void opengl_change_active_lights(int);
void opengl_init_light();

#endif //_GROPENGLLIGHT_H
