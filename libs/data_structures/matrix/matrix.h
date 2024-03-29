#ifndef GIT_PROJECT_MATRIX_H
#define GIT_PROJECT_MATRIX_H

#include <stdbool.h>
#include <stddef.h>

typedef struct matrix {
    int **values; //элемент матрицы
    int nRows; //кол-во рядов
    int nCols; //кол-во столбцов
} matrix;

typedef struct position {
    int rowIndex;
    int colIndex;
} position;

//размещает в динамической памяти матрицу размером nRows на nCols
matrix getMemMatrix(int nRows, int nCols);

//размещает в динамической памяти массив из nMatrices матриц размером nRows на nCols
matrix *getMemArrayOfMatrices(int nMatrices, int nRows, int nCols);

//освобождает память выделенную под хранение матрицы m
void freeMemMatrix(matrix *m);

//освобождает память, выделенную под хранение массива ms из nMatrices матриц
void freeMemMatrices(matrix *ms, int nMatrices);

//ввод матрицы m
void inputMatrix(matrix *m);

//ввод массива из nMatrices матриц, хранящиеся по адресу ms
void inputMatrices(matrix *ms, int nMatrices);

//вывод матрицы m
void outputMatrix(matrix m);

//вывод массива из nMatrices матриц, хранящейся по адресу ms
void outputMatrices(matrix *ms, int nMatrices);


//обмен строк с порядковыми номерами i1 и i2 в матрице m
void swapRows(matrix *m, int i1, int i2);

//обмен колонок с порядковыми номерами j1 и j2 в матрице m
void swapColumns(matrix *m, int j1, int j2);

//выполняет сортировку вставками строк матрицы m по неубыванию значения функции criteria применяемой для строк
void insertionSortRowsMatrixByRowCriteria(matrix m, int (*criteria)(int *, int));

//вычесляет сумму одномерного массива
int getSum(int *a, int n);

//выполняет сортировку выбором столбцов матрицы m по неубыванию значения функции criteria применяемой для столбцов
void selectionSortColsMatrixByColCriteria(matrix m, int (*criteria)(int *, int));

//возвращает значение ’истина’, если матрица m является квадратной, ложь – в противном случае
bool isSquareMatrix(matrix *m);

//возвращает значение ’истина’, если матрицы m1 и m2 равны, ложь – в противном случае
bool areTwoMatricesEqual(matrix *m1, matrix *m2);

//возвращает значение ’истина’, если матрица m является единичной, ложь – в противном случае
bool isEMatrix(matrix *m);

//возвращает значение ’истина’, если матрица m является симметричной, ложь – в противном случае
bool isSymmetricMatrix(matrix *m);

//транспонирует квадратную матрицу m
void transposeSquareMatrix(matrix *m);

//транспонирует матрицу m
void transposeMatrix(matrix *m);

//возвращает позицию минимального элемента матрицы m
position getMinValuePos(matrix m);

//возвращает позицию максимального элемента матрицы m
position getMaxValuePos(matrix m);

//возвращает матрицу размера nRows на nCols, построенную из элементов массива a
matrix createMatrixFromArray(const int *a, size_t nRows, size_t nCols);

//возвращает указатель на нулевую матрицу массива из nMatrices матриц, размещенных
//в динамической памяти, построенных из элементов массива a
matrix *createArrayOfMatrixFromArray(const int *values, size_t nMatrices, size_t nRows, size_t nCols);

void test_swap_rows();

void test_swap_columns();

void test_is_square_matrix_true();

void test_is_square_matrix_false();

void test_is_e_matrix_true();

void test_is_e_matrix_false();

void test_is_symmetric_matrix_true();

void test_is_symmetric_matrix_false();

void test_transpose_matrix();

void test_get_min_value_pos();

void test_get_max_value_pos();

void test_matrix();


void swap_rows_with_min_and_max_element(matrix *m);

void test_swap_rows_with_min_and_max_element_1();

void test_swap_rows_with_min_and_max_element_2();

void test_swap_rows_with_min_and_max_element();

int getMax(int *a, int n);

void sortRowsByMinElement();

void test_sortRowsByMinElement_1();

void test_sortRowsByMinElement_2();

void test_sortRowsByMinElement();

int getMin(int *a, int n);

void sortColsByMinElement(matrix *m);

void test_sortColsByMinElement_1();

void test_sortColsByMinElement_2();

void test_sortColsByMinElement();

matrix mulMatrices(matrix m1, matrix m2);

void getSquareOfMatrixIfSymmetric(matrix *m);

void test_getSquareOfMatrixIfSymmetric_1();

void test_getSquareOfMatrixIfSymmetric_2();

void test_getSquareOfMatrixIfSymmetric_3();

void test_getSquareOfMatrixIfSymmetric();
#endif //GIT_PROJECT_MATRIX_H


