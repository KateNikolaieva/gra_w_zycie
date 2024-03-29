#include "generator.h"

void generate(map *cur) {
    int x = 10 + rand() % 50;  // field of size [10; 49]
    cur->n = x;
    x = 10 + rand() % 50; // field of size [10; 49]
    cur->m = x;
    cur->arr = get_memory(cur->arr, cur->n, cur->m);
    for (int i = 0; i < cur->n; i++) {
        for (int j = 0; j < cur->m; j++) {
            x = rand();
            x %= 4; // the chance of a living cell appearing - 25%
            cur->arr[i][j].live = x == 0 ? 1 : 0;
        }
    }
}