#include "LRU_cache.h"

void run_tests (){
	run_test("./tests/test1.txt");
	run_test("./tests/test2.txt");
	run_test("./tests/test3.txt");
	run_test("./tests/test4.txt");
	run_test("./tests/test5.txt");
	run_test("./tests/test6.txt");
	run_test("./tests/test7.txt");
	run_test("./tests/test8.txt");
	run_test("./tests/test9.txt");
	run_test("./tests/test10.txt");
	run_test("./tests/test11.txt");
	run_test("./tests/test12.txt");
	run_test("./tests/test13.txt");
	run_test("./tests/test14.txt");
	run_test("./tests/test15.txt");
	return;
}

void run_test(const char *filename){
  
  FILE *f = fopen(filename, "r");
  int capacity = 0, n = 0, page = 0, cache_hits = 0, i = 0, answer;
  struct queue *my_cache;
  struct hash *my_hash;
  assert(f != NULL);

  fscanf(f, "%d %d ", &capacity, &n);
  my_hash = create_table();
  my_cache = queue_ctor(capacity);
  
  for (; i < n; i++) {
    fscanf(f, "%d", &page);
    add_new_page(my_hash, my_cache, page, &cache_hits);
  }
  
  fscanf(f, "%d", &answer);
  if(answer == cache_hits) printf("\ntest: result %d, correct %d \n OK\n", cache_hits, answer);
  else printf("\ntest: result %d, correct %d \nwrong answer\n", cache_hits, answer);
  
  delete_queue(my_cache);
  delete_table(my_hash);
  return;	
} 