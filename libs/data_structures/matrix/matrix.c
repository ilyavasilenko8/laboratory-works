#include <malloc.h>
#include <stdio.h>
#include <assert.h>
#include <memory.h>
#include "matrix.h"

matrix getMemMatrix(int nRows, int nCols) {
    int **values = (int **) malloc(sizeof(int *) * nRows);
    for (int i = 0; i < nRows; i++) {
        values[i] = (int *) malloc(sizeof(int) * nCols);
    }
    return (matrix) {values, nRows, nCols};
}

matrix *getMemArrayOfMatrices(int nMatrices, int nRows, int nCols) {
    matrix *ms = (matrix *) malloc(sizeof(matrix) * nMatrices);
    for (int i = 0; i < nMatrices; i++) {
        ms[i] = getMemMatrix(nRows, nCols);
    }
    return ms;
}

void freeMemMatrix(matrix *m) {
    for (int i = 0; i < m->nRows; i++) {
        free(m->values[i]);
    }
    int nRows = 0;
    int nCols = 0;
    free(m->values);
}

void freeMemMatrices(matrix *ms, int nMatrices) {
    for (int i = 0; i < nMatrices; i++) {
        freeMemMatrix(&ms[i]);
    }
    int nRows = 0;
    int nCols = 0;
}

void inputMatrix(matrix *m) {
    for (int i = 0; i < m->nRows; i++) {
        for (int j = 0; j < m->nCols; j++) {
            scanf("%d", &m->values[i][j]);
        }
    }
}

void inputMatrices(matrix *ms, int nMatrices) {
    for (int i = 0; i < nMatrices; i++) {
        inputMatrix(&ms[i]);
    }
}

void outputMatrix(matrix m) {
    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++) {
            printf("%d ", m.values[i][j]);
        }
        printf("\n");
    }
}

void outputMatrices(matrix *ms, int nMatrices) {
    for (int i = 0; i < nMatrices; i++) {
        outputMatrix(ms[i]);
    }
}

void swapRows(matrix *m, int i1, int i2) {
    assert(i1 < m->nRows && i2 < m->nRows);

    int *temp = m->values[i1];

    memcpy(&m->values[i1], &m->values[i2], sizeof(int *));
    memcpy(&m->values[i2], &temp, sizeof(int *));
}

void swapColumns(matrix *m, int j1, int j2) {
    assert(j1 < m->nCols && j2 < m->nCols);
    for (int i = 0; i < m->nRows; i++) {
        int temp = m->values[i][j1];

        memcpy(&m->values[i][j1], &m->values[i][j2], sizeof(int));
        memcpy(&m->values[i][j2], &temp, sizeof(int));
    }
}

void insertionSortRowsMatrixByRowCriteria(matrix m, int (*criteria)(int *, int)) {
    int *values = malloc(sizeof(int) * m.nRows);

    for (int i = 0; i < m.nRows; i++) {
        values[i] = criteria(m.values[i], m.nCols);
    }

    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < i; j++) {
            if (values[i] < values[j]) {
                int t = values[i];
                values[i] = values[j];
                values[j] = t;
                swapRows(&m, i, j);
            }
        }
    }
    free(values);
}

int getSum(int *a, int n) {
    int res = 0;
    for (int i = 0; i < res; i++) {
        res += a[i];
    }
    return res;
}

void selectionSortColsMatrixByColCriteria(matrix m, int (*criteria)(int *, int)) {
    int *values = malloc(sizeof(int) * m.nCols);

    for (int i = 0; i < m.nCols; i++) {
        int *column = malloc(sizeof(int) * m.nRows);

        for (int j = 0; j < m.nRows; j++) {
            column[j] = m.values[j][i];
        }

        values[i] = criteria(column, m.nRows);
    }

    for (int i = 0; i < m.nCols; i++) {
        for (int j = 0; j < i; j++) {
            if (values[i] < values[j]) {
                int t = values[i];
                values[i] = values[j];
                values[j] = t;
                swapColumns(&m, i, j);
            }
        }
    }
}

bool isSquareMatrix(matrix *m) {
    return m->nRows == m->nCols;
}

bool areTwoMatricesEqual(matrix *m1, matrix *m2) {
    if (m1->nCols != m2->nCols || m1->nRows != m2->nRows) {
        return false;
    }
    for (int i = 0; i < m1->nRows; i++) {
        if (memcmp(m1->values[i], m2->values[i], sizeof(int) * m1->nCols) != 0) {
            return false;
        }
    }
    return true;
}

bool isEMatrix(matrix *m) {
    if (!isSquareMatrix(m)) {
        return false;
    }

    for (int i = 0; i < m->nRows; i++) {
        for (int j = 0; j < m->nCols; j++) {
            if (i == j && m->values[i][j] != 1) {
                return false;
            } else if (i != j && m->values[i][j] != 0) {
                return false;
            }
        }
    }
    return true;
}

bool isSymmetricMatrix(matrix *m) {
    for (int i = 0; i < m->nRows; i++) {
        for (int j = 0; j < m->nCols; j++) {
            if (m->values[i][j] != m->values[j][i]) {
                return false;
            }
        }
    }
    return true;
}

