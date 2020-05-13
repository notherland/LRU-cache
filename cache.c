#include "header.h"

struct node {
    char* data;
    int index;
    struct node* next;
    struct node* prev;
};

struct queue* queue_ctor() //создание очереди
{
    //printf ("beg queue\n");
    struct queue* res = (struct queue*) calloc(1, sizeof(struct queue));
    //printf ("res = %p", res);
    assert(res);
    res->head = NULL;
    res->tail = NULL;
    res->capacity = 10;
    res->length = 0;
    //printf ("end queue\n");
    return res;
}

struct node* node_ctor(struct page* page) //создание элемента
{
    struct node* res = (struct node*) calloc(1, sizeof(*res));
    res->next = NULL;
    res->prev = NULL;
    res->index = page->index;
    char* text = (char*) calloc(page->n, sizeof(char));
    assert(text != NULL);
    for (int i = 0; i < page->n; i++)
        text[i] = page->data[i];
    res->data = text;
    return res;
}

void queue_dtor(struct queue* list) //удаление очереди
{
    list->tail = NULL;
    list->head = NULL;
    list->capacity = -666;
    list->length = 0;

}

int node_dtor(struct node* elem) //удаление элемента
{
    assert(elem);
    int idx = elem->index;
    elem->index = -1;
    free(elem->data);
    free(elem);
    elem = NULL;
    return idx;
}

struct node* add_node(struct queue* list, struct page* page) //добавление элемента в начало
{
    struct node* elem = node_ctor(page);
    if (list->length == 0)
    {
        elem->next = NULL;
        elem->prev = NULL;
        list->tail = elem;
        list->head = elem;
    }
    else
    {
        list->head->prev = elem;
        elem->next = list->head;
        list->head = elem;
        elem->prev = NULL;
    }
    (list->length)++;
    return elem;
}

struct node* add_new_elem(struct queue* list, struct page* page, int* last_idx) //добавление нового элемента
{
    assert(list->capacity >= list->length);
    if (list->capacity > list->length) { //добавление без удаления последнего
        return add_node(list, page);
    }
    struct node* res = add_node(list, page); //добавление с удалением последнего
    list->capacity--;
    struct node* last = list->tail;
    list->tail = last->prev;
    list->tail->next = NULL;
    *last_idx = node_dtor(last);//хэш для поиска и удаления последнего элемента в хэш-таблице
    return res;
}

struct node* move_elem(struct queue* list, struct node* cur_elem) { //перемещение элемента в начало
    if (cur_elem->prev != NULL)
        cur_elem->prev->next = cur_elem->next;
    if (cur_elem->next != NULL)
        cur_elem->next->prev = cur_elem->prev;
    cur_elem->prev = NULL;
    cur_elem->next = list->head;
    list->head = cur_elem;
    return cur_elem;
}


void print_list(struct queue* s) //распечатка очереди
{
    printf("list.....\n");
    printf("head %8p tail %8p count %d\n",s->head,s->tail,s->capacity);
    struct node* cur_el = s->head;
    for (int i = 0; i < (s->capacity); i++)
    {
        printf("cur_el %8p   :    val %d  :  next %8p  :  prev %8p\n",cur_el, cur_el->index, cur_el->next, cur_el->prev);
        cur_el = cur_el->next;
    }
}

void delete_queue(struct queue* list) //удаление очереди целиком
{
    int idx = 0;
    struct node* cur_el = list->head;
    for (int i = 0; i < list->capacity - 1; i++)
    {
        cur_el = cur_el->next;
        idx = node_dtor(cur_el);
    }
    queue_dtor(list);
}
