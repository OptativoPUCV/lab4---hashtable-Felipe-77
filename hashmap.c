#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "hashmap.h"


typedef struct HashMap HashMap;
int enlarge_called=0;

struct HashMap {
    Pair ** buckets;
    long size; //cantidad de datos/pairs en la tabla
    long capacity; //capacidad de la tabla
    long current; //indice del ultimo dato accedido
};

Pair * createPair( char * key,  void * value) {
    Pair * new = (Pair *)malloc(sizeof(Pair));
    new->key = key;
    new->value = value;
    return new;
}

long hash( char * key, long capacity) {
    unsigned long hash = 0;
     char * ptr;
    for (ptr = key; *ptr != '\0'; ptr++) {
        hash += hash*32 + tolower(*ptr);
    }
    return hash%capacity;
}

int is_equal(void* key1, void* key2){
    if(key1==NULL || key2==NULL) return 0;
    if(strcmp((char*)key1,(char*)key2) == 0) return 1;
    return 0;
}

void insertMap(HashMap * map, char * key, void * value) {

    Pair * newPair = createPair(key, value);

    long index = hash(key, map->capacity);
    

    while (map->buckets[index] != NULL && map->buckets[index]->key != NULL){
        
        if (is_equal(key, map->buckets[index]->key) == 1)
            return;
        index++;

        if (index >= map->size)
            index %= map->capacity;
    }

    map->buckets[index] = newPair;
    map->size += 1;
}

void enlarge(HashMap * map) {
    enlarge_called = 1; //no borrar (testing purposes)
    
    Pair ** aux = map->buckets;
    
    long oldCapacity = map->capacity;
    map->capacity = oldCapacity * 2;
    map->size = 0;

    map->buckets = (Pair**)calloc(map->capacity, sizeof(Pair*));
    for (int i = 0; i < oldCapacity; i++){
        Pair * current = aux[i];
        if (current == NULL) continue;
        insertMap(map, current->key, current->value);
    }
    
    return;
}


HashMap * createMap(long capacity) {
    
    HashMap * new = (HashMap *) malloc(sizeof(HashMap));
    if (new == NULL) exit(EXIT_FAILURE);

    new->buckets = (Pair **) calloc(capacity, sizeof(Pair *));
    if (new->buckets == NULL)   exit(EXIT_FAILURE);
    new->capacity = capacity;
    new->size = 0;
    new->current = -1;

    return new;
}

void eraseMap(HashMap * map,  char * key) {    

    long index = hash(key, map->capacity);
    while (map->buckets[index] != NULL && map->buckets[index]->key != NULL){
        
        if (is_equal(key, map->buckets[index]->key) == 1){
            map->buckets[index]->key = NULL;
            map->size--;
            return;
        }
        
        index++;

        if (index >= map->size)
            index %= map->capacity;
    }
    return ;
}

Pair * searchMap(HashMap * map,  char * key) {   
    if (map->size == 0) return NULL;

    long index = hash(key, map->capacity);
    while (map->buckets[index] != NULL && map->buckets[index]->key != NULL){
        
        if (is_equal(key, map->buckets[index]->key) == 1){
            map->current = index;
            return map->buckets[index];
        }
        
        index++;

        if (index >= map->size)
            index %= map->capacity;
    }
    return NULL;
}

Pair * firstMap(HashMap * map) {
    if (map->size == 0) return NULL;
    long index = 0;

    while (map->buckets[index] == NULL || map->buckets[index]->key == NULL){
        index++;
        if (index >= map->capacity) return NULL;
    }

    map->current = index;
    return map->buckets[index];
}

Pair * nextMap(HashMap * map) {
    if (map->size == 0) return NULL;
    long index = map->current + 1;

    while (map->buckets[index] == NULL || map->buckets[index]->key == NULL){
        index++;

        if (index >= map->capacity) return NULL;
    }

    map->current = index;
    return map->buckets[index];
}
