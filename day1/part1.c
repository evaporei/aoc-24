#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../primitives.h"

/* #define TEST */

#ifdef TEST
#define NUMBER_LEN 1
// n1 + \s + n2 + \n
//  1 +  3 +  1 +  1
#define LINE_SIZE 6

#define MAX_LINES 6

#define FILE_NAME "sample.txt"
#else
#define NUMBER_LEN 5
// n1 + \s + n2 + \n
//  5 +  3 +  5 +  1
#define LINE_SIZE 14

#define MAX_LINES 1000

#define FILE_NAME "input.txt"
#endif

#define INPUT_SIZE MAX_LINES * LINE_SIZE

int cmpU32(const void *a, const void *b) {
    return *(u32*) a - *(u32*) b;
}

int main(void) {
    // ------- READ INPUT FILE -------
    FILE *file = fopen(FILE_NAME, "r");

    char input[INPUT_SIZE];
    fread(input, 1, INPUT_SIZE, file);
    /* printf("contents: %.*s\n", INPUT_SIZE, input); */
    // ------- READ INPUT FILE -------

    // ------- PARSE INTEGERS LEFT & RIGHT -------
    u32 left[MAX_LINES];
    u32 right[MAX_LINES];

    usize input_idx = 0;
    u16 output_idx = 0;
    char tmp[NUMBER_LEN + 1];
    while (input_idx < INPUT_SIZE) {
        strncpy(tmp, &input[input_idx], NUMBER_LEN);
        tmp[NUMBER_LEN] = '\0';
        left[output_idx] = atoi(tmp);
        input_idx += NUMBER_LEN + 3; // 3 x \s

        strncpy(tmp, &input[input_idx], NUMBER_LEN);
        tmp[NUMBER_LEN] = '\0';
        right[output_idx] = atoi(tmp);
        input_idx += NUMBER_LEN + 1; // \n
        output_idx += 1;
    }
    /* printf("unsorted: \n"); */
    /* for (output_idx = 0; output_idx < MAX_LINES; output_idx++) { */
    /*     printf("%d   %d\n", left[output_idx], right[output_idx]); */
    /* } */
    // ------- PARSE INTEGERS LEFT & RIGHT -------

    // ------- SORT LEFT & RIGHT -------
    qsort(left, MAX_LINES, sizeof(u32), cmpU32);
    qsort(right, MAX_LINES, sizeof(u32), cmpU32);
    /* printf("\nsorted: \n"); */
    /* for (output_idx = 0; output_idx < MAX_LINES; output_idx++) { */
    /*     printf("%d   %d\n", left[output_idx], right[output_idx]); */
    /* } */
    // ------- SORT LEFT & RIGHT -------

    // ------- CALCULATE DISTANCE (diff) -------
    u64 dist = 0;
    for (u16 i = 0; i < MAX_LINES; i++) {
        dist += abs((i32) left[i] - (i32) right[i]);
    }
    printf("dist: %llu\n", dist); // 1646452
    // ------- CALCULATE DISTANCE (diff) -------
}
