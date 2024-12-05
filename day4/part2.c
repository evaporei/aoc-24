#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

#include "../primitives.h"

/* #define TEST */

#ifdef TEST
#define SIDE 10
#define FILE_NAME "sample.txt"
#else
#define SIDE 140
#define FILE_NAME "input.txt"
#endif

#define FILE_SIZE (SIDE * (SIDE + 1) + 1)

typedef struct Pos {
    i16 r, c;
} Pos;

bool check_bounds(Pos m, Pos s) {
    return m.r >= 0 && m.r < SIDE && m.c >= 0 && m.c < SIDE &&
        s.r >= 0 && s.r < SIDE && s.c >= 0 && s.c < SIDE;
}

bool is_ms(char grid[SIDE][SIDE], Pos m, Pos s) {
    return grid[m.r][m.c] == 'M' &&
            grid[s.r][s.c] == 'S';
}

bool search(char grid[SIDE][SIDE], i16 r, i16 c) {
    Pos up_right = {-1, 1},
        up_left = {-1, -1},
        down_right = {1, 1},
        down_left = {1, -1};
    Pos m1, s1, m2, s2;
    bool found = false;

    // M..
    // .A.
    // ..S
    m1 = (Pos){r + up_left.r, c + up_left.c};
    s1 = (Pos){r + down_right.r, c + down_right.c};
    // ..M
    // .A.
    // S..
    m2 = (Pos){r + up_right.r, c + up_right.c};
    s2 = (Pos){r + down_left.r, c + down_left.c};
    if (check_bounds(m1, s1) && check_bounds(m2, s2)) {
        found |= is_ms(grid, m1, s1) && is_ms(grid, m2, s2);
    }

    // S..
    // .A.
    // ..M
    m1 = (Pos){r + down_right.r, c + down_right.c};
    s1 = (Pos){r + up_left.r, c + up_left.c};
    // ..S
    // .A.
    // M..
    m2 = (Pos){r + down_left.r, c + down_left.c};
    s2 = (Pos){r + up_right.r, c + up_right.c};
    if (check_bounds(m1, s1) && check_bounds(m2, s2)) {
        found |= is_ms(grid, m1, s1) && is_ms(grid, m2, s2);
    }

    // M..
    // .A.
    // ..S
    m1 = (Pos){r + up_left.r, c + up_left.c};
    s1 = (Pos){r + down_right.r, c + down_right.c};
    // ..S
    // .A.
    // M..
    m2 = (Pos){r + down_left.r, c + down_left.c};
    s2 = (Pos){r + up_right.r, c + up_right.c};
    if (check_bounds(m1, s1) && check_bounds(m2, s2)) {
        found |= is_ms(grid, m1, s1) && is_ms(grid, m2, s2);
    }

    // S..
    // .A.
    // ..M
    m1 = (Pos){r + down_right.r, c + down_right.c};
    s1 = (Pos){r + up_left.r, c + up_left.c};
    // ..M
    // .A.
    // S..
    m2 = (Pos){r + up_right.r, c + up_right.c};
    s2 = (Pos){r + down_left.r, c + down_left.c};
    if (check_bounds(m1, s1) && check_bounds(m2, s2)) {
        found |= is_ms(grid, m1, s1) && is_ms(grid, m2, s2);
    }

    return found;
}

int main(void) {
    FILE *file = fopen(FILE_NAME, "r");
    char buffer[FILE_SIZE];
    fread(buffer, 1, FILE_SIZE, file);

    char input[SIDE][SIDE];
    for (u16 i = 0; i < SIDE; i++) {
        // removing \n just for the lolz
        memcpy(input[i], buffer + i * (SIDE + 1), SIDE);
    }
    /* for (u16 i = 0; i < SIDE; i++) { */
    /*     printf("%.*s\n", SIDE, input[i]); */
    /* } */

    u16 count = 0;
    for (i16 r = 0; r < SIDE; r++)
        for (i16 c = 0; c < SIDE; c++)
            if (input[r][c] == 'A' && search(input, r, c))
                count += 1;

    printf("x-mas count: %d\n", count); // 1875
}
