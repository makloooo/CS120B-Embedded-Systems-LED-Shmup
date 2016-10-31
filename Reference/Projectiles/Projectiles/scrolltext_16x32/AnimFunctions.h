#ifndef ANIMFUNCTIONS_H_
#define ANIMFUNCTIONS_H_

#include "Bitmaps.h"

void draw_ship(byte& x, byte& y, Colors& coreColor);
void draw_cross(byte& x, byte& y, byte& frame, Colors& clr);
void draw_tracer(byte& x, byte& y, byte& frame, byte frm_delay);
void draw_panel(byte& x, byte& y, byte& frame, byte frm_delay);
void draw_eyeball(byte& x, byte& y, byte& frame, byte frm_delay);
void draw_explosion_l(byte& x, byte& y, byte& frame, byte frm_delay, Colors& clr);

#endif /* ANIMFUNCTIONS_H_ */