
#include "header.h"

const int TABLESIZE = 10;

struct hash {
    int capacity;
    struct hash_node* elem;
};

struct hash_node{
    int index;
    struct node* n_cache;
    struct hash_node* next;
};

int Hash_func (int index)
{
    return index % TABLESIZE;
}

struct hash_table* Create_table (){

}
struct hash_node* Check_index (int index, struct hash* table)
{
    int key = Hash_func(index);
    struct hash_node* node = table[key].elem;
    while (node != NULL)
    {
        if (index == node->index)
            return node;
        node = node->next;
    }
    return NULL;
}

void Delete_table(struct hash* table){
    int i = 0;
    struct hash_node* list = NULL, *prev = NULL;
    for (i = 0; i < table->capacity; i += 1)
    {
        list = table[i].elem;
        while (list != NULL)
        {
            prev = list;
            list = list->next;
            free(prev);
        }
    }
    return;
}
