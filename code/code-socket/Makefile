## [M1]
#  Below command obtains current directory of this MakeFile.
#  $(MAKEFILE_LIST) contains the name of each makefile parsed by make
#  Current Makefile is added at the end of MAKEFILE_LIST
#  Hence $lastword returns name of current MakeFile
#  $realpath returns the absolute path of file "MakeFile"
#  dirname returns the path with its last non-slash component removed.
#  ...
CUR_DIR := $(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))

## [M2]
#  Set the Unix Compiler Command CC to point to GNU compiler gcc
#  += enables the port to append its values to CFLAGS instead of overiding.
#  -Werror makes all warning to errors
#  -Wall turns on certain warning flags about constructions in code
#  LDFLAGS is used for extra flags to give to compiler when invoking linker.
#  ...
CC = gcc
CFLAGS += -g -O2 -Werror -Wall
LDFLAGS +=

## [M3] -- REMOVED
#  ...

## [M5]
#  wildcard funtion gets all c source files in the directory (matching pattern)
#  ...
SRC_FILES = $(wildcard *.c)

## [M6]
#  Converts all .c files obtained in SRC_FILES to EXE files
#  ...
EXE_FILES = $(SRC_FILES:.c=)

## [M7]
#  Assigning the executable files to all to run when "make" command is called.
#  ...
all: $(EXE_FILES)

## [M8] -- UPDATED
#  Below command calls gcc for execution
#  $@ is the target being generated - all
#  $< is the list of first prerequisite
#  ...
%:%.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $< 

## [M9]
#  The rm command will not make a file named clean but it will be executed 
#  everytime make clean is called.
#  ...
clean:
	rm -f $(EXE_FILES)

## [M10]
#  executables are assigned as .PHONY to compile the executables but not 
#  build documentation.
#  make all and make clean will run regardless of whether a file named 
#  all or clean exists.
#  ...
.PHONY: all clean
