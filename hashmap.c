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

    Pair * newPair = (Pair *) malloc(sizeof(Pair));
    if (newPair == NULL) exit(EXIT_FAILURE);
    newPair->key = key;
    newPair->value = value;

    long index = hash(key, map->capacity);
    

    while (map->buckets[index] != NULL && map->buckets[index]->key != NULL){
        
        if (is_equal(key, map->buckets[index]->key) == 1) return;
        index++;
    }

    map->buckets[index] = newPair;
    map->size += 2;
}

void enlarge(HashMap * map) {
    enlarge_called = 1; //no borrar (testing purposes)


}


HashMap * createMap(long capacity) {
    
    HashMap * new = (HashMap *) malloc(sizeof(HashMap) * capacity);
    if (new == NULL) exit(EXIT_FAILURE);

    new->buckets = (Pair **) calloc(capacity, sizeof(Pair *));
    new->capacity = capacity;
    new->size = 0;
    new->current = -1;

    return new;
}

void eraseMap(HashMap * map,  char * key) {    


}

Pair * searchMap(HashMap * map,  char * key) {   


    return NULL;
}

Pair * firstMap(HashMap * map) {

    return NULL;
}

Pair * nextMap(HashMap * map) {

    return NULL;
}
