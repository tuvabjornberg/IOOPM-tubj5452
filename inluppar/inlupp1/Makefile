C_COMPILER     = gcc 
C_OPTIONS      = -Wall -pedantic -g 
C_GCOV		   = -fprofile-arcs -ftest-coverage 
C_OPTIONS_PROF = -pg
C_LINK_OPTIONS = -lm
CUNIT_LINK     = -lcunit
PG_OPT		   = -pg

%.o:  %.c #%.h  $<
	$(C_COMPILER) $(C_OPTIONS) $^ -c  

freq_count.out: hash_table.o linked_list.o freq_count.o
	$(C_COMPILER) $(C_LINK_OPTIONS) $(C_OPTIONS) $^ -o $@ 

freq_count_prof.out: freq_count.c hash_table.c linked_list.c
	$(C_COMPILER) $(C_OPTIONS) $(PG_OPT) $^ -o $@ 

hash_test: hash_table_tests.o hash_table.o linked_list.o 
	$(C_COMPILER) $(C_GCOV) $(C_LINK_OPTIONS) $^ -o $@ $(CUNIT_LINK) 

list_test: linked_list.o linked_list_tests.o
	$(C_COMPILER) $(C_GCOV) $(C_LINK_OPTIONS) $^ -o $@ $(CUNIT_LINK) 

tests: hash_test.out list_test.out
	./hash_test.out 
	./list_test.out

prof: freq_count_prof.out
	./freq_count_prof.out small.txt
	gprof freq_count_prof.out gmon.out > small.profiling

	./freq_count_prof.out 1k-long-words.txt
	gprof freq_count_prof.out gmon.out > 1k-long-words.profiling

	./freq_count_prof.out 10k-words.txt
	gprof freq_count_prof.out gmon.out > 10k-words.profiling

	./freq_count_prof.out 16k-words.txt
	gprof freq_count_prof.out gmon.out > 16k-words.profiling

clean:
	rm -f *.o *.out *.profiling freq_count hash_test list_test freq_count_prof 

mem_tests: hash_test.out list_test.out
	valgrind --leak-check=full ./hash_test.out
	valgrind --leak-check=full ./list_test.out

mem_freq_count: freq_count.out
	valgrind --leak-check=full ./freq_count.out $(ARGS) 

.PHONY: freq_count test hash_mem list_mem freq_count_mem clean freq_count_prof
