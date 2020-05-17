#include "LRU_cache.h"

void run_tests (){
	run_test("test1.txt");
	run_test("test2.txt");
	run_test("test3.txt");
	run_test("test4.txt");
	run_test("test5.txt");
	run_test("test6.txt");
	run_test("test7.txt");
	run_test("test8.txt");
	run_test("test9.txt");
	run_test("test10.txt");
	run_test("test11.txt");
	run_test("test12.txt");
	run_test("test13.txt");
	run_test("test14.txt");
	run_test("test15.txt");
	return;
}

void run_test(const char *filename){
  
  FILE *f = fopen("./tests/filename", "r");
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
  
  fscanf(" %d", &answer);
  if(answer == cache_hits) printf("\ntest: result %d, correct %d \n OK\n", cache_hits, answer);
  else printf("\n test: result %d, correct %d \nwrong answer\n");
  
  delete_queue(my_cache);
  delete_table(my_hash);
  return;	
} 