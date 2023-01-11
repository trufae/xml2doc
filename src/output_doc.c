#include "output.h"
#include "defs.h"

void output_begin_doc(char *f)
{
	switch(DocS.output)
	{
#if WITH_PDF
	case O_PDF:
		DocS.p=PDF_new();
		if ( PDF_open_file(DocS.p,f) < 0)
		{
			printf("Cannot open output file for writing \"%s\"\n",f);
			exit(1);
		}
		break;
#endif
	case O_TEXT:
	case O_MAN:
	case O_ABIW:
	case O_HTML:
		if (! (DocS.fd=fopen(f,"w")) )
		{
			printf("Cannot open output file for writing \"%s\"\n",f);
			exit(1);
		}
		switch(DocS.output)
		{
			case O_HTML:
				fprintf(DocS.fd,"<html>\n");
				break;
			case O_MAN:
				fprintf(DocS.fd,".\\\" Generated with xml2doc.\n");
				break;
			case O_ABIW:
				fprintf(DocS.fd,"<abiword>\n");
				break;
		}
		break;
	}
}

void output_end_doc()
{
	switch (DocS.output)
	{
#if WITH_PDF
	case O_PDF:
		PDF_close(DocS.p);
		PDF_delete(DocS.p);
		break;
#endif
	case O_HTML:
		fprintf(DocS.fd,"</html>\n");
	case O_ABIW:
		if (DocS.output==O_ABIW)
		fprintf(DocS.fd,"</abiword>\n");
	case O_MAN:
	case O_TEXT:
		fclose(DocS.fd);
		break;
	}
}


