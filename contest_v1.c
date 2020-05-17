//------------------------------------------------------------------------------
//Контестная версия: оптимизация по времени путем сокращения аллокаций памяти
//------------------------------------------------------------------------------
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int k = 0, l = 0;
const int TABLESIZE = 1009;
struct node {
    int data;
    struct node *next;
    struct node *prev;
};
struct hash_node {
    int index;
    struct node *n_cache;
    struct hash_node *next;
};
struct hash {
    int capacity;
    struct hash_node *hash_nodes; //массив структур для хранения элементов хэш-таблицы
    struct hash_node **elem;
};
struct queue {
    int capacity;
    int length;
    struct node *head;
    struct node *tail;
    struct node *queue_nodes; //массив структур для хранения элементов кэша
};
int hash_func(int index) {
    return index % TABLESIZE;
}
struct queue *queue_ctor(int capacity) //создание очереди
{
    struct node *nodes = NULL;
    struct queue *res = (struct queue *)calloc(1, sizeof(*res));
    // assert(res);
    res->head = NULL;
    res->tail = NULL;
    res->capacity = capacity;
    res->length = 0;
    nodes = (struct node *)calloc(capacity, sizeof(struct node));
    res->queue_nodes = nodes;
    return res;
}

struct node *node_ctor(struct node *pointer, int idx) { //создание элемента кэша
    struct node *res = pointer + k;
    k++;
    res->next = NULL;
    res->prev = NULL;
    res->data = idx;
    return res;
}
void node_dtor(struct node *elem) //удаление элемента кэша
{
    assert(elem);
    free(elem);
    elem = NULL;
}
void queue_dtor(struct queue *list) //удаление очереди
{
    int i = 0;
    list->tail = NULL;
    list->head = NULL;
    list->length = 0;
    list->capacity = -666;
    free(list->queue_nodes);
    free(list);
}
void print_list(struct queue *s) //распечатка очереди
{
    struct node *cur_el = s->head;
    while (cur_el != NULL) {
        printf("%d ", cur_el->data);
        cur_el = cur_el->next;
    }
}
struct node *add_node(struct queue *list,
                      int index) //добавление элемента кэша в начало
{
    struct node *elem = node_ctor(list->queue_nodes, index);
    if (list->length == 0) {
        elem->next = NULL;
        elem->prev = NULL;
        list->tail = elem;
        list->head = elem;
    }
    else {
        list->head->prev = elem;
        elem->next = list->head;
        list->head = elem;
        elem->prev = NULL;
    }
    (list->length)++;
    return elem;
    // print_list(list);
}
struct node *replace_node (struct queue *list, int cur_idx) {
    struct node *res = NULL;
    struct node *tmp = NULL;
    tmp = list->head;
    res = list->tail;
    list->tail = list->tail->prev;
    list->tail->next = NULL;
    res->prev = NULL;
    res->data = cur_idx;
    res->next = tmp;
    tmp->prev = res;
    list->head = res;
    return res;
}
struct node *add_new_elem(struct queue *list, int cur_idx) { //добавление элемента кэша
    if (list->capacity > list->length)  //добавление без удаления последнего
        return add_node(list, cur_idx);
    else
        return replace_node(list, cur_idx);
}
void move_elem(struct queue *list,
               struct node *cur_elem) { //перемещение элемента в начало
    if (cur_elem->prev != NULL) {
        cur_elem->prev->next = cur_elem->next;
        if (cur_elem->next != NULL)
            cur_elem->next->prev = cur_elem->prev;
        else
            list->tail = cur_elem->prev;
        cur_elem->prev = NULL;
        list->head->prev = cur_elem;
        cur_elem->next = list->head;
        list->head = cur_elem;
    }
}
void delete_queue(struct queue *list) //удаление очереди целиком
{
    struct node *p;
    struct node *cur_el = list->head;
    for (int i = 0; i < (list->length); i++) {
        p = cur_el;
        cur_el = cur_el->next;
        node_dtor(p);
    }
    queue_dtor(list);
}
struct hash *create_table(int capacity) { //создание xэша
    struct hash *table = (struct hash *)calloc(1, sizeof(struct hash));
    table->capacity = TABLESIZE;
    table->elem = (struct hash_node **)calloc(table->capacity, sizeof(struct hash_node *));
    table->hash_nodes = (struct hash_node *)calloc(capacity, sizeof(struct hash_node));
    return table;
}
struct hash_node *check_index(int key, int index, struct hash *table) {
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
void remove_hash_node(struct hash_node *p) { //удаление элемента таблицы
    p->next = NULL;
    p->index = -666;
    free(p);
}
struct hash_node *erase_hash_node(struct hash_node *p) {
    p->next = NULL;
    p->index = -666;
    return p;
}

struct hash_node *delete_from_hash(int last_idx,
                                   struct hash *table) { //удаление по индексу из таблицы
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
void add_new_page(struct hash *table, struct queue *list, int page, int *cache_hits) {  //добавление в хэш
    struct hash_node *newpage = NULL;
    struct hash_node *check = NULL;
    struct hash_node *p = NULL;
    int key = 0, last_idx = 0;
    key = hash_func(page);
    check = check_index(key, page, table);
    if (check == NULL) {
        if ((list->length) == (list->capacity)) {
            last_idx = list->tail->data;
            newpage = delete_from_hash(last_idx, table); //стираем последний элемент для записи нового
        }
        else {
            p = table->hash_nodes;
            newpage = p + l;
            l++;
        }
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
void delete_table(struct hash *table) { //удаление хэш-таблицы
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
    free(table->hash_nodes);
    free(table);
    table = NULL;
    return;
}

void print_hash(struct hash *table) //печать таблицы
{
    int i = 0;
    struct hash_node *list = NULL;//исправление
    printf ("hash-table..\n");
    for (i = 0; i < (table->capacity); i++) {
        printf ("elem %p : ", table->elem[i]);
        list = table->elem[i];
        while (list != NULL) {
            list = list->next;
        }
    }
}

int main() {
    int capacity = 0, n = 0, page = 0, cache_hits = 0, i = 0;
    struct queue *my_cache;
    struct hash *my_hash;
    scanf("%d %d ", &capacity, &n);
    my_hash = create_table(capacity);
    my_cache = queue_ctor(capacity);
    for (; i < n; i++) {
        scanf("%d ", &page);
        add_new_page(my_hash, my_cache, page, &cache_hits);
    }
    printf("%d ", cache_hits);
    delete_queue(my_cache);
    delete_table(my_hash);
    return 0;
}
