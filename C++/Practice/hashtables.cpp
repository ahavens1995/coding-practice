//Code taken from https://www.digitalocean.com/community/tutorials/hash-table-in-c-plus-plus
//Used for educational/tutorial purposes

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//shortening
using namespace std;

#define CAPACITY 50000 //size of hashtable

unsigned long hash_function(char* str)
{
    unsigned long i = 0;

    for (int j = 0; str[j]; j++)
        i += str[j];
    
    return i % CAPACITY;
}

typedef struct Hash_Item
{

    char* key;
    char* val;

}Hash_Item;

typedef struct HashTable
{
    //contains an array of pointers to items
    Hash_Item** items;
    //every item has a chain so the whole table is an array of LinkedList pointers
    LinkedList** overflow_buckets;
    int size;
    int count;

}HashTable;

typedef struct LinkedList {
    Hash_Item* item;
    struct LinkedList* next;
}LinkedList;

Hash_Item* create_item(char* key, char* val)
{

    Hash_Item* item = (Hash_Item*) malloc(sizeof(Hash_Item));
    item->key = (char*) malloc(strlen(key) + 1);
    item->val = (char*) malloc(strlen(val));
    
    //Copies the C string pointed by source into the array pointed by destination, including the terminating null character (and stopping at that point)
    strcpy(item->key, key);
    strcpy(item->val, val);
    
    return item;

}

LinkedList** create_overflow_buckets(HashTable* table)
{
    //create overflow buckets, which are an array of linked lists
    LinkedList** buckets = (LinkedList**) calloc(table->size, sizeof(LinkedList*));

    for(int i = 0; i < table->size; i++)
    {
        buckets[i] = NULL;
    }

    return buckets;
}

void free_overflow_buckets(HashTable* table)
{
    //free overflow bucket lists
    LinkedList** buckets = table->overflow_buckets;
    
    for(int i = 0; i < table->size; i++)
    {
        free_linkedlist(buckets[i]);
    }

    free(buckets);
}

HashTable* create_table(int size)
{
    //Create a new Hashtable
    HashTable* table = (HashTable*) malloc(sizeof(HashTable));
    table->size = size;
    table->count = 0;
    table->items = (Hash_Item**) calloc(table->size, sizeof(Hash_Item*));

    for(int i = 0; i < table->size; i++)
    {
        table->items[i] = NULL;
    }

    table->overflow_buckets = create_overflow_buckets(table);

    return table;
}

void free_item(Hash_Item* item)
{
    free(item->key);
    free(item->val);
    free(item);
}

void free_Table(HashTable* table)
{
    //free the table
    for(int i = 0; i < table->size; i++)
    {
        Hash_Item* item = table->items[i];

        if(item != NULL)
        {
            free_item(item);
        }
    }

    free_overflow_buckets(table);
    free(table->items);
    free(table);
}

void print_table(HashTable* table)
{
    printf("\nHash Table\n--------------------\n");

    for(int i = 0; i < table->size; i++)
    {
        if(table->items[i])
        {
            printf("Index:%d, Key:%s, Value:%s\n", i, table->items[i] -> key, table->items[i]->val);
        }
    }

    printf("----------------\n\n");
}

void handle_collision(HashTable* table, unsigned long index, Hash_Item* item)
{
    LinkedList* head = table->overflow_buckets[index];

    if(head == NULL)
    {
        //Creates the list
        head = allocate_list();
        head->item = item;
        table->overflow_buckets[index] = head;
        return;
    }
    else
    {
        //insert to the list
        table->overflow_buckets[index] = linkedlist_insert(head, item);
        return;
    }
}

void hashtable_insert(HashTable* table, char* key, char* val)
{
    //create a hash item
    Hash_Item* item = create_item(key, val);

    //determine location in table to be inserted
    int index = hash_function(key);

    Hash_Item* current_item = table->items[index];

    //if they item does not exist
    if(current_item == NULL)
    {
        // HasbTable is full, exit the function
        if (table->count == table->size)
        {
            printf("Insert Error: Hash Table is full\n");
            free_item(item);
            return;
        }
    }
    else // Scenario 1: Update the value at the index
    {
        //compare the strings and if they're equal then update the value
        if (strcmp(current_item->key, key) == 0)
        {
            current_item->val = val;
        }
        else
        {
            handle_collision(table, index, item);
            return;
        }
    }

    //Insert directly
    table->items[index] = item;
    table->count++;

}

