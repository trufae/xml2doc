#include "defs.h"

int parse_bookmark(xmlNodePtr p) {
	xmlChar *buf=0;
	int open=0,node=0;
	
	open = parm_bool(xmlGetProp(p,"open"),false);

	if (!(buf=xmlGetProp(p,"node")))
		printf("WARNING: node not defined on bookmark tag. default is 0.\n");
	else node=atoi(buf);

	if (!(buf=xmlGetProp(p,"name"))) {
		printf("No bookmark name defined\n");
		exit(1);
	}

	switch(DocS.output)
	{
#if WITH_PDF
	case O_PDF:
		printf("Bookmark node: %d\n",
			PDF_add_bookmark(DocS.p,buf,node,open));
		break;
#endif
	default:
		printf("No bookmark yet implemented on this output mode.\n");
		break;
	}
	return 0;
}



