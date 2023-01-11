#include "defs.h"

int parse_img(xmlNodePtr page) {
	int r,x,y;
	float s;
	xmlChar *type,*src,*buf,*text=0;

	if (!xmlGetProp(page,"src") ) { 
		printf("No src attribute on <img tag>\n"); return 1; }
	else   src=xmlGetProp(page,"src");
	type=xmlGetProp(page,"type");
	r=strlen(src)-3;
	if (!type)
	{
		if (!strcmp("png",src+r))  type="png"; else
		if (!strcmp("pg",src+r+1)) type="jpeg"; else
		if (!strcmp("gif",src+r))  type="gif"; else
		if (!strcmp("iff",src+r))  type="tiff";
	}

	text=xmlGetProp(page,"text");

	x = parm_value( xmlGetProp(page,"x"), 
		&Doc[n].now.textx, Doc[n].now.width);

	y = parm_value( xmlGetProp(page,"y"),
		&Doc[n].now.texty, Doc[n].now.width);

	buf=xmlGetProp(page,"scale");
	if (!buf)  s=1.0f; else s=atof(buf);
					
	output_image(src,type,text,s,x,y);

	return 0;
}



