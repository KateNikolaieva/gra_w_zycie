#ifndef PW_GAME_OF_LIFE_STRUCT_H
#define PW_GAME_OF_LIFE_STRUCT_H

typedef struct element{
    int live;
} elem;

typedef struct square{
    int n;
    int m;
    elem **arr;
} map;

#endif