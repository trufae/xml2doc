#include "defs.h"

int parse(const char *file)
{
	Doc[n].doc=xmlParseFile(file);
	if (!Doc[n].doc)
	{
		printf("Invalid XML document\n");
		return 1;
	}
	Doc[n].cur=xmlDocGetRootElement(Doc[n].doc);
	if( xmlStrcmp(Doc[n].cur->name,(const xmlChar *)"xmldoc") &&
	    xmlStrcmp(Doc[n].cur->name,(const xmlChar *)"xml2doc") )
	{
		printf("Isn't a xmldoc document (is <%s>)\n",Doc[n].cur->name);
		return 1;
	}

	Doc[n].cur=Doc[n].cur->xmlChildrenNode;

	while(Doc[n].cur)
	{
		defs_update();
		printf("WIDTH: %d\n",Doc[n].now.width);

		if (!strcmp("default",Doc[n].cur->name)) {
			parse_default();
		} else
		if (!strcmp("reset",Doc[n].cur->name)) {
			defs_default();
		} else
		if (!strcmp("info",Doc[n].cur->name)) {
			parse_info();
		} else
		if (!strcmp("page",Doc[n].cur->name)) {
			if ( parse_page() ) break;
		} else 
		if (!strcmp("include",Doc[n].cur->name)) {
			parse_include();
		} else
		if (!strcmp("add",Doc[n].cur->name)) {
			parse_add();
		} else
		if (!strcmp("eof",Doc[n].cur->name)) {
			break; // Force eof!
		} else
		if (strcmp("text",Doc[n].cur->name) &&
		    strcmp("comment",Doc[n].cur->name)) {
			printf("<xmldoc> Unknown tag: <%s>\n",Doc[n].cur->name);
			exit(1);
		}
		Doc[n].cur=Doc[n].cur->next;
	}

	return 0;
}



