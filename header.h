//
// Created by Kostenok Elizaveta, Tsepkova Alexandra, Shirikova Ksenia on 10.05.2020.
//

#include <stdio.h>
#include <stdlib.h>

//hash table

struct hash* Create_table();

struct hash_node* Check_index (int index, struct hash* table);

void Delete_table(struct hash* table);
