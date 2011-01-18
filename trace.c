#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

static FILE *pTraceFile;
static int indent = -1;

void __attribute__ ((constructor))
trace_begin (void)
{
	pTraceFile = fopen("trace.out", "w");
	if(pTraceFile == NULL) {
		printf ("Error opening file: %s\n",strerror(errno));
		exit(1);
	}
}

void __attribute__ ((destructor))
trace_end (void)
{
	if(pTraceFile != NULL) {
		fclose(pTraceFile);
	}
	else{
		printf ("Error in %s: %s\n", __FUNCTION__, strerror(errno));
	}
}

void __attribute__ ((no_instrument_function))
__cyg_profile_func_enter (void *func, void *caller)
{
 /* Function Entry Address */
    unsigned char i;
    time_t rawTime;
    struct tm * timeInfo;

    time ( &rawTime );
    timeInfo = localtime ( &rawTime );
  
    indent++;    
    
	if(pTraceFile != NULL) {
        for(i = 1; i<indent; ++i) {
            fprintf(pTraceFile, " ");
        }
		fprintf(pTraceFile, "Entered 0x%08X from 0x%08X at %s", \
		(unsigned int)func, (unsigned int)caller, asctime(timeInfo) );
	}
	else{
		printf ("Error in %s: %s\n", __FUNCTION__, strerror(errno));
	}
}

void __attribute__ ((no_instrument_function))
__cyg_profile_func_exit (void *func, void *caller)
{
    unsigned char i;
    time_t rawTime;
    struct tm * timeInfo;

    time ( &rawTime );
    timeInfo = localtime ( &rawTime );
    
	if(pTraceFile != NULL) {
        for(i = 1; i<indent; ++i) {
            fprintf(pTraceFile, " ");
        }
        indent--;
		fprintf(pTraceFile, "Exiting 0x%08X at %s", \
		(unsigned int)func, asctime(timeInfo));
	}
	else{
		printf ("Error in %s: %s\n", __FUNCTION__, strerror(errno));
	}
}
