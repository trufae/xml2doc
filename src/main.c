#include "main.h"

/*
 *
 * PDF_set_value(p,"nameofvalue",(float)value); // get/set
 *   - leading, textrise, textrendering,leading,horzscaling,
 *   
 */

int
main(int argc, char **argv, char **envp)
{
	int err=0;
	if (argc<4)
	{
		printf( "xml2doc - %s version - contact: pancake@phreaker.net\n"\
			"Please usage %s [-o?] [input.xml] [output.pdf]\n"\
			"  -oH : Html output\n"
			#ifdef WITH_PDF
			"  -oP : PDF output\n"
			#endif
			"  -oT : Text output\n"\
			"  -oM : Manpage output\n"\
			"  -oA : Abiword output\n",VERSION,argv[0]);
		return 1;
	}

	Doc=(DocStruct *)malloc(sizeof(DocStruct));

	defs_init();    // Init static struct
        defs_default(); // Init dynamic struct

	if (strlen(argv[1])>=2)
	{
		int w=1;
		if (argv[1][0]=='-') w++;
		switch(argv[1][w])
		{
		case 'H': DocS.output=O_HTML; break;
		#ifdef WITH_PDF
		case 'P': DocS.output=O_PDF;  break;
		#endif
		case 'T': DocS.output=O_TEXT; break;
		case 'M': DocS.output=O_MAN;  break;
		case 'A': DocS.output=O_ABIW; break;
		default:
			  printf("Invalid output format.\n");
			  exit(1);
			  break;
		}
	} 
	
	if( access(argv[2],R_OK) ) {
		printf("Cannot open input file \"%s\"\n",argv[2]);
		return 1;
	}

	defs_default(); // Set default values

	output_begin_doc(argv[3]);

	err=parse(argv[2]);

	output_end_doc();

	return err;
}



