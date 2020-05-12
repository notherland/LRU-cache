#include "header.h"

void input (struct hash* table, struct queue* queue)
{
    int n = 0, i = 0, index = 0;
    printf ("Please enter the amount of requests : ");
    assert (scanf ("%d", &n));
    for (i = 0; i < n; i += 1)
    {
        scanf ("%d", &index);
        input_page (index);
        add_new_elem()
    }
    return;
}

struct page* input_page (int index)
{
    struct page* page = {index, NULL, 0};
    return page;
}
