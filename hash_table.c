
#include "header.h"

const int TABLESIZE = 10;

struct hash_node{
    int index;
    struct node* n_cache;
    struct hash_node* next;
};

int hash_func (int index)
{
    return index % TABLESIZE;
}


struct hash *create_table(){
    int i = 0;
    struct hash *table = (struct hash *)calloc(1,sizeof(struct hash));
    table->capacity = TABLESIZE;
    table->elem = (struct hash_node**)calloc (1, sizeof (struct hash_node));
    for (i = 0; i < table->capacity; i++)
    {
        table->elem[i] = (struct hash_node*) calloc (1, sizeof (struct hash_node));
    }
    return table;
}

struct hash_node* check_index (int index, struct hash* table)
{
    printf ("CHECK INDEX : %d\n", index);
    int key = hash_func(index);
    struct hash_node* node = (struct hash_node*)calloc (1, sizeof(struct hash_node));
    node = table->elem[key];
    while (node != NULL)
    {
        if (index == node->index)
            return node;
        node = node->next;
    }
    return NULL;
}

struct node *add_new_page (struct page *page, struct hash *table, struct queue *list) {
    struct hash_node *current = (struct hash_node *) calloc (1, sizeof(struct hash_node));
    struct hash_node *check = (struct hash_node *) calloc (1, sizeof(struct hash_node));
    int last_idx = 0, key = 0, index;
    struct node *newnode;
    index = page->index;
    check = check_index(index, table);
    key = hash_func(index);
    if (check == NULL) { //такого элемента нет - создаем новый
        newnode = add_new_elem(list, page, &last_idx);
        current = table->elem[key];
        printf ("%d", table->elem[key]);
        while (current->next != NULL) current = current->next;
        current -> index = index;
        current -> n_cache = newnode;
        current -> next = NULL;
        if(last_idx != 0) {
            printf ("hui");
            //delete_hash_node (last_idx, table);
        }
        return newnode;
    }
    else { //такой элемент есть, перемещаем его в кэше, хэш-таблицу не трогаем
        newnode = move_elem(list, check->n_cache);
        return newnode;
    }
}

void delete_table(struct hash* table){
    int i = 0;
    struct hash_node* list = NULL, *prev = NULL;
    for (i = 0; i < table->capacity; i += 1)
    {
        list = table->elem[i];
        while (list != NULL)
        {
            prev = list;
            list = list->next;
            free(prev);
        }
    }
    return;
}

void print_hash (struct hash* table)
{
    int i = 0;
    struct hash_node* list = (struct hash_node*) calloc(1, sizeof(struct hash_node));
    printf ("hash-table:\n");
    for (i = 0; i < table->capacity; i+=1)
    {
        printf ("elem %d : ", i);
        list = table->elem[i];
        while (list != NULL)
        {
            printf ("%d, ", list->index);
            list = list->next;
        }
        printf ("\n");
    }
    return;
}

