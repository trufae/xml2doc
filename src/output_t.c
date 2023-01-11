#include "output.h"
#include "defs.h"

void output_t(unsigned char *str)
{
	int i,j,len,len2;

	len2 = xmlUTF8Strlen(str);
	len  = strlen(str);
	UTF8Toisolat1(str,&len,str,&len);
	for( str[i=len=len2]=0;i;i-- ) if(str[i]=='\n') str[i]=0;
	if ( str[0]=='\n' ) str[0]=0;
	
	if ( Doc[n].now.trim )
	{ // Trim string.
		int j,i=0;
		while(i<len)
		{
		for(j=i;str[i]==' ';i++);
		memcpy (str+j,str+i,len2-j);
		len-=(i-j)+1;
		i+=strlen(str+i)+1;
		}
	}                                  	
	
        switch(DocS.output)
	{
	case O_ABIW:
		fprintf(DocS.fd,
				// text-align:center
			"<p props='font-size:%d;"\
			"color:%.2x%.2x%.2x;margin-left:%dmm'>\n",
			  Doc[n].now.fsize,
			  (int)Doc[n].now.text_c[0],
			  (int)Doc[n].now.text_c[1],
			  (int)Doc[n].now.text_c[2],
			  (int)(Doc[n].now.textx/5)
			);
		for( i=0;i<len;i+=strlen(str+i)+1 )
		{
			int j;
			for(j=0;j<strlen(str+i);j++)
				if (str[i+j]>'~') str[i+j]='_';
			fprintf(DocS.fd,
				"<c props='color:%.2x%.2x%.2x;font-size:%dpt'>%s</c>",
					Doc[n].now.text_c[0],
					Doc[n].now.text_c[1],
					Doc[n].now.text_c[2],
					Doc[n].now.fsize,
					str+i);
		}
		fprintf(DocS.fd,"</p>\n");
		break;
	case O_MAN:
		for(i=0;i<len;i+=strlen(str+i)+1 )
		{
			if (Doc[n].now.fsize>Doc[n].std.fsize)
				fprintf(DocS.fd,".SH %s\n\n",str+i);
			else
			if (Doc[n].now.underline)
				fprintf(DocS.fd,".I %s\n.br\n",str+i);
			else
			if (Doc[n].now.bold)
				fprintf(DocS.fd,".BR %s\n",str+i);
			else
				fprintf(DocS.fd,"%s\n",str+i);
		}
		break;
        case O_TEXT:
		for(  i=0;   i<len;  i+=strlen(str+i)+1 )
		{
			if (strlen(str+i)+(int)(Doc[n].now.textx/10)>78)
			{
				for(	j=78-(int)(Doc[n].now.textx/10);
					j && str[i+j]!=' ';
					j-- );
				str[i+j]=0;
			}
			switch(Doc[n].now.align)
			{
			case ALIGN_LEFT:
				for(j=0;j<(Doc[n].now.textx/10);j++)fprintf(DocS.fd," ");
	                	fprintf(DocS.fd,"%s\n",str+i);
				break;
			case ALIGN_RIGHT:
				fprintf(DocS.fd,"%78s\n",str+i);
				break;
			case ALIGN_CENTER:
				len2=(int)((78-strlen(str+i))/2);
				while(len2--) fprintf(DocS.fd," ");
				fprintf(DocS.fd,"%s\n",str+i);
				break;
			case ALIGN_JUSTIFY:
				{
				fprintf(DocS.fd,"%s\n",str+i);
				printf("JUSTIFY on Text output not yet implemented\n");
				break;
				}
			}
		}
                break;
#if WITH_PDF
	case O_PDF:
		PDF_set_value(DocS.p,"wordspacing",Doc[n].now.wordspacing);
		PDF_set_value(DocS.p,"charspacing",Doc[n].now.charspacing);
		PDF_setfont(DocS.p,Doc[n].now.font,Doc[n].now.fsize);
		PDF_set_parameter(DocS.p,"underline",(Doc[n].now.underline)?"true":"false");
		PDF_set_parameter(DocS.p,"overline",(Doc[n].now.overline)?"true":"false");
		PDF_set_parameter(DocS.p,"strikeout",(Doc[n].now.strikeout)?"true":"false");
		PDF_set_text_pos(DocS.p,
		                 Doc[n].now.margeleft+Doc[n].now.textx,
		                 Doc[n].now.margetop-Doc[n].now.texty);

		for (i=0;i<len;i+=strlen(str+i)+1)
		{
			int plusx=0; // variable to center and right align text
			// Wrap text loop
			j=PDF_stringwidth(DocS.p,str+i,Doc[n].now.font,Doc[n].now.fsize); 
			if (j && j > ( Doc[n].now.margeright-Doc[n].now.margeleft-Doc[n].now.textx) )
			{
				j = (((Doc[n].now.margeright-Doc[n].now.margeleft-
						Doc[n].now.textx)*strlen(str+i))/j)-3;
				for(j=j;j&&str[i+j]!=' ';j--);
				str[i+j]=0;
			}
			
			switch(Doc[n].now.align)
			{
			case ALIGN_CENTER:
				plusx=( Doc[n].now.margeright-Doc[n].now.margeleft-
					PDF_stringwidth(DocS.p,str+i,Doc[n].now.font,Doc[n].now.fsize) )/2;
				plusx-=Doc[n].now.textx;
				break;
			case ALIGN_RIGHT:
				plusx=( Doc[n].now.margeright-Doc[n].now.margeleft-Doc[n].now.textx-
					PDF_stringwidth(DocS.p,str+i,Doc[n].now.font,Doc[n].now.fsize) );
				plusx-=Doc[n].now.textx;
				break;
			case ALIGN_JUSTIFY:
				{
				float ws=0,l=0.0f,k=0.1f;
				printf("Warning using justify!\n");
				for(	ws=0.0f,l=PDF_stringwidth(DocS.p,str+i,Doc[n].now.font,Doc[n].now.fsize);
					l!=k&&l<(Doc[n].now.margeright-Doc[n].now.margeleft-Doc[n].now.textx);
					ws+=0.1f )
					{
					PDF_set_value(DocS.p,"wordspacing",ws+Doc[n].now.wordspacing);
					printf("%f\n",PDF_get_value(DocS.p,"wordspacing",0));
					k=l;
					l=PDF_stringwidth(DocS.p,str+i,
							  Doc[n].now.font,
							  Doc[n].now.fsize);
					};
				PDF_set_value(DocS.p,"wordspacing",ws+Doc[n].now.wordspacing);
				}
				break;
			}
			
			Doc[n].now.texty=Doc[n].now.margetop-PDF_get_value(DocS.p,"texty",0);
			Doc[n].now.texty+=PDF_get_value(DocS.p,"leading",0)+Doc[n].now.linespacing;
			PDF_set_text_pos(DocS.p,
				Doc[n].now.margeleft+Doc[n].now.textx + plusx,
				Doc[n].now.margetop-Doc[n].now.texty);

			//printf("WIDTH %f\n",		PDF_stringwidth(DocS.p,str+i,Doc[n].now.font,Doc[n].now.fsize));
			//PDF_set_value(DocS.p,"charspacing",100);
			//printf("WIDTH %f\n",		PDF_stringwidth(DocS.p,str+i,Doc[n].now.font,Doc[n].now.fsize));
			//	PDF_continue_text(DocS.p,str+i);
			
			if (PDF_get_value(DocS.p,"texty",0)<Doc[n].now.margebottom)
			{
			if (Doc[n].now.autonum)
				output_autonum();
			output_end_page();
			output_begin_page();
			PDF_set_text_pos(DocS.p,Doc[n].now.margeleft+Doc[n].now.textx,Doc[n].now.margetop);
			DocS.page++;
			}
			PDF_setfont(DocS.p,Doc[n].now.font,Doc[n].now.fsize);

			PDF_setcolor(DocS.p,"both","rgb",
						(float)((float)Doc[n].now.text_c[0]/(float)255),
						(float)((float)Doc[n].now.text_c[1]/(float)255),
						(float)((float)Doc[n].now.text_c[2]/(float)255) ,0.0f );			
			PDF_show(DocS.p,str+i);
		}
		Doc[n].now.textx=PDF_get_value(DocS.p,"textx",0);
		Doc[n].now.texty=Doc[n].now.margetop-PDF_get_value(DocS.p,"texty",0);
                PDF_setcolor(DocS.p,"both","rgb",
                                    (float)((float)Doc[n].std.text_c[0]/(float)255),
                                    (float)((float)Doc[n].std.text_c[1]/(float)255),
                                    (float)((float)Doc[n].std.text_c[2]/(float)255) ,0.0f );
		break;
#endif
	case O_HTML:
		fprintf(DocS.fd,"<div ");
		switch(Doc[n].now.align)
		{
		case ALIGN_CENTER:
			fprintf(DocS.fd,"align='center' ");
			break;
		case ALIGN_RIGHT:
			fprintf(DocS.fd,"align='right' ");
			break;
		case ALIGN_JUSTIFY:
			fprintf(DocS.fd,"align='justify' ");
			break;
		}
		
		fprintf(DocS.fd,"style='position:relative;left:%dpx;",
				(int)(10+Doc[n].now.textx));
		fprintf(DocS.fd,"color:#%.2x%.2x%.2x;",
				(int)Doc[n].now.text_c[0],
				(int)Doc[n].now.text_c[1],
				(int)Doc[n].now.text_c[2] );
		fprintf(DocS.fd,"font-size:%d;",4+Doc[n].now.fsize);
		if (!strncmp(Doc[n].now.fnt,"Helvetica",9))
			fprintf(DocS.fd,"font-family:Verdana;");
		else
		if (!strncmp(Doc[n].now.fnt,"Courier",7))
			fprintf(DocS.fd,"><tt");
		fprintf(DocS.fd,"'>\n");

		// Bold OBlique.. :) posar tags <b> i <i> -- seria mes maco font-weight:..
		
		for(i=0;i<len;i+=strlen(str+i)+1)
		{
			fprintf(DocS.fd,"%s<br>\n",str+i);
		}

		if (!strncmp(Doc[n].now.fnt,"Courier",7))
			fprintf(DocS.fd,"</tt>");
		fprintf(DocS.fd,"</div>\n");
		break;
	}
}


