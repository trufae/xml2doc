#ifndef _INCLUDE_MAIN_H_
#define _INCLUDE_MAIN_H_

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#ifdef WITH_PDF
#include <pdflib.h>
#endif
#include <libxml/parser.h>
#include "defs.h"

/* Global vars */
unsigned int n=0;
DocStruct *Doc=NULL;
DocStatic DocS; // Static data in document

int main (int argc, char **argv, char **envp);

#endif 


