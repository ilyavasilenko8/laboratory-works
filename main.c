#include <stdio.h>
#include "libs/data_structures/vector/vector.h"
#include "libs/data_structures/vector/vectorVoid.h"
#include "libs/data_structures/matrix/matrix.h"

int main(){
    //test2();
    // test1();
    //test2();
    matrix m = getMemMatrix(2,2);
    inputMatrix(&m);
    selectionSortColsMatrixByColCriteria(m, getSum);
    outputMatrix(m);

    return 0;
}