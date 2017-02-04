#ifndef _HASH
#define _HASH

typedef enum { true, false } bool;
typedef enum { Id, ARRAY, MATRIX } Type;

typedef struct info {
    int address;
    int maxsizeX, maxsizeY;
    Type type;
} *Info;

typedef struct entry {
    char *key;
    Info value;
    struct entry *next;
} Entry;

typedef struct hashtable {
    int size, used;
    Entry **table;
} HashTable;

Info new_id( int );
Info new_array( int,int );
Info new_matrix( int,int,int );

HashTable *ht_create( int );
bool ht_set( HashTable *,char *,Info );
Info ht_get( HashTable *,char * );

#endif
