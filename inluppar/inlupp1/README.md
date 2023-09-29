 # Initial Profiling Results 
   ## small.txt
   **Most used functions:** \
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;1. find_previous_entry_for_key\
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;1. get_bucket_index\
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;3. ioopm_hash_table_lookup

   **Time average (of 10):**
   - real    0m0.005s
   - user    0m0.003s
   - sys     0m0.002s

   Percent of CPU this job got: 0%

   ## 1k-long-words.txt
   **Most used functions:** \
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;1. find_previous_entry_for_key\
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;1. get_bucket_index\
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;3. ioopm_hash_table_lookup
   
   **Time average:**
   - real    0m0.005s
   - user    0m0.001s
   - sys     0m0.004s
   
   Percent of CPU this job got: 100%

   ## 10k-words.txt
   **Most used functions:** \
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;1. find_previous_entry_for_key\
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;1. get_bucket_index\
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;3. ioopm_hash_table_lookup
   
   **Time average:**
   - real    0m0.015s
   - user    0m0.001s
   - sys     0m0.013s
   
   Percent of CPU this job got: 88%

   ## 16k-words.txt
   **Most used functions:** \
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;1. find_previous_entry_for_key\
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;1. get_bucket_index\
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;3. ioopm_hash_table_lookup
   
   **Time average:**
   - real    0m0.113s
   - user    0m0.085s
   - sys     0m0.019s
   
   Percent of CPU this job got: 95%
      
   ##
   No library functions were among the most used and the most used was consistent across all inputs (a trend).


   It was consistent because for every lookup, has_key and insert we needed to run `find_previous_entry_for_key`. This function is also run in linear time. Meaning in the worst case we may need to run through the entire bucket to find the previous value in a case where all entries are in the same bucket. With a smaller hashtable (in our case with 17 buckets) the entries are not spread out enough to make an efficient hashtable. In the 16k-word file we have 4370 unique words and if all buckets were filled the same we would still have 257 entries in each and in the worst case we need the last element.


   `get_bucket_index` is used as many times as `find_previous_entry_for_key` because it is also used in every insert-, lookup- and has_key-functions. Though time spent in this function is dependent on how long the words are, and so far our long words are still not up to a measurable threshold.


   While 1k-long-words did not use as much time as 10k-words and 16k-words it had worse performance (used most of the CPU to get the job done). It was unexpected but also logical. Longer words will spend more time in our hashing function since it adds the values of each character. Compare-functions will also take longer because there are more characters to compare with each other before we can determine that they are in fact identical or not.


   It was expected for the larger files to have worse performance and take more time. But 10k-words was surprisingly not as bad as we initially thought. It was closer to 1k-long-words in time than to 16k-words and took almost as much percent of the CPU as the 16k-words-file. Though the difference in unique words between 16k-words and 10k-words is 4171 and as explained with the 16k-words above, is a major player in the performance aspect.


   Based on the results we would need to find a better solution to find the previous key for an entry. Best case would be to find a constant time solution for it or implement another method for inserting, removing etc.
   A short-term solution would be to increase our buckets so these linear functions have better conditions for their search through the buckets. With more buckets we can spread the elements across and have fewer elements in each. This will take a larger amount of memory but time-wise the performance would improve.


The 16k-words was the only input which spent mesurable amount of time in each functions.\
**17 Buckets:**                               
| % time |  cumulative seconds   |self seconds   | calls |  self ns/call | total ns/call | name  |  
|------|------------|----------|-------|----------|---------|--------------------------------|
|100.00|      0.02  |   0.02   | 55346 |   361.36 |  361.36 | find_previous_entry_for_key    |
|  0.00|      0.02  |   0.00   | 55346 |     0.00 |    0.00 | get_bucket_index               |
|  0.00|      0.02  |   0.00   | 38354 |     0.00 |  361.36 | ioopm_hash_table_lookup        |
|  0.00|      0.02  |   0.00   | 16992 |     0.00 |  361.36 | ioopm_hash_table_has_key       |
|  0.00|      0.02  |   0.00   | 16992 |     0.00 |  361.36 | ioopm_hash_table_insert        |
|  0.00|      0.02  |   0.00   |  4370 |     0.00 |    0.00 | entry_create                   |
|  0.00|      0.02  |   0.00   |  4370 |     0.00 |    0.00 | ioopm_iterator_has_next        |
|  0.00|      0.02  |   0.00   |  4370 |     0.00 |    0.00 | ioopm_iterator_next            |
|  0.00|      0.02  |   0.00   |  4370 |     0.00 |    0.00 | ioopm_linked_list_append       |
|  0.00|      0.02  |   0.00   |  4370 |     0.00 |    0.00 | link_create                    |
|  0.00|      0.02  |   0.00   |    17 |     0.00 |    0.00 | entry_destroy                  |
|  0.00|      0.02  |   0.00   |     1 |     0.00 |    0.00 | ioopm_hash_table_apply_to_all  |   
|  0.00|      0.02  |   0.00   |     1 |     0.00 |    0.00 | ioopm_hash_table_clear         |   
|  0.00|      0.02  |   0.00   |     1 |     0.00 |    0.00 | ioopm_hash_table_create        |   
|  0.00|      0.02  |   0.00   |     1 |     0.00 |    0.00 | ioopm_hash_table_destroy       |
|  0.00|      0.02  |   0.00   |     1 |     0.00 |    0.00 | ioopm_hash_table_keys          |   
|  0.00|      0.02  |   0.00   |     1 |     0.00 |    0.00 | ioopm_hash_table_size          |
|  0.00|      0.02  |   0.00   |     1 |     0.00 |    0.00 | ioopm_iterator_current         |   
|  0.00|      0.02  |   0.00   |     1 |     0.00 |    0.00 | ioopm_iterator_destroy         |   
|  0.00|      0.02  |   0.00   |     1 |     0.00 |    0.00 | ioopm_linked_list_clear        |   
|  0.00|      0.02  |   0.00   |     1 |     0.00 |    0.00 | ioopm_linked_list_create       |   
|  0.00|      0.02  |   0.00   |     1 |     0.00 |    0.00 | ioopm_linked_list_destroy      |      
|  0.00|      0.02  |   0.00   |     1 |     0.00 |    0.00 | ioopm_linked_list_is_empty     |            
|  0.00|      0.02  |   0.00   |     1 |     0.00 |    0.00 | ioopm_linked_list_size         |            
|  0.00|      0.02  |   0.00   |     1 |     0.00 |    0.00 | ioopm_list_iterator            |   


