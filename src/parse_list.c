#include "defs.h"

int parse_list(xmlNodePtr page ) 
{
	xmlChar *titol, *type, *link;
	int pag=0,depth=0, space=20;

	titol = xmlGetProp(page,"titol");
	if ( xmlGetProp(page,"depth") )  
		depth = atoi(xmlGetProp(page,"depth") );

	type = xmlGetProp(page,"type");
      
	if (type && !strcmp(type,"index") && xmlGetProp(page,"pag") )
	{
		pag = atoi(xmlGetProp(page,"pag"));
	} else 
	if( type && !strcmp(type,"index") && !xmlGetProp(page,"pag") ) 
	{
		printf("si vols fer un index cal posar una pagina \n");
		return -1; 
	}
	parm_color( xmlGetProp(page,"color"),
			Doc[n].now.text_c,Doc[n].std.text_c);
	link = xmlGetProp(page,"link");
	if (!titol) 
	{
		printf("necesitu un nom per la llista :(\n");
		return -1;
	}
	if ( xmlGetProp(page,"space") ) 
		space=atoi(xmlGetProp(page,"space"));
     
	if (!type) type="normal";
	      
	output_list(titol , type , depth , pag , link, space );    
      
	return 0;
}
