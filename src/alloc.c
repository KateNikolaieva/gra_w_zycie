#include "alloc.h"

elem** get_memory(elem **arr, int n, int m) {
    arr = (elem**)malloc(sizeof(elem*) * n);
    for (int i = 0; i < n; i++) {
        arr[i] = (elem*)malloc(sizeof(elem*) * m);
    }
    return arr;
}