**100 Buckets:**  
| % time |  cumulative seconds   |self seconds   | calls |  self ns/call | total ns/call | name  |  
|------|------------|----------|-------|----------|---------|--------------------------------|
|  0.00|      0.00  |   0.00   | 55346   |     0.00 |  0.00 | get_bucket_index
|  0.00|      0.00  |   0.00   | 38354   |     0.00 |  0.00 | ioopm_hash_table_lookup
|  0.00|      0.00  |   0.00   | 16992   |     0.00 |  0.00 | ioopm_hash_table_has_key
|  0.00|      0.00  |   0.00   | 16992   |     0.00 |  0.00 | ioopm_hash_table_insert
|  0.00|      0.00  |   0.00   |  4370   |     0.00 |  0.00 | entry_create
|  0.00|      0.00  |   0.00   |  4370   |     0.00 |    0.00| ioopm_iterator_has_next                   |
|  0.00|      0.00  |   0.00   |  4370   |     0.00 |    0.00| ioopm_iterator_next        |
|  0.00|      0.00  |   0.00   |  4370   |     0.00 |    0.00| ioopm_linked_list_append            |
|  0.00|      0.00  |   0.00   |  4370   |     0.00 |    0.00| link_create       |
|  0.00|      0.00  |   0.00   |   100   |     0.00 |    0.00| entry_destroy                    |
|  0.00|      0.00  |   0.00   |     1   |     0.00 |    0.00| ioopm_hash_table_apply_to_all                  |
|  0.00|      0.00  |   0.00   |     1   |     0.00 |    0.00| ioopm_hash_table_clear  |   
|  0.00|      0.00  |   0.00   | 55346   |     0.00 |    0.00| find_previous_entry_for_key         |   
|  0.00|      0.00  |   0.00   |     1   |     0.00 |    0.00| ioopm_hash_table_create        |   
|  0.00|      0.00  |   0.00   |     1   |     0.00 |    0.00| ioopm_hash_table_destroy       |
|  0.00|      0.00  |   0.00   |     1   |     0.00 |    0.00| ioopm_hash_table_keys          |   
|  0.00|      0.00  |   0.00   |     1   |     0.00 |    0.00| ioopm_hash_table_size          |
|  0.00|      0.00  |   0.00   |     1   |     0.00 |    0.00| ioopm_iterator_current         |   
|  0.00|      0.00  |   0.00   |     1   |     0.00 |    0.00| ioopm_iterator_destroy         |   
|  0.00|      0.00  |   0.00   |     1   |     0.00 |    0.00| ioopm_linked_list_clear        |   
|  0.00|      0.00  |   0.00   |     1   |     0.00 |    0.00| ioopm_linked_list_create       |   
|  0.00|      0.00  |   0.00   |     1   |     0.00 |    0.00| ioopm_linked_list_destroy      |      
|  0.00|      0.00  |   0.00   |     1   |     0.00 |    0.00| ioopm_linked_list_is_empty     |            
|  0.00|      0.00  |   0.00   |     1   |     0.00 |    0.00| ioopm_linked_list_size         |            
|  0.00|      0.00  |   0.00   |     1   |     0.00 |    0.00| ioopm_list_iterator            |   


- real    0m0.034s
- user    0m0.008s
- sys     0m0.022s

As seen with 100 buckes the time improved significantly. Because we don't have as many elements in each buckets to search through before we find what we want. 


   ## How results were obtained: 
      
   #### Top functions used: 
   ```
   $ make clean
   $ make freq_count
   $ ./driver filename.txt
   $ gprof driver gmon.out > output
   ```

   #### Time:  
   ```
   $ make clean
   $ make driver
   $ command time --verbose ./driver filename.txt
   ```

   #### Extended time: 
   ```
   $ make clean
   $ make driver
   $ command time --verbose ./driver filename.txt
   ```