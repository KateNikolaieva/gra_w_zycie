#include "generator.h"

void generate(map* cur) {
    int x = 10 + rand() % 50;  //от 10 + 49
    cur->n = x;
    x = 10 + rand() % 50;
    cur->m = x;
    cur->arr = get_memory(cur->arr, cur->n, cur->m);
    for (int i = 0 ; i < cur->n; i++) {
        for (int j = 0; j < cur->m; j++) {
            x = rand();
            x %= 4; //шанс дропа 1(живой мобилы) = 100% / div(в данном случае 4) = 25% для изменения шанса меняйте 4 на любое другое число
            cur->arr[i][j].live = x == 0 ? 1 : 0;
        }
    }
}