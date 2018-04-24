#include<stdarg.h>
#include<stdlib.h>
#include "log.h"
#include "platform_print.h"

void
log_init(struct log *log,FILE *f){
	log->f = f;
};

void
log_printf(struct log *log,const char *format,...){
	if(format[0] == '!'){
		va_list ap;
		va_start(ap,format);
		pf_vprint(format + 1,ap);
		va_end(ap);
	}else{
		va_list ap;
		va_start(ap,format);
		pf_vprint(format,ap);
		va_end(ap);
		exit(1);
	}
}
