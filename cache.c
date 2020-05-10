
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include <math.h>
struct page {
    int index;
    char* data;
    int n; //кол-во символов
};
struct node {
    char* data;
    int hash;
    struct node* next;
    struct node* prev;
};

struct queue
{
    int capacity;
    int length;
    struct node* head;
    struct node* tail;
};

struct queue* queue_ctor() //создание очереди
{
    struct queue* res = (struct queue*) calloc(1, sizeof(*res));
    assert(res);
    res->head = NULL;
    res->tail = NULL;
    res->capacity = 0;
    res->length = 0;
    return res;
}

struct node* node_ctor(int n, int hash, char* text) //создание элемента
{
    struct node* res = (struct node*) calloc(1, sizeof(*res));
    res->next = NULL;
    res->prev = NULL;
    res->hash = hash;
    char* data = (char*) calloc(n, sizeof(char));
    assert(data != NULL);
    for (int i = 0; i < n; i++)
        data[i] = text[i];
    res->data = data;
    return res;
}

void queue_dtor(struct queue* list) //удаление очереди
{
    list->tail = NULL;
    list->head = NULL;
    list->capacity = -666;
    list->length = 0;
    return;
}

int node_dtor(struct node* elem) //удаление элемента
{
    assert(elem);
    int idx = elem->hash;
    elem->hash = -1;
    free(elem->data);
    free(elem);
    elem = NULL;
    return idx;
}

struct node* add_node(struct queue* list, int hash, struct page* page) //добавление элемента в начало
{
    struct node* elem = node_ctor(page->n, hash, page->data);
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

struct node* add_new_elem(struct queue* list, struct page* page, int hash, int* hash_last) //добавление нового элемента
{
    assert(list->capacity >= list->length);
    if (list->capacity > list->length) { //добавление без удаления последнего
        return add_node(list, hash, page);
    }
    struct node* res = add_node(list, hash, page); //добавление с удалением последнего
    list->capacity--;
    struct node* last = list->tail;
    list->tail = last->prev;
    list->tail->next = NULL;
    *hash_last = node_dtor(last);//хэш для поиска и удаления последнего элемента в хэш-таблице
    return res;
}

struct node* move_elem(struct queue* list, struct node* cur_elem, struct page* page) { //перемещение элемента в начало
    cur_elem->prev->next = cur_elem->next;
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
    for (int i =0; i < s->capacity; i++)
    {
        printf("cur_el %8p   :    val %d  :  next %8p  :  prev %8p\n",cur_el, cur_el->hash, cur_el->next, cur_el->prev);
        cur_el = cur_el->next;
    }
}

void delete_queue(struct queue* list) //удаление очереди целиком
{
    int hash = 0;
    struct node* cur_el = list->head;
    for (int i = 0; i < list->capacity - 1; i++)
    {
        cur_el = cur_el->next;
        hash = node_dtor(cur_el);
    }
    queue_dtor(list->head);
}