void transposeSquareMatrix(matrix *m) {
    assert(isSquareMatrix(m));

    for (int i = 0; i < m->nRows; i++) {
        for (int j = i + 1; j < m->nCols; j++) {
            int t = m->values[i][j];
            m->values[i][j] = m->values[j][i];
            m->values[j][i] = t;
        }
    }
}

void transposeMatrix(matrix *m) {
    matrix res = getMemMatrix(m->nCols, m->nRows);

    for (int i = 0; i < m->nCols; i++) {
        for (int j = 0; j < m->nRows; j++) {
            res.values[i][j] = m->values[j][i];
        }
    }
    memcpy(m, &res, sizeof(matrix));
}

position getMinValuePos(matrix m) {
    position res = {0, 0};
    int min_value = m.values[0][0];

    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++) {
            if (m.values[i][j] < min_value) {
                min_value = m.values[i][j];
                res.rowIndex = i;
                res.colIndex = j;
            }
        }
    }
    return res;
}

position getMaxValuePos(matrix m) {
    position res = {0, 0};
    int max_value = m.values[0][0];

    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++) {
            if (m.values[i][j] > max_value) {
                max_value = m.values[i][j];
                res.rowIndex = i;
                res.colIndex = j;
            }
        }
    }
    return res;
}

matrix createMatrixFromArray(const int *a, size_t nRows, size_t nCols) {
    matrix m = getMemMatrix(nRows, nCols);
    int k = 0;

    for (int i = 0; i < nRows; i++) {
        for (int j = 0; j < nCols; j++) {
            m.values[i][j] = a[k++];
        }
    }
    return m;
}

matrix *createArrayOfMatrixFromArray(const int *values, size_t nMatrices, size_t nRows, size_t nCols) {
    matrix *ms = getMemArrayOfMatrices(nMatrices, nRows, nCols);
    int l = 0;
    for (int k = 0; k < nMatrices; k++) {
        for (int i = 0; i < nRows; i++) {
            for (int j = 0; j < nCols; j++) {
                ms[k].values[i][j] = values[l++];
            }
        }
    }
    return ms;
}

void test_swap_rows() {
    matrix m = createMatrixFromArray((int[]) {1, 2, 3,
                                              4, 5, 6,
                                              7, 8, 9}, 3, 3);
    matrix result = createMatrixFromArray((int[]) {4, 5, 6,
                                                   1, 2, 3,
                                                   7, 8, 9}, 3, 3);

    swapRows(&m, 0, 1);

    assert(areTwoMatricesEqual(&m, &result));

    freeMemMatrix(&m);
    freeMemMatrix(&result);
}

void test_swap_columns() {
    matrix m = createMatrixFromArray((int[]) {1, 2, 3,
                                              4, 5, 6,
                                              7, 8, 9}, 3, 3);
    matrix result = createMatrixFromArray((int[]) {2, 1, 3,
                                                   5, 4, 6,
                                                   8, 7, 9}, 3, 3);

    swapColumns(&m, 0, 1);

    assert(areTwoMatricesEqual(&m, &result));

    freeMemMatrix(&m);
    freeMemMatrix(&result);
}

void test_is_square_matrix_true() {
    matrix m = createMatrixFromArray((int[]) {1, 2, 3,
                                              4, 5, 6,
                                              7, 8, 9}, 3, 3);

    assert(isSquareMatrix(&m));

    freeMemMatrix(&m);
}

void test_is_square_matrix_false() {
    matrix m = createMatrixFromArray((int[]) {1, 2,
                                              4, 5,
                                              7, 8}, 3, 2);

    assert(!isSquareMatrix(&m));

    freeMemMatrix(&m);
}

void test_is_e_matrix_true() {
    matrix m = createMatrixFromArray((int[]) {1, 0, 0,
                                              0, 1, 0,
                                              0, 0, 1}, 3, 3);

    assert(isEMatrix(&m));

    freeMemMatrix(&m);
}

void test_is_e_matrix_false() {
    matrix m = createMatrixFromArray((int[]) {2, 4, 0,
                                              0, 3, 5,
                                              8, 1, 1}, 3, 3);

    assert(!isEMatrix(&m));

    freeMemMatrix(&m);
}

void test_is_symmetric_matrix_true() {
    matrix m = createMatrixFromArray((int[]) {1, 2, 3,
                                              2, 5, 6,
                                              3, 6, 9}, 3, 3);

    assert(isSymmetricMatrix(&m));

    freeMemMatrix(&m);
}

void test_is_symmetric_matrix_false() {
    matrix m = createMatrixFromArray((int[]) {1, 2, 3,
                                              4, 5, 6,
                                              7, 8, 9}, 3, 3);

    assert(!isSymmetricMatrix(&m));

    freeMemMatrix(&m);
}

