#include <stdlib.h>
#include <string.h>
#include "tabhash.h"

Info new_id(int address) {
    Info aux = (Info) malloc(sizeof(struct info));
    aux->address = address;
    aux->maxsizeX = 1;
    aux->maxsizeY = 0;
    aux->type = Id;
    return aux;
}

Info new_array(int address, int size) {
    Info aux = (Info) malloc(sizeof(struct info));
    aux->address = address;
    aux->maxsizeX = size;
    aux->maxsizeY = 0;
    aux->type = ARRAY;
    return aux;
}

Info new_matrix(int address, int sizeX, int sizeY) {
    Info aux = (Info) malloc(sizeof(struct info));
    aux->address = address;
    aux->maxsizeX = sizeX;
    aux->maxsizeY = sizeY;
    aux->type = MATRIX;
    return aux;
}

/* Create a new hashtable. */
HashTable *ht_create(int size) {
    int i;
    HashTable *hashtable = NULL;

    if (size < 1)
        return NULL;
    /* Allocate the table itself. */
    if ((hashtable = (HashTable *) malloc(sizeof(HashTable))) == NULL)
        return NULL;
    /* Allocate pointers to the head nodes. */
    if ((hashtable->table = (Entry **) malloc(sizeof(Entry *) * size)) == NULL)
        return NULL;

    for (i = 0; i < size; i++)
        hashtable->table[i] = NULL;

    hashtable->used = 0;
    hashtable->size = size;
    return hashtable;
}

/* Hash a string. */
unsigned long ht_hash(char *key) {
    unsigned long hash = 5381;
    int c;
    while ((c = *key++) != 0)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    return hash;
}

/* Create a key-value pair. */
Entry *ht_newpair(char *key, Info value) {
    Entry *newpair;
    newpair = (Entry *) malloc(sizeof(Entry));
    newpair->key = strdup(key);
    newpair->value = value;
    newpair->next = NULL;
    return newpair;
}

/* Insert a key-value pair into a hash table. */
bool ht_set(HashTable *hashtable, char *key, Info value) {
    int i, bin = 0;
    Entry *newpair = NULL;
    Entry *next = NULL;
    Entry *last = NULL;

    bin = ht_hash(key) % hashtable->size;
    next = hashtable->table[bin];

    while (next != NULL && next->key != NULL && strcmp(key, next->key) != 0) {
        last = next;
        next = next->next;
    }
    // If there's already a pair, it has to give an ERROR
    if (next != NULL && next->key != NULL && strcmp(key, next->key) == 0)
        return false;
    else {
        hashtable->used++;
        newpair = ht_newpair(key, value);
        // We're at the start of the linked list in this bin.
        if (next == hashtable->table[bin]) {
            newpair->next = next;
            hashtable->table[bin] = newpair;
        // We're at the end of the linked list in this bin.
        } else if (next == NULL) {
            last->next = newpair;
        /* We're in the middle of the list. */
        } else {
            newpair->next = next;
            last->next = newpair;
        }
        return true;
    }
}

/* Retrieve a key-value pair from a hash table. */
Info ht_get(HashTable *hashtable, char *key) {
    int bin = 0;
    Entry *pair;

    bin = ht_hash(key) % hashtable->size;
    /* Step through the bin, looking for our value. */
    pair = hashtable->table[bin];

    while (pair != NULL && pair->key != NULL && strcmp(key, pair->key) != 0)
        pair = pair->next;
    /* Did we actually find anything? */
    if (pair == NULL || pair->key == NULL || strcmp(key, pair->key) != 0)
        return NULL;
    else
        return pair->value;
}
