#include "parm.h"

bool parm_bool(const char *str, bool ref)
{
	if (!str) return ref;
	if (	(!strcmp(str,"true"))  ||
		(!strcmp(str,"yes"))   ||
		(!strcmp(str,"on"))    ||
		(!strcmp(str,"1"))      )
	{
		return true;
	} else
	if (	(!strcmp(str,"false")) ||
		(!strcmp(str,"no"))    ||
		(!strcmp(str,"off"))   ||
		(!strcmp(str,"0"))      )
	{
		return false;
	} else
	if (	(!strcmp(str,"toggle")) ||
		(!strcmp(str,"swap"))    )
	{
		return (ref)?false:true;
	} else
	return false;
}

int parm_align(const char *str, int align)
{
	return 0;
}

int parm_value(char *str, int *ref,int total)
{
	int i, ret=*ref;

	if (!str) return ret;
	if (!strlen(str)) return ret;
	for(i=strlen(str);i;i--)
		if (str[i]<'0' || str[i]>'9' ) break;
	printf ("Total %d\n",total);
	if (i) 
	{
	bool less=0, plus=0, perc=0, equa=0;
	int ptr;

	if (strlen(str)>1)
		{
		if (str[strlen(str)-1]=='%') {
			perc=true; str[strlen(str)-1]=0; }
		if (str[0]=='+') plus=true;
		if (str[0]=='-') less=true;
		if (str[plus+less]=='=') equa=true;
		ptr=plus+less+equa;
		// Symbolworks
		if (perc) 
		{
			if (plus) ret+=(total*atoi(str+ptr)/100);
			if (less) ret-=(total*atoi(str+ptr)/100);
		} else {
			if (plus) ret+=atoi(str+ptr);
			if (less) ret-=atoi(str+ptr);
			if (!plus&&!less&&!perc&&!equa) ret=atoi(str); // if!sym
			}
		}
		if (equa) *ref=ret;
	} else ret=atoi(str);

	if (ret<1)
	{
		printf("WARNING: Value %d <= 0; changed to 1 for sanity reasons\n",ret);
		ret=1;
		if (*ref<1) *ref=ret;
	}
	return ret;
}

void parm_color(const char *str, unsigned char *ptr, unsigned char ref[3])
{
	unsigned char naw[3];
	int i,ncolors;
	struct_colors colors[]= {
		{ "red",   { 255,  0,  0 } },
		{ "green", {   0,255,  0 } },
		{ "blue",  {   0,  0,255 } },
		{ "gray",  { 150,150,150 } },
		{ "yellow",{ 255,255,  0 } },
		{ "orange",{ 255,100,  0 } },
		{ "black", {   0,  0,  0 } },
		{ "white", { 255,255,255 } },
		{ "cyan",  {   0,255,255 } }
	};

	if (!str) 
	 { memcpy(ptr,ref,3); return; }

	for(i=0;i<DocS.add.ncolors;i++)
	{
		if (!strcmp(str,DocS.add.colors[i].name))
		{
		int j;
		for(j=0;j<3;j++)
		naw[j]=DocS.add.colors[i].rgb[j];
		break;
		}
	}

	if (i==DocS.add.ncolors) // not found
	{
	ncolors=sizeof(colors)/sizeof(struct_colors);
	for(i=0;i<ncolors;i++)
	  { 
		if (!strcmp(str,colors[i].name))
		{
		int j;
		for(j=0;j<3;j++)
		naw[j]=colors[i].rgb[j];
		break;
		}
	  }

	if (ncolors==i)
	{
	if (strlen(str)==7)
		{
	  	if ( !strncmp(str,"rgb:",4) ) 
	   		{
			for(i=0;i<3;i++)
			naw[i]=(str[i+4]-'0')*25;
			}
	   	else if (str[0]=='#')
	   	{
			char b[10];
                	int col;
			for(i=0;i<3;i++)
			{
			memcpy(b,str+1+(i*2),2); b[3]=0;
			sscanf(b,"%x",&col);
			naw[i]=(unsigned char)col;
			}
	   	} else {
		   printf("Unknown value for color: \"%s\"\n",str);
		}
	} else {
		printf("Unknown value for color: \"%s\"\n",str);
		}
	} } // } } }  ... xD

	memcpy(ptr,naw,3);

	return;
}


