#include "defs.h"

int defs_init()
{
	DocS.page=0;
	DocS.info=false;
	DocS.add.ncolors=
	DocS.add.npages=
	DocS.add.nsizes=0;
	DocS.add.colors=(struct_colors *)malloc(1);
	DocS.add.pages =(struct_pages  *)malloc(1);
	DocS.add.sizes =(struct_sizes  *)malloc(1);
}

int defs_default() // Set default values
{
	Doc[n].std = (Document)
	{
	  a4_width,
	  a4_height,
	  0.0f,
	  0.0f,
	  // -----------------[ Marges
	  a4_height-60, //   top
	  80,           //   bottom
	  50,           //   left
	  a4_width-50,  //   right
	  ALIGN_LEFT, // default text align
	  0,12,  // font/fsize
	  2,0,0, // Linespacing, wordspacing, charspacing
	  "Times-Roman", // *fnt
	  "./",  // *path
	  false,  // autonum
          true,   // trim strings
	  false,  //underline
	  false, // overline
	  false,  // strikeout
	  false,
	  true, // begin/end page
	  {0,0,0}, // black
	  {255,255,255} // white
	};
	return 0;
}

int defs_download()
{
	n--;
	return 0;
}

int defs_upload() // upload defs from inner include;
{
	n++;
	if (n>10)
	{
		printf("Please don't overflow my poor include support :\"\n");
		exit(1);
	}
	Doc=(DocStruct*)realloc(Doc,sizeof(DocStruct)*(n+1));
	memcpy(&Doc[n],&Doc[n-1],sizeof(DocStruct));
	return 0;
}

int defs_update() // set now options to std ones
{
	memcpy(&Doc[n].now,&Doc[n].std,sizeof(Document));
	return 0;
}


