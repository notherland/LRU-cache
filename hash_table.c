#include "LRU_cache.h"

const int TABLESIZE = 1009;

int hash_func(int index)
{
    return index % TABLESIZE;
}

struct hash *create_table() {
    struct hash *table = (struct hash *)calloc(1, sizeof(struct hash));
    table->capacity = TABLESIZE;
    table->elem = (struct hash_node **)calloc(
            table->capacity, sizeof(struct hash_node *));
    return table;
}

struct hash_node *check_index(int key, int index, struct hash *table) {
    assert(table);

    struct hash_node *res;
    res = table->elem[key];
    while (res != NULL) {
        if (index == (res->index)) {
            return res;
        }
        res = res->next;
    }
    return NULL;
}

void remove_hash_node(struct hash_node *p) {
    assert (p);

    p->next = NULL;
    p->index = -666;
    free(p);
}

struct hash_node *erase_hash_node(struct hash_node *p) {
    assert(p);

    p->next = NULL;
    p->index = -666;
    return p;
}

struct hash_node *delete_from_hash(int last_idx, struct hash *table) {
    assert (table);

    int idx = hash_func(last_idx);
    struct hash_node *p;
    struct hash_node *cur = table->elem[idx];

    if ((cur->index) == last_idx) {
        table->elem[idx] = cur->next;
        return erase_hash_node(cur);
    }
    while ((cur->next->index) != last_idx)
        cur = cur->next;
    p = cur->next;
    cur->next = cur->next->next;

    return erase_hash_node(p);
}

void add_new_page(struct hash *table, struct queue *list, int page, int *cache_hits) { //добавление в хэш
    assert(table);
    assert(list);
    assert (cache_hits);

    struct hash_node *newpage = NULL;
    struct hash_node *check = NULL;
    struct hash_node *p;
    int key = 0, last_idx = 0;
    key = hash_func(page);
    check = check_index(key, page, table);
    if (check == NULL) {
        if ((list->length) == (list->capacity)) {
            last_idx = list->tail->data;
            newpage = delete_from_hash(last_idx, table); //стираем последний элемент для записи нового
        }
        else
            newpage = (struct hash_node *)calloc(1, sizeof(*newpage));
        p = table->elem[key];
        newpage->next = p;
        newpage->index = page;
        table->elem[key] = newpage;
        newpage->n_cache = add_new_elem(list, page);
    }
    else {
        move_elem(list, check->n_cache);
        (*cache_hits)++;
    }
}

void print_hash(struct hash *table){
    assert(table);

    int i = 0;
    struct hash_node *list = NULL;
    printf ("hash-table....\n");
    for (i = 0; i < (table->capacity); i++) {
        printf ("elem %p : ", table->elem[i]);
        list = table->elem[i];
        while (list != NULL) {
            printf ("%d ", list->index);
            list = list->next;
        }
        printf ("\n");
    }
}

void delete_table(struct hash *table) { //удаление хэш-таблицы
    assert(table);

    int i = 0;
    struct hash_node *list = NULL, *prev = NULL;
    for (i = 0; i < (table->capacity); i++) {
        list = table->elem[i];
        while (list != NULL) {
            prev = list;
            list = list->next;
            remove_hash_node(prev);
        }
    }
    free(table->elem);
    free(table);
    table = NULL;
}