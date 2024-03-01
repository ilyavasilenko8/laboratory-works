#ifndef GIT_PROJECT_VECTOR_H
#define GIT_PROJECT_VECTOR_H

#include <stdio.h>
#include <stdbool.h>

typedef struct vector {
    int *data;
    size_t size;
    size_t capacity;
} vector;

//возвращает структуру-дескриптор вектор из n значений
vector createVector(size_t n);

//изменяет кол-во памяти, выделенное под хранение элементов вектора
void reserve(vector *v, size_t newCapacity);

//удаляет элементы из контейнера, но не освобождает выделенную память
void clear(vector *v);

//освобождает память, выделенную под неиспользуемые элементы
void shrinkToFit(vector *v);

//освобождает память, выделенную вектору
void deleteVector(vector *v);

//проверка на то, является ли вектор пустым
bool isEmpty(vector *v);

//проверка на то, явлется ли вектор полным
bool isFull(vector *v);

//возвращает i-ый элемент вектора v
int getVectorValue(vector *v, size_t i);

//добавляет элемент x в конец вектора v
void pushBack(vector *v, int x);

void test_pushBack_emptyVector();

//удаляет последний элемент из вектора
void popBack(vector *v);

void test_popBack_notEmptyVector();

//возвращает указатель на index-ый элемент вектора
int *atVector(vector *v, size_t index);

//возвращает указатель на последний элемент вектора
int *back(vector *v);

//возвращает указатель на нудевой элемент вектора
int *front(vector *v);

void test_atVector_notEmptyVector();

void test_atVector_requestToLastElement();

void test_back_oneElementInVector();

void test_front_oneElementInVector();

void test();

#endif //GIT_PROJECT_VECTOR_H
