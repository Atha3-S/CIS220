//Merkins, William
//Chpt6 PA
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define structure to represent the key-value pair (Item)
typedef struct Item {
    char *key;  
    char *value;  
    struct Item *next;  
} Item;

// Define structure to represent the hash table
typedef struct HashTable {
    Item **hashTable;  
    int length;  
} HashTable;

// Function to create a new Item (key-value pair)
Item* createItem(char *key, char *value) {
    Item *newItem = (Item*)malloc(sizeof(Item));  
    newItem->key = strdup(key);  
    newItem->value = strdup(value);  
    newItem->next = NULL;  
    return newItem;
}

// Function to create a new hash table with a specified number of buckets
HashTable* createHashTable(int size) {
    HashTable *table = (HashTable*)malloc(sizeof(HashTable));  
    table->length = size;  
    table->hashTable = (Item**)malloc(sizeof(Item*) * size);  

    for (int i = 0; i < size; i++) {
        table->hashTable[i] = NULL;  
    }
    return table;
}

// Hash function implementation
int hash(char *key) {
    int stringHash = 0;
    int multiplier = 13;
    while (*key) {
        stringHash = stringHash * multiplier + *key;
        key++;
    }
    return stringHash;
}

// Function to insert a key-value pair into the hash table
int hashInsert(HashTable *table, char *key, char *value) {
    int bucketIndex = hash(key) % table->length;
    if (bucketIndex < 0) bucketIndex += table->length;
    
    Item *currentItem = table->hashTable[bucketIndex];
    Item *previousItem = NULL;

    while (currentItem != NULL) {
        if (strcmp(currentItem->key, key) == 0) {
            free(currentItem->value);
            currentItem->value = strdup(value);
            return 1;
        }
        previousItem = currentItem;
        currentItem = currentItem->next;
    }

    Item *newItem = createItem(key, value);
    newItem->next = table->hashTable[bucketIndex];
    table->hashTable[bucketIndex] = newItem;
    return 1;  
}

// Function to search for the specified key
char *hashGet(HashTable *table, char *key) {
    int bucketIndex = hash(key) % table->length;
    if (bucketIndex < 0) bucketIndex += table->length;
    
    Item *item = table->hashTable[bucketIndex];
    while (item != NULL) {
        if (strcmp(item->key, key) == 0) {
            return item->value;
        }
        item = item->next;
    }
    return NULL;
}

// Function to remove a key-value pair
int hashRemove(HashTable *table, char *key) {
    int bucketIndex = hash(key) % table->length;
    if (bucketIndex < 0) bucketIndex += table->length;
    
    Item *currentItem = table->hashTable[bucketIndex];
    Item *previousItem = NULL;

    while (currentItem != NULL) {
        if (strcmp(currentItem->key, key) == 0) {
            if (previousItem == NULL) {
                table->hashTable[bucketIndex] = currentItem->next;
            } else {
                previousItem->next = currentItem->next;
            }
            free(currentItem->key);
            free(currentItem->value);
            free(currentItem);
            return 1;
        }
        previousItem = currentItem;
        currentItem = currentItem->next;
    }
    return 0;
}

// Function to print the hash table contents
void printTable(HashTable *table) {
    for (int i = 0; i < table->length; i++) {  
        printf("Bucket %d: ", i);  
        Item *currentItem = table->hashTable[i];  
        if (currentItem == NULL) {  
            printf("empty\n");  
        } else {
            while (currentItem != NULL) {  
                printf("[Hash is: %d, key is: %s, value is: %s] ", hash(currentItem->key), currentItem->key, currentItem->value);  
                currentItem = currentItem->next;  
            }
            printf("\n");  
        }
    }
}

// Main function
int main() {
    HashTable *table = createHashTable(5);
    
    hashInsert(table, "keyA1", "value1");
    hashInsert(table, "keyB2", "value2");
    hashInsert(table, "keyC3", "value3");
    hashInsert(table, "keyD23", "value23");
    hashInsert(table, "keyE45", "value45");
    hashInsert(table, "keyF52", "value52");
    
    printTable(table);
    
    if (hashRemove(table, "keyF52"))
        printf("\nkeyF52 was removed\n");
    else
        printf("\nFailed to remove keyF52.\n");
    
    if (hashGet(table, "keyZ6"))
        printf("\nFound keyZ6: %s\n", hashGet(table, "keyZ6"));
    else
        printf("\nkeyZ6 not found.\n");
    
    if (hashGet(table, "keyC3"))
        printf("\n%s\n", hashGet(table, "keyC3"));
    else
        printf("\nkeyC3 was not found.\n");
    
    hashInsert(table, "keyG18", "value18");
    hashInsert(table, "keyH7", "value7");
    hashInsert(table, "keyI33", "value33");
    hashInsert(table, "keyD23", "newvalue23");
    
    printTable(table);
    
    free(table->hashTable);
    free(table);
    return 0;
}
