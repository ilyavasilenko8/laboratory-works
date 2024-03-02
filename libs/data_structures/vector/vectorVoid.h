#ifndef GIT_PROJECT_VECTORVOID_H
#define GIT_PROJECT_VECTORVOID_H
#include <limits.h>

typedef struct vectorVoid{
    void *data; //указатель на нулевой элемент вектора
    size_t size; //размер вектора
    size_t capacity; // вместимость вектора
    size_t baseTypeSize; //размер базового типа
} vectorVoid;

#endif //GIT_PROJECT_VECTORVOID_H
