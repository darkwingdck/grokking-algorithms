// original article - https://www.digitalocean.com/community/tutorials/hash-table-in-c-plus-plus

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CAPACITY 50000

unsigned long hash_function(char* str) {
    unsigned long length = 0;

    for (int i = 0; str[i]; i++) {
        length += str[i];
    }

    return length % CAPACITY;
}

typedef struct HashTable_item {
    char* key;
    char* value;
} HashTable_item;

typedef struct LinkedList {
    HashTable_item* item;
    struct LinkedList* next;
} LinkedList;

typedef struct HashTable {
    HashTable_item** items;
    LinkedList** overflow_buckets;
    int size;
    int count;
} HashTable;

void free_linkedlist(LinkedList* list) {
    LinkedList* temp = list;

    while (list) {
        temp = list;
        list = list->next;
        free(temp->item->key);
        free(temp->item->value);
        free(temp->item);
        free(temp);
    }
}

LinkedList** create_overflow_buckets(HashTable* table) {
    LinkedList** buckets = (LinkedList**) calloc(table->size, sizeof(LinkedList*));

    for (int i = 0; i < table->size; i++) {
        buckets[i] = NULL;
    }

    return buckets;
}

void free_overflow_buckets(HashTable* table) {
    LinkedList** buckets = table->overflow_buckets;

    for (int i = 0; i < table->size; i++) {
        free_linkedlist(buckets[i]);
    }

    free(buckets);
}

HashTable_item* create_item(char* key, char* value) {
    HashTable_item* item = (HashTable_item*) malloc(sizeof(HashTable_item));
    item->key = (char*) malloc(strlen(key) + 1);
    item->value = (char*) malloc(strlen(value) + 1);
    strcpy(item->key, key);
    strcpy(item->value, value);
    return item;
}

HashTable* create_table(int size) {
    HashTable* table = (HashTable*) malloc(sizeof(HashTable));
    table->size = size;
    table->count = 0;
    table->items = (HashTable_item**) calloc(table->size, sizeof(HashTable_item*));

    for (int i = 0; i < table->size; i++) {
        table->items[i] = NULL;
    }

    table->overflow_buckets = create_overflow_buckets(table);

    return table;
}

LinkedList* allocate_list() {
    LinkedList* list = (LinkedList*) malloc(sizeof(LinkedList));
    return list;
}

LinkedList* linkedlist_insert(LinkedList* list, HashTable_item* item) {
    if (!list) {
        LinkedList* head = allocate_list();
        head->item = item;
        head->next = NULL;
        list = head;
        return list;
    } else if (list->next == NULL) {
        LinkedList* node = allocate_list();
        node->item = item;
        node->next = NULL;
        list->next = node;
        return list;
    }

    LinkedList* temp = list;

    while (temp->next->next) {
        temp = temp->next;
    }

    LinkedList* node = allocate_list();
    node->item = item;
    node->next = NULL;
    list->next = node;
    return list;
}

HashTable_item* linkedlist_remove(LinkedList* list) {
    if (!list) {
        return NULL;
    }

    if (!list->next) {
        return NULL;
    }

    LinkedList* node = list->next;
    LinkedList* temp = list;
    temp->next = NULL;
    list = node;
    HashTable_item* it = NULL;
    memcpy(temp->item, it, sizeof(HashTable_item));
    free(temp->item->key);
    free(temp->item->value);
    free(temp->item);
    free(temp);
    return it;    
}

void free_item(HashTable_item* item) {
    free(item->key);
    free(item->value);
    free(item);
}

void free_table(HashTable* table) {
    for (int i = 0; i < table->size; i++) {
        HashTable_item* item = table->items[i];

        if (item != NULL) {
            free_item(item);
        }
    }

    free_overflow_buckets(table);
    free(table->items);
    free(table);
}

