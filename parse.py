#!/usr/bin/env python

# Parse output trace file from a binary compiled with -finstrument-functions flag
# Replaces function addresses with name and location of functions
# ...using addr2line utility from binutils

import sys
import getopt
import re
import os.path
from os import popen

def usage() :
    print "Usage: parse.py -p <program binary> -t <trace file>"    
    print "    Example: parse.py -p prog -t trace.out"

def main(argv):
    argCount = 0
    
    # Parse command line arguments
    try:                                
        opts, args = getopt.getopt(argv, "hp:t:", ["help", "program=", "trace="]) 
    except getopt.GetoptError:  
        usage()                         
        sys.exit(1)        
    for opt, arg in opts:                
        if opt in ("-h", "--help"):      
            usage()                     
            sys.exit(1)                  
        elif opt in ("-p", "--program"): 
            program = arg   
            if os.path.exists(program):
                print "Parse traces from %s ..." % (program)
                argCount = argCount +1
            else:
                print "Inexisent binary file"
                sys.exit(2)                
        elif opt in ("-t", "--trace"):
            traceFile = arg
            if os.path.exists(traceFile):
                print ".. using tracefile %s." % (traceFile)
                argCount = argCount +1
            else:
                print "Inexisent trace file"
                sys.exit(2)
    if argCount != 2 :
        usage()
        print "Not enough arguments. Exiting..."
        sys.exit(2)

    # Search and replace addresses with names and location
    cmd = "cat "+traceFile
    cmdOut = popen(cmd)

    # Parse each line and extract each function once
    for eachLine in cmdOut.readlines():
        # Keep line indentation
        indent = 0
        while eachLine[indent] == ' ':
            print ' ',
            indent = indent + 1
            
        for word in eachLine.rsplit():            
            funcAddr = re.search("0x[0-9A-F]*", word)
            if funcAddr != None:                
                funcName = ((popen("addr2line -f -e " + program +" " + funcAddr.group(0) + "|head -1")).readlines()[0]).strip()
                funcLoc = ((popen("addr2line -s -e " + program +" " + funcAddr.group(0))).readlines()[0]).strip()
                print "%s(%s)" % (funcName, funcLoc),
            else:
                print word,
        print "\n",

    cmdOut.close()
    
if __name__ == "__main__":
    main(sys.argv[1:])
