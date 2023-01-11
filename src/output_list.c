#include "defs.h"
#include "output.h"

void output_list ( char *titol , char *type ,
		int depth , int pag , unsigned char *link, int space) {
	int i;
//	unsigned char *text = (unsigned char *) malloc(strlen(str) + 4);

	printf("WARNING: <list> tag will change in the future\n");
	
	switch(DocS.output){
		case O_TEXT:	
			for(i=0; i<depth; i++) 
				fprintf(DocS.fd,"  ");

			if(!strcmp(type,"normal" )) 
			{
				fprintf(DocS.fd , "o %s", titol);	
			} else 
			if(! strcmp(type,"index")  )
			{
				fprintf(DocS.fd,"- %s",titol);
				for(i=0;i < 76-(depth*2)-strlen(titol)-4-1;i++ )
					fprintf(DocS.fd , "." );
				fprintf(DocS.fd,"%i",pag);
			}
			fprintf(DocS.fd,"\n");
			break;

		case O_HTML:
			printf("%i\t" , depth);
			depth = depth * space ;
			printf("%i\n" , depth);
			fprintf(DocS.fd , "<TABLE width=\"100\%\"> ");
			fprintf(DocS.fd , "<td width=%i> </td>" , depth);
			
			if (!strcmp(type,"normal"))
			{
				fprintf(DocS.fd, "<TD>");
				if(link) 					
				    fprintf(DocS.fd, "<a href=\"%s\">", link);
				fprintf(DocS.fd , "<ul><li>");
				output_t(titol);
				fprintf(DocS.fd , "</ul></li>");
				if(link) fprintf(DocS.fd , "</a>");
				fprintf(DocS.fd , "</TD>\n");
			} else 
			if (!strcmp(type,"index")) 
			{
				fprintf(DocS.fd, "<TD width=\"90%\">");
                                if (link)
				    fprintf(DocS.fd, "<a href=\"%s\">", link);
				fprintf(DocS.fd, "<ul><li>");
				output_t(titol);
				fprintf(DocS.fd, "</ul></li>");
				if (link) fprintf(DocS.fd, "</a>");
				fprintf(DocS.fd, 
					"</TD align=\"right\"><TD>%i</TD>\n",pag); 
			}
			fprintf(DocS.fd , "</TABLE>");
			break;
			
		case O_PDF:
			printf("WARNING: List output not implemented on PDF.\n");
			break;
			
		case O_MAN:
			for(i=0; i<depth; i++) 
				fprintf(DocS.fd , "  " );
			if(strcmp(type,"normal" )== 0) 
				fprintf(DocS.fd , "o %s", titol);	
			else if( strcmp(type,"index") ==0 ){
				fprintf(DocS.fd , "=%s", titol);
				for(i=0;
			 i < 76-(depth*2)-strlen(titol)-4;
				   i++ )
					fprintf(DocS.fd , "." );
				fprintf(DocS.fd , "%i" , pag );

				}
				fprintf(DocS.fd , "\n");
			break;
		case O_ABIW:
			break;
	}
}