void test_transpose_square_matrix() {
    matrix m = createMatrixFromArray((int[]) {1, 2, 3,
                                              4, 5, 6,
                                              7, 8, 9}, 3, 3);
    matrix result = createMatrixFromArray((int[]) {1, 4, 7,
                                                   2, 5, 8,
                                                   3, 6, 9}, 3, 3);

    transposeSquareMatrix(&m);

    assert(areTwoMatricesEqual(&m, &result));

    freeMemMatrix(&m);
    freeMemMatrix(&result);
}

void test_transpose_matrix() {
    matrix m = createMatrixFromArray((int[]) {1, 2,
                                              3, 4,
                                              5, 6}, 3, 2);
    matrix result = createMatrixFromArray((int[]) {1, 3, 5,
                                                   2, 4, 6}, 2, 3);

    transposeMatrix(&m);

    assert(areTwoMatricesEqual(&m, &result));

    freeMemMatrix(&m);
    freeMemMatrix(&result);
}

void test_get_min_value_pos() {
    matrix m = createMatrixFromArray((int[]) {2, 4, 3,
                                              5, 1, 6,
                                              7, 8, 9}, 3, 3);
    position result = {1, 1};

    position pos = getMinValuePos(m);

    assert(pos.colIndex == result.colIndex);
    assert(pos.rowIndex == result.rowIndex);

    freeMemMatrix(&m);
}

void test_get_max_value_pos() {
    matrix m = createMatrixFromArray((int[]) {2, 4, 3,
                                              5, 9, 6,
                                              7, 8, 1}, 3, 3);
    position result = {1, 1};

    position pos = getMaxValuePos(m);

    assert(pos.colIndex == result.colIndex);
    assert(pos.rowIndex == result.rowIndex);

    freeMemMatrix(&m);
}

void test_matrix() {
    test_swap_rows();
    test_swap_columns();
    test_is_square_matrix_true();
    test_is_square_matrix_false();
    test_is_e_matrix_true();
    test_is_e_matrix_false();
    test_is_symmetric_matrix_true();
    test_is_symmetric_matrix_false();
    test_transpose_square_matrix();
    test_transpose_matrix();
    test_get_min_value_pos();
    test_get_max_value_pos();
}


void swap_rows_with_min_and_max_elemnts(matrix *m) {
    position max_pos = getMaxValuePos(*m);
    position min_pos = getMinValuePos(*m);

    if (max_pos.rowIndex != min_pos.rowIndex) {
        swapRows(m, max_pos.rowIndex, min_pos.rowIndex);
    }
}

void test_swap_rows_with_min_and_max_element_1() {
    matrix m = createMatrixFromArray((int[]) {9, 4, 3,
                                              5, 2, 6,
                                              7, 8, 1}, 3, 3);

    matrix res = createMatrixFromArray((int[]) {7, 8, 1,
                                                5, 2, 6,
                                                9, 4, 3}, 3, 3);
    swap_rows_with_min_and_max_elemnts(&m);
    assert(areTwoMatricesEqual(&m, &res));

    freeMemMatrix(&m);
    freeMemMatrix(&res);
}

void test_swap_rows_with_min_and_max_elements_2() {
    matrix m = createMatrixFromArray((int[]) {7, 4, 3,
                                              5, 2, 6,
                                              9, 8, 1}, 3, 3);
    matrix res = createMatrixFromArray((int[]) {7, 4, 3,
                                                5, 2, 6,
                                                9, 8, 1}, 3, 3);

    swap_rows_with_min_and_max_elemnts(&m);

    assert(areTwoMatricesEqual(&m, &res));

    freeMemMatrix(&m);
    freeMemMatrix(&res);
}

void test_swap_rows_with_min_and_max_element() {
    test_swap_rows_with_min_and_max_element_1();
    test_swap_rows_with_min_and_max_element_2();
}


int getMax(int *a, int n){
    int res = a[0];

    for(int i = 1; i < n; i++){
        if(a[i] > res){
            res = a[i];
        }
    }
    return res;
}

void sortRowsByMinElement(matrix *m){
    int cols = m->nCols;

    for(int i = 1; i < cols - 1; i++){
        int max = getMax(m->values[i], cols);
        int row_idx = i;

        for (int j = 1; j < cols; j++){
            int max_of_row = getMax(m->values[i], cols);

            if(max_of_row < max){
                max = max_of_row;
                row_idx = j;
            }
        }
        if(row_idx != i){
            swapRows(m,i,row_idx);
        }
    }
}

void test_sortRowsByMinElement_1() {
    matrix m = createMatrixFromArray((int[]) {7, 1, 2,
                                              1, 8, 1,
                                              3, 2, 3},3, 3);
    matrix res = createMatrixFromArray((int[]) {3, 2, 3,
                                                   7, 1, 2,
                                                   1, 8, 1},3, 3);

    sortRowsByMinElement(&m);

    assert(areTwoMatricesEqual(&m, &res));

    freeMemMatrix(&m);
    freeMemMatrix(&res);
}

void test_sortRowsByMinElement_2() {
    matrix m = createMatrixFromArray((int[]) {},0, 0);

    sortRowsByMinElement(&m);

    freeMemMatrix(&m);
}

void test_sortRowsByMinElement(){
    test_sortRowsByMinElement_1();
    test_sortRowsByMinElement_2();
}
