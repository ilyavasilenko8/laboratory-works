#ifndef GIT_PROJECT_VECTORVOID_H
#define GIT_PROJECT_VECTORVOID_H

#include <limits.h>

typedef struct vectorVoid {
    void *data; //указатель на нулевой элемент вектора
    size_t size; //размер вектора
    size_t capacity; // вместимость вектора
    size_t baseTypeSize; //размер базового типа
} vectorVoid;


vectorVoid createVectorV(size_t n, size_t baseTypeSize);

void reserveV(vectorVoid *v, size_t newCapacity);

void shrinkToFitV(vectorVoid *v);

void clearV(vectorVoid *v);

void deleteVectorV(vectorVoid *v);


bool isEmpty(vectorVoid *v);

bool isFull(vectorVoid *v);

void getVectorValueV(vectorVoid *v, size_t index, void *destination);

void setVectorValueV(vectorVoid *v, size_t index, void *source);

void popBackV(vectorVoid *v);

void pushBackV(vectorVoid *v, void *source);

void test1();

void test2();

#endif //GIT_PROJECT_VECTORVOID_H
