#include "defs.h"

int parse_t(xmlNodePtr page) {
	xmlChar *str,*str2;

	Doc[n].now.textx=Doc[n].std.textx;
	str=xmlNodeListGetString(Doc[n].doc,page->xmlChildrenNode,1);
	if (xmlGetProp(page,"font"))
		Doc[n].now.fnt=xmlGetProp(page,"font");
	else Doc[n].now.fnt=Doc[n].std.fnt;

	Doc[n].now.fsize = 
		parm_value(xmlGetProp(page,"size"),
			&Doc[n].std.fsize,Doc[n].std.fsize);

#if WITH_PDF
	if (DocS.output==O_PDF)
	Doc[n].now.font=PDF_findfont(DocS.p,Doc[n].now.fnt,"host",0);
#endif

	// Text Decoration
	Doc[n].now.underline = 
		parm_bool(xmlGetProp(page,"underline"),Doc[n].std.underline);
	Doc[n].now.overline =
		parm_bool(xmlGetProp(page,"overline"),Doc[n].std.overline);
	Doc[n].now.strikeout =
		parm_bool(xmlGetProp(page,"strikeout"),Doc[n].std.strikeout);
	Doc[n].now.bold =
		parm_bool(xmlGetProp(page,"bold"),Doc[n].std.bold);

	if ((str2=xmlGetProp(page,"wordspacing")))
		Doc[n].now.wordspacing=atoi(str2);
	 else Doc[n].now.wordspacing=Doc[n].std.wordspacing;
	
	if ((str2=xmlGetProp(page,"charspacing")))
		Doc[n].now.charspacing=atoi(str2);
	 else Doc[n].now.charspacing=Doc[n].std.charspacing;

	if ((str2=xmlGetProp(page,"linespacing")))
		Doc[n].now.linespacing=atoi(str2);
	else Doc[n].now.linespacing=Doc[n].std.linespacing;

	//printf("LEADING %f\n",PDF_get_value(Doc[n].p,"leading",0.0f));
	
	Doc[n].now.trim =
		parm_bool(xmlGetProp(page,"trim"),Doc[n].std.trim);

        if ((str2=xmlGetProp(page,"align")))
	{
        	if (!strcmp(str2,"right"))
			Doc[n].now.align=ALIGN_RIGHT; else
		if (!strcmp(str2,"left"))
			Doc[n].now.align=ALIGN_LEFT; else
		if (!strcmp(str2,"center"))
			Doc[n].now.align=ALIGN_CENTER; else
		if (!strcmp(str2,"justify"))
		        Doc[n].now.align=ALIGN_JUSTIFY;
		else printf("<t> Invalid value \"%s\" in property \"%s\"\n",str2,"align");
	} else
	Doc[n].now.align=Doc[n].std.align;
	
	parm_color(xmlGetProp(page,"color"),Doc[n].now.text_c,Doc[n].std.text_c);

	if (xmlGetProp(page,"x")) Doc[n].now.textx = atof(xmlGetProp(page,"x"));
	if ( (str2=xmlGetProp(page,"y")) )
	{
		float lead=0;
#if WITH_PDF
		lead==PDF_get_value(DocS.p,"leading",0.0f);
#endif
		if (!strcmp(str2,"up")) 
		{
			if (Doc[n].now.align!=ALIGN_CENTER)
			Doc[n].now.texty-=lead+Doc[n].now.linespacing;
		}
		else
		Doc[n].now.texty = atof(xmlGetProp(page,"y"));
	}

	output_t(str);
	
	return 0;
}