char* hashtable_search(HashTable* table, char* key)
{
    //searches for key in hashtable returns Null if doesn't exist
    int index = hash_function(key);
    Hash_Item* item = table->items[index];
    LinkedList* head = table->overflow_buckets[index];

    if(item != NULL)
    {
        if(strcmp(item->key, key) == 0)
            return item->val;
        
        if(head == NULL)
            return NULL;
        
        item = head->item;
        head = head->next;
    }

    return NULL;
}

LinkedList* allocate_list()
{
    //Allocates mem for a LinkedList pointer
    LinkedList* list = (LinkedList*) malloc(sizeof(LinkedList));
    return list;
}

LinkedList* linkedlist_insert(LinkedList* list, Hash_Item* item)
{
    //insert item into LinkedList
    //If the list is empty
    if(!list)
    {
        LinkedList* head = allocate_list();
        head->item = item;
        head->next = NULL;
        list = head;
        return list;
    }
    else if(list->next == NULL)
    {
        //if the list has one item in it
        LinkedList* node = allocate_list();
        node->item = item;
        node->next = NULL;
        list->next = node;
        return list;
    }

    //if the list has multiple items in it
    LinkedList* temp = list;

    //while the next node of the next node is not empty
    while(temp->next->next)
    {
        temp = temp->next;
    }

    //once we've reached the point where the next item is null
    LinkedList* node = allocate_list();
    node->item = item;
    node->next = NULL;
    temp->next = node;

    //temp = list, so the lists are the same
    return list;
}

Hash_Item* linkedlist_remove(LinkedList* list)
{
    //remove head from linked list and return the item
    
    //if list is empty return null
    if(!list)
    {
        return NULL;
    }
        
    //if there was only one item in the list, return NULL
    if(!list->next)
    {
        return NULL;
    }

    LinkedList* node = list->next;
    LinkedList* temp = list;

    //disconnect the head
    temp->next = NULL;
    //set the head to the next node
    list = node;
    Hash_Item* it = NULL;

    memcpy(temp->item, it, sizeof(Hash_Item));

    free(temp->item->key);
    free(temp->item->val);
    free(temp->item);
    free(temp);

    return it;
   
}

void free_linkedlist(LinkedList* list)
{
    LinkedList* temp = list;

    while(list)
    {
        temp = list;
        list = list->next;
        free(temp->item->key);
        free(temp->item->val);
        free(temp->item);
        free(temp);
    }
}

void hash_delete(HashTable* table, char* key)
{
    //deletes an item from the table
    int index = hash_function(key);
    Hash_Item* item = table->items[index];
    LinkedList* head = table->overflow_buckets[index];

    //if nothing in the table at that point
    if(item == NULL)
    {
        return;
    }
    else{
        //if head of the list is NULL, and the keys are the same
        if(head == NULL && strcmp(item->key, key) == 0)
        {
            //collision does not exist, so remove the item and set table index to NULL
            table->items[index] = NULL;
            free_item(item);
            table->count--;
            return;
        }
        else if(head != NULL){
            //collision chain does exist
            if(strcmp(item->key, key) == 0)
            {
                //remove this item
                //set head of the list as a new item
                free_item(item);
                LinkedList* node = head;
                head = head->next;
                node->next = NULL;
                table->items[index] = create_item(node->item->key, node->item->val);
                free_linkedlist(node);
                table->overflow_buckets[index] = head;
                return;
            }

            LinkedList* curr = head;
            LinkedList* prev = NULL;

            while(curr)
            {
                if(strcmp(curr->item->key, key) == 0)
                {
                    if(prev == NULL)
                    {
                        //First element of the chain
                        //remove chain
                        free_linkedlist(head);
                        table->overflow_buckets[index] = NULL;
                        return;
                    }
                    else
                    {
                        //this is somewhere in the chain
                        prev->next = curr->next;
                        curr->next = NULL;
                        free_linkedlist(curr);
                        table->overflow_buckets[index] = head;
                        return;
                    }
                }

                curr = curr->next;
                prev = curr;
            }

        }
    }

}

void print_search(HashTable *table, char *key)
{
    char *val;

    if((val = hashtable_search(table, key)) == NULL)
    {
        printf("Key: %s does not exist\n", key);
        return;
    }
    else
    {
        printf("Key:%s, Value%s\n", key, val);
    }
}

int main(){

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
    hash_delete(ht, (char *)"1");
    hash_delete(ht, (char *)"Cau");
    print_table(ht);
    free_Table(ht);

    return 0;

};