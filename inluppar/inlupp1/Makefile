C_COMPILER     = gcc
C_OPTIONS      = -Wall -pedantic -g 
C_OPTIONS_PROF = -pg
C_LINK_OPTIONS = -lm 
CUNIT_LINK     = -lcunit

%.o:  %.c #%.h  $<
	$(C_COMPILER) $(C_OPTIONS) $^ -c  

freq_count: hash_table.o linked_list.o freq_count.o
	$(C_COMPILER) $(C_LINK_OPTIONS) $(C_OPTIONS) $^ -o $@ 

freq_count_prof: hash_table.o linked_list.o freq_count.o
	$(C_COMPILER) $(C_LINK_OPTIONS) $(C_OPTIONS) $(C_OPTIONS_PROF) $^ -o $@ 

hash_test: hash_table_tests.o hash_table.o linked_list.o 
	$(C_COMPILER) $(C_LINK_OPTIONS) $^ -o $@ $(CUNIT_LINK) 

list_test: linked_list.o linked_list_tests.o
	$(C_COMPILER) $(C_LINK_OPTIONS) $^ -o $@ $(CUNIT_LINK) 

test: hash_test list_test
	./hash_test 
	./list_test

clean:
	rm -f *.o *.out driver hash_test list_test

mem_test: hash_test list_test
	valgrind --leak-check=full ./hash_test
	valgrind --leak-check=full ./list_test

freq_count_mem: freq_count
	valgrind --leak-check=full ./driver $(ARGS) 

.PHONY: freq_count test hash_mem list_mem freq_count_mem clean
