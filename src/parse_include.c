#include "defs.h"

int parse_include()
{
	xmlChar *str;

	if (( str=xmlGetProp(Doc[n].cur,"src") ))
	{
		defs_upload();
		parse(str);
		defs_download();
	} else {
		printf("<include> src attribute not defined\n");
		exit(1);
	}

	return 0;
}
