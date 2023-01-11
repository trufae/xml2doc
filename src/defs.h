#ifndef _INCLUDE_DEFS_H_
#define _INCLUDE_DEFS_H_

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#ifdef WITH_PDF
  #include <pdflib.h>
#else
  #include "papers.h"
#endif
#include <libxml/parser.h>
#include "output.h"
#define bool int
#define true 1
#define false 0
#include "parm.h"

/* Global vars */

enum
{
	ALIGN_RIGHT,
	ALIGN_LEFT,
	ALIGN_JUSTIFY,
	ALIGN_CENTER
} align;

typedef struct 
{
	int   width,
	      height;
	int   textx,
	      texty;
	int   margetop,
	      margebottom,
	      margeleft,
	      margeright;
	char  align;
	int   font,fsize;
	int   linespacing,
	      wordspacing,
	      charspacing;
	xmlChar *fnt,
	      *path;
	bool  autonum,
	      trim,
	      underline,
	      overline,
	      strikeout,
	      bold;
	bool  page_end;
	unsigned char text_c[3]; // font color
	unsigned char page_c[3]; // page color
} Document;

typedef struct 
{
	/* XML/PDF data */
	xmlDocPtr doc;
	xmlNodePtr cur;
	/* Document data */
	Document now; // Actual data.
	Document std; // Standard data (default one)
} DocStruct;

typedef struct {
	char *name;
	unsigned char rgb[3];
} struct_colors;

typedef struct {
	char *name;
	float w,h;
} struct_pages;

typedef struct {
	char *name;
	int sz;
} struct_sizes;

typedef struct {
	int ncolors,npages,nsizes;
	struct_colors *colors;
	struct_pages  *pages;
	struct_sizes  *sizes;
} AddStruct;

typedef struct
{
#ifdef WITH_PDF
	PDF *p;     // PDF Document
#endif
	FILE *fd;   // File handler
	int page,   // page number
	    output; // O_PDF, O_HTML, O_TXT ...
	bool info;  // info wrotten?
	// Add values
	AddStruct add;
} DocStatic;

extern DocStruct *Doc;
extern DocStatic DocS;
extern unsigned int n;

extern int 
	defs_init(),
	defs_default(),
	defs_update(),
	defs_upload(),
	defs_download(),
	parse(),
	parse_info(),
	parse_page(),
	parse_t(),
	parse_img(),
	parse_bookmark(),
	parse_default(),
	parse_sep(),
	parse_add(),
	parse_include(),
	parse_list();

#endif


