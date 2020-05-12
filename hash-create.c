#include"header.h"

const int TABLESIZE = 10;

struct page {
    int index;
    char* data;
    int n; //кол-во символов
};
struct node {
    char* data;
    int index;
    struct node* next;
    struct node* prev;
};

struct queue {
    int capacity;
    int length;
    struct node* head;
    struct node* tail;
};

struct hash {
  int capacity;
  struct hash_node *elem;
};

struct hash_node {
  int index;
  struct node *n_cache;
  struct hash_node *next;
};

struct hash *create_table(){
  struct hash *table = (struct hash *)calloc(1,sizeof(struct hash));
  table->capacity = TABLESIZE;
  table->elem = (struct hash_node *)calloc(table->capacity, sizeof(struct_hash node));
  for(int i = 0; i < table->capacity; i++){
    table->elem[i] = NULL;
  }
  return table;
}

void delete_from_hash(int last_idx, struct hash* table) {
  int idx = hash_func(last_idx);
  struct hash_node* cur = table->elem[idx];
  if ((cur->index) == last_idx) {
    table->elem[idx] = cur->next;
    remove_hash_node(cur);
  }
  else {
    while ((cur->next->index) != last_idx)
      cur = cur->next;
    cur->next = cur->next->next;
    remove_hash_node(cur);
  }
}

void remove_hash_node(struct hash_node* p) {
  p->next = NULL;
  p->index = -666;
  free(p);
}

struct node *add_new_page (struct page *page, struct hash *table, struct queue *list) {
  struct hash_node *current = NULL, *check = NULL;
  int last_idx = 0, i = 0, index;
  struct node *newnode;
  index = page->index;
  check = Check_index(index, table);
  i = Hash_func(index);
  if (check == NULL) { //такого элемента нет - создаем новый
    newnode = add_new_elem(list, page, &last_idx);
    current = table->elem[i];
    while (current != NULL) current = current->next;
    current -> index = index;
    current -> n_cache = newnode;
    current -> next = NULL;
    if(last_idx != 0)
      delete_from_hash(last_idx, table);
    return newnode;
  }
  else { //такой элемент есть, перемещаем его в кэше, хэш-таблицу не трогаем
    newnode = move_elem(list, check->n_cache);
    return newnode;
  }
}
