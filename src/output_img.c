#include "output.h"
#include "defs.h"

void output_image(char *src, char *type, char *text, float s,int x,int y)
{
#if WITH_PDF
	int img,imgh;
#endif
	switch(DocS.output)
	{
#if WITH_PDF
	case O_PDF:
		img=PDF_open_image_file(DocS.p,type,src,"",0);
		if (img<0)
		{
			printf("Error loading image %s as %s.\n",src,type); 
			return;
		}
		imgh = PDF_get_value(DocS.p, "imageheight", (float) img);
		PDF_place_image(DocS.p,
			img,x+Doc[n].now.margeleft,
			Doc[n].now.margetop-Doc[n].now.texty-y-(imgh*s),s);
		Doc[n].now.texty+=PDF_get_value(DocS.p,"imageheight",(float)img)*s;
		Doc[n].now.textx+=PDF_get_value(DocS.p,"imagewidth",(float)img);
		PDF_close_image(DocS.p,img);
		if (text)
		{
			printf("FootText on Img unsupported on PDF output...\n");
		}
		break;
#endif
	case O_TEXT:
		fprintf(DocS.fd,"[ %s ]",src);
		if (text) fprintf(DocS.fd," (%s)\n",text);
		else fprintf(DocS.fd,"\n");
		break;
	case O_HTML:
		if (x==Doc[n].now.textx && y==Doc[n].now.texty)
			fprintf(DocS.fd,"<img src='%s'>\n",src);
		else
		{
			s*=100.0f;
			fprintf(DocS.fd, "<div style='position:absolute;top:%d;left:%d;'>\n",x,y);
			fprintf(DocS.fd,"<img src='%s' border='0' ",src);
			if (text) fprintf(DocS.fd," title='%s' ",text);
			if (s!=1.0f) fprintf(DocS.fd, "width='%.0f%%' height='%.0f%%'",s,s);
			fprintf(DocS.fd, ">\n</div>\n");
		}
		break;
	case O_ABIW:
		printf("Warning: Image on Abiword documents, not supported yet.\n");
		break;
	}
}


