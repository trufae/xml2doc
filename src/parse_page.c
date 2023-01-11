#include "defs.h"

int parse_page() {
	int i,err=0;
	xmlChar *str,*str2;
	xmlNodePtr page;

	//if (Doc[n].now.page_begin)
        //	{
//	defs_update();
	//	}

	Doc[n].now.page_end= 
		parm_bool(xmlGetProp(Doc[n].cur,"end"),Doc[n].std.page_end);    	
	parm_color(xmlGetProp(Doc[n].cur,"bgcolor"),
			Doc[n].now.page_c,
			Doc[n].std.page_c);

	parm_color(xmlGetProp(Doc[n].cur,"color"),
			Doc[n].now.text_c,          	
			Doc[n].std.text_c);     

	output_begin_page();

	page=Doc[n].cur->xmlChildrenNode;
	{
	struct _pages {
		char *name;
		float w,h;
	} pages[] = {
		{ "a4",     a4_width,     a4_height },
		{ "a3",     a3_width,     a3_height },
		{ "a2",     a2_width,     a2_height },
		{ "letter", letter_width, letter_height }
	};
	int i,npages=sizeof(pages)/sizeof(struct _pages);

	str=xmlGetProp(Doc[n].cur,"type");
	if (str)
	for(i=0;i<npages;i++)
		{
		if (!strcmp(str,pages[i].name))
			{
			Doc[n].now.width  = pages[i].w;
			Doc[n].now.height = pages[i].h;
			break;
			}
		}
	}
	
	if (xmlGetProp(Doc[n].cur,"left")) 
	   Doc[n].now.margeleft=atof(xmlGetProp(Doc[n].cur,"left"));
	if (xmlGetProp(Doc[n].cur,"top"))
	   Doc[n].now.margetop=Doc[n].now.height-atof(xmlGetProp(Doc[n].cur,"top"));
	if (xmlGetProp(Doc[n].cur,"bottom"))
	   Doc[n].now.margebottom=atof(xmlGetProp(Doc[n].cur,"bottom"));
	
	Doc[n].now.autonum = 
		parm_bool(xmlGetProp(Doc[n].cur,"autonum"),Doc[n].std.autonum);

	if ((str2=xmlGetProp(Doc[n].cur,"num")))
		DocS.page=atoi(str2);

	str=xmlNodeListGetString(Doc[n].doc,page,1);
	
	if (str)
	for( i=strlen(str);i;i-- ) if(str[i]=='\n') str[i]=' ';

	while( page )
	{
		if (!strcmp("t",page->name))  // Text block
			parse_t(page);
		else
		if (!strcmp("img",page->name))  // Image block
			parse_img(page);
		else 
		if (!strcmp("bookmark",page->name)) // bookmark tag
			parse_bookmark(page);
		else
		if (!strcmp("sep",page->name)) // Separator tag
			parse_sep(page);
		else
		if (!strcmp("list",page->name)) // Separator tag
			parse_list(page);
		else
		if (!strcmp("eof",page->name)) {
			err=1; break; }
		else
		if (strcmp("text",page->name)&&
		    strcmp("comment",page->name))
		{
			printf("<page> Unknown tag <%s>\n",page->name);
			exit(1);
		}
		page=page->next; // goto next tag
	}
	
	if ( Doc[n].now.autonum )
		output_autonum();
	
	output_end_page();

	return err;
}


