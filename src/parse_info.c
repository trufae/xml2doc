#include "defs.h"

int parse_info()
{
	if (DocS.info) 
	{
		// Could be nice to put an -strict flag.
		return 0;
	}
	
	DocS.info=true;
	output_info();

	return 0;
}



