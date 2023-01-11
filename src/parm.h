#ifndef _INCLUDE_PARM_H_
#define _INCLUDE_PARM_H_

#include "defs.h"

bool  parm_bool  (const char *str, bool ref);
int   parm_align (const char *str, int align);
void  parm_color (const char *str, unsigned char *ptr, unsigned char *ref);
int   parm_value (char *str,int *ref,int total);


/*
float my_atof(char *str)
{
	str=atof(str);
	if (!str) {
		printf("Error getting float value.");
		exit(1);
	}
	return str;
}

 GetProperty from 
int float_getprop(xmlNodePtr *p, xmlChar *s, float *v)
{
	xmlChar *str;
	float val;
	
	str=xmlGetProp(p,s);
	if (!str) return 1;

	val=atof(str);
	if (!val)
	{
		if (strlen(str)>3)
		{
		if (!strncmp(str,"+=")) *v+=my_atof(str+2);
		else
		if (!strncmp(str,"-=")) *v-=my_atof(str+2);
		} else
		if (strlen(str)==2)
		{
		if (!strcmp(str,"--")) *v-=Doc.
		}
	}

	return 0;
}
*/
#endif
