#include "defs.h"

int parse_sep(xmlNodePtr page)
{
	int	line=0,
		space=0,
		size=1,
		width=0;

	parm_color(xmlGetProp(page,"color"),Doc[n].now.text_c,Doc[n].std.text_c);
	
	line = parm_value(xmlGetProp(page,"line"), &line, 100);
	space = parm_value(xmlGetProp(page,"space"), &space, 100);
	size  = parm_value(xmlGetProp(page,"size"),  &size,  100);
	width = parm_value(xmlGetProp(page,"width"), &width, 
			Doc[n].now.margeright-Doc[n].now.margeleft);

	output_sep(line,space,size,width);
	return 0;
}


