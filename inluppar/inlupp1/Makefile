main: driver

C_COMPILER     = gcc
C_OPTIONS      = -Wall -pedantic -g
C_LINK_OPTIONS = -lm 
CUNIT_LINK     = -lcunit

%.o:  %.c #%.h $<
	$(C_COMPILER) $(C_OPTIONS) $^ -c 

driver: hash_table.o linked_list.o
	$(C_COMPILER) $(C_LINK_OPTIONS) $^ -o $@

hash_test: hash_table_tests.o hash_table.o linked_list.o 
	$(C_COMPILER) $(C_LINK_OPTIONS) $^ -o $@ $(CUNIT_LINK) 

list_test: linked_list_tests.o linked_list.o
	$(C_COMPILER) $(C_LINK_OPTIONS) $^ -o $@ $(CUNIT_LINK) 

test: hash_test list_test
	./hash_test 
	./list_test

#.PHONY: test

clean:
	rm -f *.o driver hash_test list_test

hash_mem: hash_test
	valgrind --leak-check=full ./hash_test

list_mem: list_test
	valgrind --leak-check=full ./list_test

#.PHONY: main test clean
