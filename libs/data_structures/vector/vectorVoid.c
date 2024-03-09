#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>
#include <memory.h>
#include "vectorVoid.h"

vectorVoid createVectorV(size_t n, size_t baseTypeSize) {
    vectorVoid res;
    res.data = malloc(sizeof(int) * n);

    if (!res.data) {
        fprintf(stderr, "bad alloc");
        exit(1);
    }
    res.size = 0;
    res.capacity = n;
    res.baseTypeSize = baseTypeSize;

    printf("Vector void has been successfully initialized\n");

    return res;
}

void reserveV(vectorVoid *v, size_t newCapacity) {
    v->data = realloc(v->data, sizeof(int) * newCapacity);

    if (!v->data) {
        fprintf(stderr, "bad alloc");
        exit(1);
    }

    v->capacity = newCapacity;
    v->size = newCapacity < v->size ? newCapacity : v->size;

    printf("Memory has been successfully reallocated\n");
}

void shrinkToFitV(vectorVoid *v) {
    v->data = realloc(v->data, sizeof(int) * v->size);
}

void clearV(vectorVoid *v) {
    v->size = 0;
}

void deleteVectorV(vectorVoid *v) {
    v->size = 0;
    v->capacity = 0;
    v->baseTypeSize = 0;
    free(v->data);
}

bool isEmptyV(vectorVoid *v) {
    return v->size == 0 ? true : false;
}

bool isFull(vectorVoid *v) {
    return v->size == v->capacity ? true : false;
}

void getVectorValue(vectorVoid *v, size_t index, void *destination) {
    char *source = (char *) v->data + index * v->baseTypeSize;
}

void setVectorValueV(vectorVoid *v, size_t index, void *source) {
    char *destination = (char *) v->data + index * v->baseTypeSize;
    memcpy(destination, source, v->baseTypeSize);
}

void popBackV(vectorVoid *v) {
    if (isEmptyV(v)) {
        fprintf(stderr, "vector void is empty");
        exit(1);
    }
    (v->size)--;
}

void pushBackV(vectorVoid *v, void *source) {
    if (v->size == v->capacity) {
        size_t newCapacity = v->capacity * 2;

        if (v->capacity == 0) {
            newCapacity = 1;
        }
        reserveV(v, newCapacity);
    }
    setVectorValueV(v, v->size++, source);
}

void test1() {
    size_t n;
    scanf("%zd", &n);
    vectorVoid v = createVectorV(0, sizeof(int));
    for (int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);
        pushBackV(&v, &x);
    }
    for (int i = 0; i < n; i++) {
        int x;
        getVectorValueV(&v, i, &x);
        printf("%d ", x);
    }
}

void test2() {
    size_t n;
    scanf("%zd", &n);
    vectorVoid v = createVectorV(0, sizeof(float));
    for (int i = 0; i < n; i++) {
        float x;
        scanf("%f", &x);
        pushBackV(&v, &x);
    }
    for (int i = 0; i < n; i++) {
        float x;
        getVectorValueV(&v, i, &x);
        printf("%f ", x);
    }
}