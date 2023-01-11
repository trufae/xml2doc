#include "defs.h"

int parse_default()
{
	xmlChar *str;

	if (xmlGetProp(Doc[n].cur,"font") )  
	   Doc[n].std.fnt=xmlGetProp(Doc[n].cur,"font");

	Doc[n].std.autonum =
		parm_bool(xmlGetProp(Doc[n].cur,"autonum"),Doc[n].std.autonum);

	if (xmlGetProp(Doc[n].cur,"size"))
		Doc[n].std.fsize=atoi(xmlGetProp(Doc[n].cur,"size"));
	if (xmlGetProp(Doc[n].cur,"linespacing"))
		Doc[n].std.linespacing=atoi(xmlGetProp(Doc[n].cur,"linespacing"));
	if (xmlGetProp(Doc[n].cur,"wordspacing"))
		Doc[n].std.wordspacing=atoi(xmlGetProp(Doc[n].cur,"wordspacing"));
	if (xmlGetProp(Doc[n].cur,"charspacing"))
		Doc[n].std.charspacing=atoi(xmlGetProp(Doc[n].cur,"charspacing"));
	if (xmlGetProp(Doc[n].cur,"x"))
		Doc[n].std.textx=atof(xmlGetProp(Doc[n].cur,"x"));
	if (xmlGetProp(Doc[n].cur,"y"))
		Doc[n].std.texty=atof(xmlGetProp(Doc[n].cur,"y"));
	if (xmlGetProp(Doc[n].cur,"margetop"))
		Doc[n].std.margetop=atof(xmlGetProp(Doc[n].cur,"margetop"));
	if (xmlGetProp(Doc[n].cur,"margebottom"))
		Doc[n].std.margebottom=atof(xmlGetProp(Doc[n].cur,"margebottom"));
	if (xmlGetProp(Doc[n].cur,"margeleft"))
		Doc[n].std.margeleft=atof(xmlGetProp(Doc[n].cur,"margeleft"));
	if (xmlGetProp(Doc[n].cur,"margeright"))
		Doc[n].std.margeright=Doc[n].std.width-atof(xmlGetProp(Doc[n].cur,"margeright"));

	Doc[n].std.trim =
		parm_bool(xmlGetProp(Doc[n].cur,"trim"), true);
	Doc[n].std.underline =
		parm_bool(xmlGetProp(Doc[n].cur,"underline"), false);
	Doc[n].std.overline =
		parm_bool(xmlGetProp(Doc[n].cur,"overline"), false);
	Doc[n].std.strikeout =
		parm_bool(xmlGetProp(Doc[n].cur,"strikeout"), false);

        parm_color(xmlGetProp(Doc[n].cur,"bgcolor"),
		                Doc[n].std.page_c,
		                Doc[n].std.page_c);

        parm_color(xmlGetProp(Doc[n].cur,"color"),
	                        Doc[n].std.text_c,
	                        Doc[n].std.text_c);     

	if ((str=xmlGetProp(Doc[n].cur,"align")))
	{
		if (!strcmp(str,"right"))
			Doc[n].std.align=ALIGN_RIGHT; else
		if (!strcmp(str,"left"))
			Doc[n].std.align=ALIGN_LEFT; else
		if (!strcmp(str,"center"))
			Doc[n].std.align=ALIGN_CENTER; else
		if (!strcmp(str,"justify"))
			Doc[n].std.align=ALIGN_JUSTIFY;
		else printf("<default> Invalid value \"%s\" in property \"%s\"\n",str,"align");
	}

	return 0;
}


