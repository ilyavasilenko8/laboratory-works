#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <assert.h>
#include "vector.h"

vector createVector(size_t n) {
    vector v;
    v.size = n;
    v.capacity = n;
    v.data = (int *) malloc(n * sizeof(int));

    if (v.data == NULL) {
        fprintf(stderr, "bad alloc");
        exit(1);
    }
    return v;
}

void reserve(vector *v, size_t newCapacity) {
    if (newCapacity == 0) {
        free(v->data);
        v->data = NULL;
    } else if (newCapacity < v->size) {
        v->size = newCapacity;
        v->data = realloc(v->data, newCapacity * sizeof(int));

        if (v->data == NULL) {
            fprintf(stderr, "Failed to allocate memory");
            exit(EXIT_FAILURE);
        }
    } else if (newCapacity > v->capacity) {
        v->data = realloc(v->data, newCapacity * sizeof(int));

        if (v->data == NULL) {
            fprintf(stderr, "Failed to allocate memory");
            exit(EXIT_FAILURE);
        }
        v->capacity = newCapacity;
    }
}

void clear(vector *v) {
    v->size = 0;
}


void shrinkToFit(vector *v) {
    v->data = (int *) realloc(v->data, v->size * sizeof(int));
    v->capacity = v->size;
}

void deleteVector(vector *v) {
    free(v->data);
    v->data = NULL;
    v->size = 0;
    v->capacity = 0;
}

bool isEmpty(vector *v) {
    return v->size == 0 ? true : false;
}

bool isFull(vector *v) {
    return v->size == v->capacity ? true : false;
}

int getVectorValue(vector *v, size_t i) {
    return i < v->size ? v->data[i] : -1;
}

void pushBack(vector *v, int x) {
    if (v->size == v->capacity) {
        size_t newCapacity = v->capacity * 2;

        if (v->capacity == 0) {
            newCapacity = 1;
        }
        reserve(v, newCapacity);
    }
    v->data[v->size++] = x;
}


void test_pushBack_emptyVector() {
    vector v = createVector(0);
    pushBack(&v, 1);

    assert(v.size == 1);
    assert(v.capacity == 1);
    assert(v.data[0] == 1);

    deleteVector(&v);
}

void test_pushBack_fullVector() {
    vector v = createVector(1);
    pushBack(&v, 1);
    pushBack(&v, 2);

    assert(v.capacity == 2);
    assert(v.size == 2);
    assert(v.data[1] == 2);

    deleteVector(&v);
}

void test_popBack(vector *v) {
    if (isEmpty(v)) {
        fprintf(stderr, "vector is empty");
        exit(1);
    }

    v->data[v->size--] = 0;
}

void test_popBack_notEmptyVector() {
    vector v = createVector(0);
    pushBack(&v, 10);
    assert(v.size == 1);
    popBack(&v);
    assert(v.size == 0);
    assert(v.capacity == 1);
}