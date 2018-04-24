#ifndef cabrite2d_log_h
#define cabrite2d_log_h

#include<stdio.h>

struct log{
	FILE *f;
};

void log_init(struct log *log,FILE *f);
void log_printf(struct log * log,const char *format,...);

#endif
