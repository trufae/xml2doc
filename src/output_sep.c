#include "output.h"
#include "defs.h"

void output_sep(int line, int space, int size, int width)
{
	int i, char_to_use;
	char text_char[] = { '.' , '_' , '-' , '=' , '#' };
	
	if (width)
	width=((Doc[n].now.margeright-Doc[n].now.margeleft)-width)/2;

	switch(DocS.output)
	{
#if WITH_PDF
	case O_PDF:
		PDF_setcolor(DocS.p,"both","rgb",
						(float)((float)Doc[n].now.text_c[0]/(float)255),
						(float)((float)Doc[n].now.text_c[1]/(float)255),
						(float)((float)Doc[n].now.text_c[2]/(float)255) ,0.0f );
		PDF_setlinewidth(DocS.p,size);
		PDF_setdash(DocS.p,line,space); // definir puntejat de linea
		PDF_save(DocS.p);
		Doc[n].now.texty+=PDF_get_value(DocS.p,"leading",0)*2;
		PDF_moveto(DocS.p,Doc[n].now.margeleft+width,
				Doc[n].now.margetop-Doc[n].now.texty);
		PDF_lineto(DocS.p,Doc[n].now.margeright-width,
				Doc[n].now.margetop-Doc[n].now.texty);
		PDF_stroke(DocS.p);
		PDF_restore(DocS.p);
		break;
#endif
	case O_HTML:
		fprintf(DocS.fd,"<hr>\n");
		break;
	case O_TEXT:
		if( (int) size >= sizeof(text_char) )
			char_to_use=sizeof(text_char)-1;
		else	char_to_use=(int) size;
		fprintf(DocS.fd,"\n");
		for(i=0; i<79; i++) 
			fprintf(DocS.fd,"%c" , char_to_use[text_char]);
		fprintf(DocS.fd,"\n");
		break;
	}
}


