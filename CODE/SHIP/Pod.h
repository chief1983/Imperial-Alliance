#ifndef __POD_H__
#define __POD_H__

struct object;

#define CAP_SHIP_JAMMER_RANGE	20.0f

int pod_start(object *objp);
void pod_stop(object *objp);
void pod_stop_sounds();
void pod_update(object *objp, float fl_frametime);
void pod_level_init();

int maybe_jam_weapons(object *objp);

int is_in_front_in_box(object *objp);

void maybe_disable_pod(object *objp);

#endif /* __POD_H__ */
