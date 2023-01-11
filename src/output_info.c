#include "output.h"
#include "defs.h"

void output_info()
{
	char 	*creator  =  xmlGetProp(Doc[n].cur,"creator"),
		*author   =  xmlGetProp(Doc[n].cur,"author"),
		*title    =  xmlGetProp(Doc[n].cur,"title"),
		*subject  =  xmlGetProp(Doc[n].cur,"subject"),
		*keywords =  xmlGetProp(Doc[n].cur,"keywords"),
		*trapped  =  xmlGetProp(Doc[n].cur,"trapped");
	struct time_t *timet;
        struct tm *clk;
	
	time((time_t *)&timet);		
	clk=localtime((const time_t *)&timet);

	switch(DocS.output)
	{
	case O_TEXT:
		return;
		break;
	case O_MAN:
		{
		char data[15];
		sprintf(data,"%4.4d-%2.2d-%2.2d",
				clk->tm_year+1900,
				clk->tm_mon+1,
				clk->tm_mday );
		if (creator)  fprintf(DocS.fd,".\\\" Creator: %s\n",creator);
		if (author)   fprintf(DocS.fd,".\\\" Author:  %s\n",author);
		if (keywords) 
			{
			int j,i=strlen(keywords);
			for(j=0;i;i--)if (keywords[i]==' ')j++;
			if (j!=1)
				{
				printf("Invalid Keyword for man output: try: \"NAME NUMBER\" (%s %d).\n",keywords,j);
				exit(1);
				}
			} else {
				printf("keywords: not defined.\n");
				exit(1);
			}
		if (trapped)
			{
				// Check trapped string
			} else {
				printf("trapped: not defined.\n");
			}
		if (title)
			{
				// Check title string.
			} else {
				printf("title: not defined.\n");
			}
		fprintf(DocS.fd,".TH %s %s \"%s\" \"%s\"\n",keywords,data,trapped,title);
		}
		break;
#if WITH_PDF
	case O_PDF:
		if (creator)  PDF_set_info(DocS.p,"Creator",creator);
		if (author)   PDF_set_info(DocS.p,"Author",author);
		if (title)    PDF_set_info(DocS.p,"Title",title);
		if (subject)  PDF_set_info(DocS.p,"Subject",subject);
		if (keywords) PDF_set_info(DocS.p,"Keywords",keywords);
		break;
#endif
	case O_HTML:
		fprintf(DocS.fd,"<head>\n");
		if (title) fprintf(DocS.fd,"  <title>%s</title>\n",title);
		// Write meta's
		fprintf(DocS.fd,"</head>\n");
		break;
	case O_ABIW:
		fprintf(DocS.fd,"<metadata>\n"\
				"  <m key='dc.format'>application/x-abiword</m>\n"\
				"  <m key='abiword.generator'>xml2doc</m>\n"\
				"  <m key='abiword.date_last_changed'>%s  </m>",
				asctime(clk));
		if (author)   fprintf(DocS.fd,"<m key='dc.creator'>%s</m>\n",author);
		if (subject)  fprintf(DocS.fd,"<m key='dc.subject'>%s</m>\n",subject);
		if (title)    fprintf(DocS.fd,"<m key='dc.subject'>%s</m>\n",title);
		if (keywords) fprintf(DocS.fd,"<m key='abiword.keywords'>%s</m>\n",keywords);
		if (creator)  fprintf(DocS.fd,"<m key='dc.publisher'>%s</m>\n",creator);
		fprintf(DocS.fd,"</metadata>\n");
		break;
	}
}

