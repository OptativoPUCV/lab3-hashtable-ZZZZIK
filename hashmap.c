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
  long indice= hash(key,map->capacity);
  
  while(1) {
    if ((map->buckets[indice]==NULL)||(map->buckets[indice]->key==NULL)){
      map->buckets[indice]= createPair(key,value);
      map->current= indice;
      map->size++;
      return;  
    }   
    indice=(indice + 1) % map->capacity;
    map->buckets[indice]= map->buckets[indice];
  }
}

void enlarge(HashMap * map) {
    enlarge_called = 1; //no borrar (testing purposes)


}


HashMap * createMap(long capacity) {
    HashMap * mapa_nuevo = (HashMap *)malloc(sizeof(HashMap));
    mapa_nuevo->buckets = (Pair **)malloc(capacity * sizeof(Pair *));
    mapa_nuevo->size = 0;
    mapa_nuevo->capacity = capacity;
    mapa_nuevo->current = -1;
    return mapa_nuevo;
}

void eraseMap(HashMap * map,  char * key) {    


}

Pair * searchMap(HashMap * map,  char * key) {   
  long indice=hash(key,map->capacity);
  
  for (long i=0;i<map->capacity;i++){
    if (map->buckets[indice]!= NULL && strcmp(map->buckets[indice]->key,key) ==0){
      map->current=indice;
      return map->buckets[indice];
    }
    indice=(indice+1)%map->capacity;
  }

  return NULL;
} 


  

Pair * firstMap(HashMap * map){
  long i=0;
  while(i<map->capacity){
    if (map->buckets[i]!=NULL){
      if(map->buckets[i]->key!=NULL){
        if(map->buckets[i]->value!=NULL){
          map->current=i;
          return map->buckets[i];
        }   
      }
    }
    i++;
  }
  return NULL;
}

Pair * nextMap(HashMap * map) {
  long i=map->current+1;
  while(i<map->capacity){
    if (map->buckets[i]!=NULL){
      if(map->buckets[i]->key!=NULL){
        if(map->buckets[i]->value!=NULL){
          map->current=i;
          return map->buckets[i];
        }   
      }
    }
    i++;
  }
  return NULL;
}
