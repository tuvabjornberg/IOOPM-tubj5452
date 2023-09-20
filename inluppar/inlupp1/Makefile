main: myprog

C_COMPILER     = gcc
C_OPTIONS      = -Wall -pedantic -g
C_LINK_OPTIONS = -lm 
CUNIT_LINK     = -lcunit

%.o:  %.c
	$(C_COMPILER) $(C_OPTIONS) $^ -c 

myprog: hash_table.o linked_list.o
	$(C_COMPILER) $(C_LINK_OPTIONS) $^ -o $@

test1: hash_table_tests.o hash_table.o 
	$(C_COMPILER) $(C_LINK_OPTIONS) $^ -o $@ $(CUNIT_LINK) 

test2: linked_list_tests.o linked_list.o
	$(C_COMPILER) $(C_LINK_OPTIONS) $^ -o $@ $(CUNIT_LINK) 

test: test1 test2
	./test1 
	./test2

clean:
	rm -f *.o myprog test1 test2
