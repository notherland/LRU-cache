#include "LRU_cache.h"

const int TABLESIZE = 1000;

int hash_func(int index)
{
    return index % TABLESIZE;
}

struct hash *create_table() {
    struct hash *table = (struct hash *)calloc(1, sizeof(struct hash));
    assert (table);
    table->capacity = TABLESIZE;
    table->elem = (struct hash_node **)calloc(table->capacity, sizeof(struct hash_node *));
    assert (table->elem);

    return table;
}

struct hash_node *check_index(int key, int index, struct hash *table) {
    assert (table);

    struct hash_node *res;
    res = table->elem[key];
    while (res != NULL) {
        if (index == (res->index))
            return res;
        res = res->next;
    }

    return NULL;
}

void remove_hash_node(struct hash_node *p) { //удаление элемента таблицы
    assert (p);

    p->next = NULL;
    p->index = -666;
    free(p);
}

void delete_from_hash(int last_idx, struct hash *table) {
    assert (table);

    int idx = hash_func(last_idx);
    struct hash_node *p;
    struct hash_node *cur = table->elem[idx];
    if ((cur->index) == last_idx) {
        table->elem[idx] = cur->next;
        remove_hash_node(cur);
    } else {
        while ((cur->next->index) != last_idx)
            cur = cur->next;
        p = cur->next;
        cur->next = cur->next->next;
        remove_hash_node(p);
    }
}

void add_new_page(struct hash *table, struct queue *list, int page, int *cache_hits) { //добавление в хэш
    assert (table);
    assert (list);
    assert (cache_hits);

    struct hash_node *newpage = NULL;
    struct hash_node *check = NULL;
    struct hash_node *p;
    int last_idx = -1, key = 0;

    key = hash_func(page);
    check = check_index(key, page, table);

    if (check == NULL) { //такого элемента нет - создаем новый
        newpage = (struct hash_node *)calloc(1, sizeof(struct hash_node));
        p = table->elem[key];
        newpage->next = p;
        newpage->index = page;
        table->elem[key] = newpage;
        newpage->n_cache = add_new_elem(list, page, &last_idx);
        if (last_idx >= 0)
            delete_from_hash(last_idx, table);
    } else { //такой элемент есть, перемещаем его в кэше, хэш-таблицу не трогаем
        move_elem(list, check->n_cache);
        (*cache_hits)++;
    }
}

void print_hash(struct hash *table){
    assert (table);

    int i = 0;
    struct hash_node *list;
    printf ("hash-table......\n");
    for (i = 0; i < table->capacity; i += 1) {
        printf ("elem %d : ", i);
        list = table->elem[i];
        while (list != NULL) {
            printf ("index = %d, ", list->index);
            list = list->next;
        }
        printf ("\n");
    }
}

void delete_table(struct hash *table) {
    assert (table);

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
}
