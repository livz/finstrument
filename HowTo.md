# Content of the project #
## Makefile ##

**make normal**:
  * builds normal binary without debug and trace info
**make debug** or **make**:
  * build the trace version, linked with trace.o object
**make clean**:
  * deletes object files (`*`.o)
**make clean\_all**:
  * deletes objects, trace output file and binary

For details on flags and options, see Makefile

## Sources ##
  1. trace.c:
> > Source for the trace library. Details on the way it works here: http://farabilet.blogspot.com/2011/01/trace-function-calls-with-gcc.html
  1. prog.c:
> > Example program
  1. parse.py:
> > Parses the output (trace.out, defined in trace.c) and replaces function address with their corresponding names and location. Uses the addr2line utility from binutils. For usage :
> > ./parse.py -h

## Example ##
```
$ make debug
$ ./prog
$ ./parse.py -p prog -t trace.out
```