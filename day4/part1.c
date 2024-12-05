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

bool check_bounds(Pos m, Pos a, Pos s) {
    return m.r >= 0 && m.r < SIDE && m.c >= 0 && m.c < SIDE &&
        a.r >= 0 && a.r < SIDE && a.c >= 0 && a.c < SIDE &&
        s.r >= 0 && s.r < SIDE && s.c >= 0 && s.c < SIDE;
}

bool is_mas(char grid[SIDE][SIDE], Pos m, Pos a, Pos s) {
    return grid[m.r][m.c] == 'M' &&
            grid[a.r][a.c] == 'A' &&
            grid[s.r][s.c] == 'S';
}

u16 search(char grid[SIDE][SIDE], i16 r, i16 c) {
    Pos directions[] = {
        {0, 1}, // right
        {0, -1}, // left
        {-1, 0}, // up
        {1, 0}, // down

        {-1, 1}, // up right
        {-1, -1}, // up left
        {1, 1}, // down right
        {1, -1}, // down left
    };
    Pos /* x */ m, a, s;
    u16 matches = 0;

    for (u8 i = 0; i < sizeof(directions) / sizeof(directions[0]); i++) {
        m = (Pos){r + directions[i].r, c + directions[i].c};
        a = (Pos){r + directions[i].r * 2, c + directions[i].c * 2};
        s = (Pos){r + directions[i].r * 3, c + directions[i].c * 3};
        if (check_bounds(m, a, s)) {
            matches += is_mas(grid, m, a, s);
        }
    }

    return matches;
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
            if (input[r][c] == 'X')
                count += search(input, r, c);

    printf("xmas count: %d\n", count); // 2536
}
