#out: hash_table.c
#	gcc -g -Wall hash_table.c hash_table.o -o out
#	gcc -o a.out -g -Wall hash_table.c

#hash_table_tests: hash_table_tests.c hash_table.c
#	# gcc -Wall hash_table_tests -lcunit -o hash_table_tests.c hash_table.c

#Prep for better Makefile, seems to have issue with CUnit library
main: myprog

C_COMPILER     = gcc
C_OPTIONS      = -Wall -pedantic -g
C_LINK_OPTIONS = -lm 
CUNIT_LINK     = -lcunit

%.o:  %.c
	$(C_COMPILER) $(C_OPTIONS) $^ -c 

myprog: hash_table_tests.o hash_table.o
	$(C_COMPILER) $(C_LINK_OPTIONS) $^ -o $@

#myprog.final: file1.o file2.o file3.o
# TODO: add e.g. optimisation flags, remove unnecessary linking, etc.

clean:
	rm -f *.o myprog

#test1: mytests1.o file1.o 
#  $(C_COMPILER) $(C_LINK_OPTIONS) $? -o $@ $(CUNIT_LINK) 
#
#test2: mytests2.o file2.o file3.o
#  $(C_COMPILER) $(C_LINK_OPTIONS) $? -o $@ $(CUNIT_LINK) 
#
#test: test1 test2
#  ./test1 
#  ./test2