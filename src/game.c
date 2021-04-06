#include "game.h"

void game() {
    map cur;
    int act;
    printf("Wprowadz liczbe w zakresie 1-3 dla wyboru tworzenia planszy do gry:\n1 - wprowadzenie reczne\n2 - wczytywanie z pliku\n3 - automatyczna generacja\n");

    scanf("%d", &act);

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
        char file[10];
        scanf("%s", &file);
        FILE *f = fopen(file, "r");
        fscanf(f,"%d %d", &cur.n, &cur.m);
        cur.arr = get_memory(cur.arr, cur.n, cur.m);

        // wypełnienie tablicy zerami
        for (int i = 0; i < cur.n; i++) {
            for (int j = 0; j < cur.m; j++) {
                (cur.arr[i][j]).live=0;
            }
        }

        for (int i = 0; i < cur.n; i++) {
            for (int j = 0; j < cur.m; j++) {
                int tmp = fscanf(f,"%d",&tmp);
                if (tmp != 0 && tmp != 1){
                    tmp = 0;
                }
                (cur.arr[i][j]).live=tmp;
            }
        }

        //z pliku
    }
    if (act == 3) {
        //generacja
        generate(&cur);
    }
    if (act < 1 && act > 3) {
        fprintf(stderr,"Liczba na nalezy do zakresu 1-3\n");
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

