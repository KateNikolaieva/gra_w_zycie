#include "game.h"

void game() {
    map cur;
    int act = 3;
    if (act == 1) {
        printf("wprowadz liczbe wierszy i kolumn: \n");
        scanf("%d%d", &cur.n, &cur.m);
        printf("wprowadz pozycje poczatkowa komorek(0 - martwa, 1 - zywa):\n");
        cur.arr = get_memory(cur.arr, cur.n, cur.m);
        for (int i = 0; i < cur.n; i++) {
            for (int j = 0; j < cur.m; j++) {
                scanf("%d", &cur.arr[i][j]);
            }
        }
    }
    if (act == 2) {
        //из файла
    }
    if (act == 3) {
        //генерация
        generate(&cur);
    }
    if (act < 1 && act > 3) {
        printf("huinu vveli");
        exit(1);
    }
    int height = cur.n, weight = cur.m;
    ge_GIF *gif = ge_new_gif(
            "ans.gif",  /* file name */
            weight, height,           /* canvas size */
            (uint8_t []) {  /* palette */
                    0x00, 0x00, 0x00, /* 0 -> black */
                    0xFF, 0xFF, 0xFF, /* 1 -> white */
                    0x00, 0xFF, 0x00, /* 2 -> green */
                    0x00, 0x00, 0xFF, /* 3 -> blue */
            },
            2,              /* palette depth == log2(# of colors) */
            0               /* infinite loop */
    );
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < weight; j++) {
            gif->frame[i * weight + j] = 1;
        }
    }
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < weight; j++) {
            if (cur.arr[i][j].live == 1) gif->frame[i * weight + j] = 0;
        }
    }
    int day = 0;
    ge_add_frame(gif, 10);
    while (day < 500) {
        int now = evolve(&cur);
        if (!now) break;
        day++;

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < weight; j++) {
                gif->frame[i * weight + j] = 1;
            }
        }
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < weight; j++) {
                if (cur.arr[i][j].live == 1) gif->frame[i * weight + j] = 0;
            }
        }
        ge_add_frame(gif, 10);
    }
    ge_close_gif(gif);
}