void print_table(HashTable* table) {
    printf("\nHash Table\n------------------\n");

    for (int i = 0; i < table->size; i++) {
        if (table->items[i]) {
            printf("Index:%d, Key: %s, Value: %s\n", i, table->items[i]->key, table->items[i]->value);
        }
    }
    printf("------------------------\n\n");
}

void handle_collision(HashTable* table, unsigned long index, HashTable_item* item) {
    LinkedList* head = table->overflow_buckets[index];

    if (head == NULL) {
        head = allocate_list();
        head->item = item;
        table->overflow_buckets[index] = head;
        return;
    } else {
        table->overflow_buckets[index] = linkedlist_insert(head, item);
        return;
    }
}

void hashtable_insert(HashTable* table, char* key, char* value) {
    HashTable_item* item = create_item(key, value);
    unsigned long index = hash_function(key);
    HashTable_item* current_item = table->items[index];
    if (current_item == NULL) {
        if (table->count == table->size) {
            printf("Insert Error: Hash Table is full!\n");
            free_item(item);
            return;
        }

        table->items[index] = item;
        table->count++;
    } else {
        if (strcmp(current_item->key, key) == 0) {
            strcpy(table->items[index]->value, value);
            return;
        } else {
            handle_collision(table, index, item);
            return;
        }
    }
}

void hashtable_delete(HashTable* table, char* key) {
    unsigned long index = hash_function(key);
    HashTable_item* item = table->items[index];
    if (item == NULL) return;

    LinkedList* head = table->overflow_buckets[index];

    if (head == NULL) {
        if (strcmp(item->key, key) != 0) return;
        table->items[index] = NULL;
        free_item(item);
        table->count--;
        return;
    }

    if (strcmp(item->key, key) == 0) {
        free_item(item);
        LinkedList* node = head;
        head = head->next;
        node->next = NULL;
        table->items[index] = create_item(node->item->key, node->item->value);
        free_linkedlist(node);
        table->overflow_buckets[index] = head;
        return;
    }

    LinkedList* cur = head;
    LinkedList* prev = NULL;

    while (cur) {
        if (strcmp(cur->item->key, key) == 0) {
            if (prev == NULL) {
                free_linkedlist(head);
                table->overflow_buckets[index] = NULL;
                return;
            } else {
                prev->next = cur->next;
                cur->next = NULL;
                free_linkedlist(cur);
                table->overflow_buckets[index] = head;
                return;
            }
        }

        cur = cur->next;
        prev = cur;
    }

}

char* hashtable_search(HashTable* table, char* key) {
    unsigned long index = hash_function(key);
    HashTable_item* item = table->items[index];
    LinkedList* head = table->overflow_buckets[index];

    if (item != NULL) {
        if (strcmp(item->key, key) == 0) {
            return item->value;
        }

        if (head == NULL) {
            return NULL;
        }

        item = head->item;
        head = head->next;
    }

    return NULL;
}

void print_search(HashTable* table, char* key) {
    char* val;

    if ((val = hashtable_search(table, key)) == NULL) {
        printf("Key:%s does not exist\n", key);
        return;
    } else {
        printf("Key:%s, Value:%s\n", key, val);
    }
}

int main(int argc, char const *argv[]) {
    HashTable *ht = create_table(CAPACITY);
    hashtable_insert(ht, (char *)"1", (char *)"First address");
    hashtable_insert(ht, (char *)"2", (char *)"Second address");
    hashtable_insert(ht, (char *)"Hel", (char *)"Third address");
    hashtable_insert(ht, (char *)"Cau", (char *)"Fourth address");
    print_search(ht, (char *)"1");
    print_search(ht, (char *)"2");
    print_search(ht, (char *)"3");
    print_search(ht, (char *)"Hel");
    print_search(ht, (char *)"Cau");
    print_table(ht);
    hashtable_delete(ht, (char *)"1");
    hashtable_delete(ht, (char *)"Cau");
    print_table(ht);
    free_table(ht);
    return 0;
}
