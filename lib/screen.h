#ifndef CABRITE_2D_SCREEN_H
#define CABRITE_2D_SCREEN_H
#include <stdbool.h>

struct render;

void screen_initrender(struct render *R);
void screen_init(float w,float h,float scale);
void screen_trans(float *x,float *y);
void screen_scissor(int x,int y,int w,int h);
bool screen_is_visible(float x,float y);

#endif
