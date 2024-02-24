#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
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

//можно улучшить
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
