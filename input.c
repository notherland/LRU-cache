#include "LRU_cache.h"

void input (struct hash* table, struct queue* list, int* cache_hits)
{
    int page;
    int n = 0, i = 0;

    printf ("Enter the amount of requests :");
    assert (scanf ("%d", &n));
    printf ("Enter your requests:");

    for (i = 0; i < n; i += 1)
    {
        scanf ("%d", &page);
        //printf ("%d) page = %d\n", i, page);
        add_new_page(table, list, page, cache_hits);
    }
}
