#include "output.h"
#include "defs.h"

void output_autonum()
{
	switch(DocS.output)
	{
	case O_TEXT:
		printf("%78d\n",DocS.page-1);
		break;
#if WITH_PDF
	case O_PDF:
		{
		char str[10];
		PDF_set_parameter(DocS.p,"underline","false");
		PDF_set_parameter(DocS.p,"overline","false");
		PDF_set_parameter(DocS.p,"strikeout","false");
		Doc[n].now.font=PDF_findfont(DocS.p,"Helvetica","host",0);
		PDF_setfont(DocS.p,Doc[n].now.font,10);
		PDF_set_text_pos(DocS.p,
				Doc[n].now.width-Doc[n].now.margeleft,
				Doc[n].now.margebottom*2/3);
		sprintf(str,"%d",DocS.page-1);
		PDF_setcolor(DocS.p,"both","rgb",.0f,.0f,.0f,0.0f);
		PDF_continue_text(DocS.p,str);
		}
		break;
#endif
	case O_ABIW:
		printf("Warning: No autonum supported yet on abiword output\n");
		break;
	}
}

void output_begin_page()
{
	switch(DocS.output)
	{
#if WITH_PDF
	case O_PDF:
		PDF_begin_page(DocS.p,Doc[n].now.width,Doc[n].now.height);
		PDF_set_text_pos(DocS.p,Doc[n].now.margeleft,Doc[n].now.margetop);
		if ( Doc[n].now.page_c[0]<255 ||
		     Doc[n].now.page_c[1]<255 ||
		     Doc[n].now.page_c[2]<255 )
		{
		PDF_save(DocS.p);
		  PDF_setlinewidth(DocS.p,30);
		  PDF_setcolor(DocS.p,"both","rgb",
				  (float)Doc[n].now.page_c[0]/255,
				  (float)Doc[n].now.page_c[1]/255,
				  (float)Doc[n].now.page_c[2]/255,0.0f);
		  PDF_rect(DocS.p,0,0,Doc[n].now.width,Doc[n].now.height);
		  PDF_fill(DocS.p);
		PDF_restore(DocS.p);
		}
		break;
#endif
	case O_HTML:
		fprintf(DocS.fd,
			"<div class='page' style='background-color:#%.2x%.2x%.2x' >\n",
				(int)Doc[n].now.page_c[0],
				(int)Doc[n].now.page_c[1],
				(int)Doc[n].now.page_c[2]
				);
		break;
	case O_ABIW:
		// what about pagesize!??!
		fprintf(DocS.fd,
			"<section props='background-color:%.2x%.2x%.2x'>\n",
			  (int)Doc[n].now.page_c[0],
			  (int)Doc[n].now.page_c[1],
			  (int)Doc[n].now.page_c[2]
			  );
		if (DocS.page) fprintf(DocS.fd,"<p><pbr/></p>\n");
		break;
	}
}

void output_end_page()
{
	DocS.page++;
	printf ("ENDING PAGE\n");
	switch(DocS.output)
	{
#if WITH_PDF
	case O_PDF:
		PDF_end_page(DocS.p);
		break;
#endif
	case O_TEXT:
		fprintf(DocS.fd,"\n--\n\n");
		break;
	case O_HTML:
		fprintf(DocS.fd,"</div>\n<hr>\n");
		break;
	case O_ABIW:
		fprintf(DocS.fd,"</section>\n");
		break;
	}
}


