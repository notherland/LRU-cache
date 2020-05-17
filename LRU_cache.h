//
// Created by Kostenok Elizaveta, Tsepkova Alexandra, Shirokova Ksenia on 17.05.2020.
//

#ifndef LRU_CACHE_H
#define LRU_CACHE_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

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
    struct hash_node **elem;
};
struct queue {
    int capacity;
    int length;
    struct node *head;
    struct node *tail;
};
//input

void input (FILE *f, struct hash* table, struct queue* list, int* cache_hits); //ввод запросов

//hash table

int hash_func(int index); //хэш-функция

struct hash* create_table(); //создание хэш-таблицы

struct hash_node *check_index(int key, int index, struct hash *table); //поиск страницы в хэш-таблице по индексу возвращает указатель на элемент, если он найден, и NULL, если нет

void remove_hash_node(struct hash_node *p); //удаление элемента таблицы

struct hash_node *erase_hash_node(struct hash_node *p); //очистка памяти элемента хэша

struct hash_node *delete_from_hash(int last_idx, struct hash *table); //удаление по индексу из таблицы

void add_new_page(struct hash* table, struct queue* list, int page, int* cache_hits); //добавление нового элемента в кэш

void print_hash (struct hash* table); //печать хэш-таблицы

void delete_table(struct hash* table); //удаление хэш-таблицы

//cache

struct queue* queue_ctor(); //создание очереди

void queue_dtor(struct queue *list); //удаление очереди

struct node *node_ctor(int idx); //создание элемента кэша

void node_dtor(struct node *elem); //удаление элемента кэша

struct node *add_node(struct queue *list, int index); //добавление элемента кэша в начало

struct node *replace_node (struct queue *list, int cur_idx); //перемешение элемента кэша

struct node *add_new_elem(struct queue *list, int cur_idx); //добавление нового элемента в очередь

void move_elem(struct queue* list, struct node* cur_elem); //перемещение элемента в начало

void print_list(struct queue* s); //печать очереди

void delete_queue(struct queue* list); //удаление очереди целиком

void run_tests();

void run_test(const char *filename);

#endif //LRU_CACHE_H
