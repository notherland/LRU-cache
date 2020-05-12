
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

struct hash_node* check_index (int index, struct hash* table)
{
    int key = hash_func(index);
    struct hash_node* node = table[key].elem;
    while (node != NULL)
    {
        if (index == node->index)
            return node;
        node = node->next;
    }
    return NULL;
}

struct hash *create_table(){
    struct hash *table = (struct hash *)calloc(1,sizeof(struct hash));
    table->capacity = TABLESIZE;
    table->elem = (struct hash_node *)calloc(table->capacity, sizeof(struct hash_node));
    for(int i = 0; i < table->capacity; i++){
        table[i].elem = NULL;
    }
    return table;
}

struct node *add_new_page (struct page *page, struct hash *table, struct queue *list) {
    struct hash_node *current = NULL, *check = NULL;
    int last_idx = 0, i = 0, index;
    struct node *newnode;
    index = page->index;
    check = check_index(index, table);
    i = hash_func(index);
    if (check == NULL) { //такого элемента нет - создаем новый
        newnode = add_new_elem(list, page, &last_idx);
        current = table[i].elem;
        while (current != NULL) current = current->next;
        current -> index = index;
        current -> n_cache = newnode;
        current -> next = NULL;
        if(last_idx != 0) {
            //cюда функцию удаления ненужного адреса из хэша, передаем (last_idx, table);
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

void print_hash (struct hash* table)
{
    int i = 0;
    struct hash_node* list = NULL;
    printf ("hash-table:\n");
    for (i = 0; i < table->capacity; i+=1)
    {
        printf ("elem %d : ", i);
        list = table->elem;
        while (list != NULL)
        {
            printf ("%d, ", list->index);
            list = list->next;
        }
        printf ("\n");
    }
    return;
}
