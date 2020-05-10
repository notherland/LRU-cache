#include"header.h"

const int TABLESIZE = 10;

struct hash {
  int capacity;
  struct hash_node *elem;
};

struct hash_node {
  int index;
  struct node *n_cache;
  struct hash_node *next;
}

struct hash *create_table(){
  struct hash *table = (struct hash *)calloc(1,sizeof(struct hash));
  table->capacity = TABLESIZE;
  table->elem = (struct hash node *)calloc(capacity, sizeof(struct hash node));
  for(int i = 0; i < table->capacity, i++){
    table->elem[i] = NULL;
  }
  return table;
} 

struct hash_node *add_hash_node (int index, struct node *node, struct hash *table) {
  struct hash_node *current = NULL, *prev = NULL, check;
  check = Checl_index(index, table);
  if (check == NULL) { 
    current = table->elem[i];
    while (current != NULL) current = current->next;
    current -> index = index;
    current -> n_cache = node;
    current -> next = NULL;
    //add_and_delete(queue, node->data) - если нет этого элемента, то добавляем его в очередь и удаляем последний
    return current;
  }
  else {
    //move(check->n_cache, index, queue) //если у нас уже есть этот элемент в очереди - двигаем его
    return check;   
  }
}
