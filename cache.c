//----------------------------------------------------------------------------------------------------------------------
//!Создание двусвязного списка для хранения страниц и работа с ним
//----------------------------------------------------------------------------------------------------------------------
#include "LRU_cache.h"

struct queue *queue_ctor(int capacity) { //создание списка
    struct queue *res = (struct queue *)calloc(1, sizeof(*res));
    assert(res);

    res->head = NULL;
    res->tail = NULL;
    res->capacity = capacity;
    res->length = 0;

    return res;
}

struct node *node_ctor(int idx) { //создание элемента для хранения страницы
    struct node *res = (struct node *)calloc(1, sizeof(*res));
    assert(res);

    res->next = NULL;
    res->prev = NULL;
    res->data = idx;

    return res;
}

void queue_dtor(struct queue *list) { //удаление списка
    assert (list);

    list->tail = NULL;
    list->head = NULL;
    list->capacity = -666;
    list->length = 0;
}

void node_dtor(struct node *elem) { //удаление элемента списка
    assert(elem);
    free(elem);
    elem = NULL;
}

struct node *add_node(struct queue *list, int index) { //создание элемента и помещение его в начало
    assert (list);

    struct node *elem = node_ctor(index);
    if (list->length == 0) {
        elem->next = NULL;
        elem->prev = NULL;
        list->tail = elem;
        list->head = elem;
    } else {
        list->head->prev = elem;
        elem->next = list->head;
        list->head = elem;
        elem->prev = NULL;
    }
    (list->length)++;

    return elem;
}

struct node *replace_node(struct queue *list, int cur_idx) { //добавление страницы с удалением последней в списке
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

struct node *add_new_elem(struct queue *list, int cur_idx, int *last_idx) { //добавление ранее не встречавшейся страницы
    assert (list);
    assert (last_idx);

    struct node *res = NULL;
    struct node *tmp = NULL;

    if (list->capacity > list->length) //добавление без удаления последнего элемента
        return add_node(list, cur_idx);
    else
        return replace_node(list, cur_idx); //добавление с удалением последнего
}

void move_elem(struct queue *list, struct node *cur_elem) { //перемещение элемента в начало списка
    assert (list);
    assert(cur_elem);

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

void delete_queue(struct queue *list) { //удаление списка
    assert (list);

    struct node *p;
    struct node *cur_el = list->head;
    for (int i = 0; i < (list->length); i++) {
        p = cur_el;
        cur_el = cur_el->next;
        node_dtor(p);
    }
    queue_dtor(list);

    return;
}

void print_list(struct queue *s) { //вывод списка и его элементов
    assert (s);

    struct node *cur_el = s->head;

    printf("list..\n");
    printf("head %8p tail %8p capacity %d length %d\n", s->head, s->tail, s->capacity, s->length);
    while (cur_el != NULL) {
        printf("%d ", cur_el->data);
        cur_el = cur_el->next;
    }
}
