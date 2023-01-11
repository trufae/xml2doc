#ifndef _INCLUDE_OUTPUT_H_
#define _INCLUDE_OUTPUT_H_

#include <time.h>


enum
{
	O_HTML=0,
	O_PDF, 
	O_TEXT,
	O_MAN,
	O_ABIW
};


void 	output_begin_page(),
	output_end_page(),
	output_autonum(),
	output_begin_doc(char *f),
	output_end_doc(),
	output_image(char *f,char *type, char *text, float s, int x, int y),
	output_info(),
	output_sep(int line,int space,int size,int width),
	output_list (char *titol,char *type ,
		int depth , int pag , unsigned char *link, int space), 
	output_t();

#endif

