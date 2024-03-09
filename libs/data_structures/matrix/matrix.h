#ifndef GIT_PROJECT_MATRIX_H
#define GIT_PROJECT_MATRIX_H

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


#endif //GIT_PROJECT_MATRIX_H
