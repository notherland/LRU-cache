
#include "LRU_cache.h"

int main() {
    int cache_hits = 0, capacity = 0;
    struct queue *list;
    struct hash* table = create_table();
    assert (table);
    
    printf ("Enter cache size :");
    assert (scanf ("%d", &capacity));
    list = queue_ctor(capacity);
    assert (list);
    
    input (table, list, &cache_hits);
    printf ("cache_hits: ");
    printf ("%d\n", cache_hits);
    //print_hash(table);
    //print_list(list);
    
    delete_table(table);
    delete_queue(list);
}
