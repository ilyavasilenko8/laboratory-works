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
    free(m->values);
}

void freeMemMatrices(matrix *ms, int nMatrices) {
    for (int i = 0; i < nMatrices; i++) {
        freeMemMatrix(&ms[i]);
    }
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

position getMinValuePos(matrix m){
    position res = {0, 0};
    int min_value = m.values[0][0];

    for(int i = 0; i < m.nRows; i++){
        for(int j = 0; j < m.nCols; j++){
            if(m.values[i][j] < min_value){
                min_value = m.values[i][j];
                res.rowIndex = i;
                res.colIndex = j;
            }
        }
    }
    return res;
}

position getMaxValuePos(matrix m){
    position res = {0, 0};
    int max_value = m.values[0][0];

    for(int i = 0; i < m.nRows; i++){
        for(int j = 0; j < m.nCols; j++){
            if(m.values[i][j] > max_value){
                max_value = m.values[i][j];
                res.rowIndex = i;
                res.colIndex = j;
            }
        }
    }
    return res;
}