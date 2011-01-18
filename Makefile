CC=/usr/bin/gcc

SRC=prog.c
TRACE_SRC=trace.c

OBJ=prog.o
TRACE_OBJ=trace.o

OUT=trace.out

CFLAGS_NORMAL=-Wall
CFLAGS_TRACE=-Wall -finstrument-functions -g

EXE=prog

debug: 
	$(CC) $(CFLAGS_TRACE) -c -o $(OBJ) $(SRC)
	$(CC) $(CFLAGS_NORMAL) -c -o $(TRACE_OBJ) $(TRACE_SRC)
	$(CC) $(OBJ) $(TRACE_OBJ) -o $(EXE)
    
normal:
	$(CC) $(CFLAGS_NORMAL) -o $(EXE) $(SRC)
    
clean:
	rm -rf  $(OBJ) $(TRACE_OBJ)
    
clean_all:
	rm -rf $(EXE) $(OUT) $(OBJ) $(TRACE_OBJ)
