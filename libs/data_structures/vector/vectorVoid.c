#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>
#include <memory.h>
#include "vectorVoid.h"

vectorVoid createVectorV(size_t n, size_t baseTypeSize){
    vectorVoid res;
    res.data = malloc(sizeof(int) * n);

    if(!res.data){
        fprintf(stderr, "bad alloc");
        exit(1);
    }
    res.size = 0;
    res.capacity = n;
    res.baseTypeSize = baseTypeSize;

    printf("Vector void has been successfully initialized\n");

    return res;
}

void reserveV(vectorVoid *v, size_t newCapacity){
    v->data = realloc(v->data, sizeof(int) * newCapacity);

    if(!v->data){
        fprintf(stderr, "bad alloc");
        exit(1);
    }

    v->capacity = newCapacity;
    v->size = newCapacity < v->size ? newCapacity : v->size;

    printf("Memory has been successfully reallocated\n");
}

void shrinkToFitV(vectorVoid *v){
    v->data = realloc(v->data, sizeof(int)*v->size);
}

void clearV(vectorVoid *v){
    v->size = 0;
}

void deleteVectorV(vectorVoid *v){
    v->size = 0;
    v->capacity = 0;
    v->baseTypeSize = 0;
    free(v->data);
}
