#include "defs.h"

/*
 * Usage: 
 *
 * <add type="color" name="red">255,0,0</add>
 * <add type="page"  name="poster">100,100</add>
 *
 */

int parse_add() {
	int i,err=0;
	xmlChar *str=xmlNodeListGetString(Doc[n].doc,
		Doc[n].cur->xmlChildrenNode,1),
		*type=xmlGetProp(Doc[n].cur,"type"),
		*name=xmlGetProp(Doc[n].cur,"name");
	
	if (type&&name)
	{
	if (!strcmp(type,"color"))
		{
		// Check exist
		for(i=0;i<DocS.add.ncolors;i++)
		{
			if (!strcmp(name,DocS.add.colors[i].name))
			{
			printf("Color %s already defined.\n",name);
			return 1;
			}
		}
		DocS.add.colors=(struct_colors*)
			realloc(DocS.add.colors, sizeof(struct_colors)*(i+1));
		DocS.add.colors[i].name=(char *)malloc(strlen(name)+1);
		strcpy(DocS.add.colors[i].name,name);
		parm_color(str,DocS.add.colors[i].rgb,Doc[n].std.text_c);
		DocS.add.ncolors++;
		} else
	if (!strcmp(type,"size"))
		{
		} else	
	if (!strcmp(type,"page"))
		{
		}
	} else {
		printf("Tag add without type and name attributes.\n");
	}

	printf("ADD : %s %s (%s)\n",type,name,str);
	return err;
}


