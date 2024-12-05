#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

#include "../primitives.h"

/* #define TEST */

#ifdef TEST
#define MAX_LINES 6
#define FILE_NAME "sample.txt"
#else
#define MAX_LINES 1000
#define FILE_NAME "input.txt"
#endif

// 8 numbers (two digits) + spaces & \n
#define MAX_LINE_SIZE 24

int main(void) {
    FILE *file = fopen(FILE_NAME, "r");
    u32 buf_len = MAX_LINE_SIZE;
    char line[buf_len];
    int atoi_ret;
    u8 numbers[8], i, len;
    u16 safe_count = 0;
    bool inc;

    while(fgets(line, buf_len, file)) {
        len = 0;
        for (char *p = strtok(line, " "); p != NULL; p = strtok(NULL, " "))
            if ((atoi_ret = atoi(p)))
                numbers[len++] = atoi_ret;

        if (len == 0)
            goto next;

        if (numbers[0] > numbers[1])
            inc = false;
        else if (numbers[1] > numbers[0])
            inc = true;
        else
            goto next;

        for (i = 1; i < len; i++) {
            if (numbers[i-1] > numbers[i]) {
                if (inc || numbers[i-1] - numbers[i] > 3)
                    goto next;
            } else if (numbers[i] > numbers[i-1]) {
                if (!inc || numbers[i] - numbers[i-1] > 3)
                    goto next;
            } else
                goto next;
        }

        safe_count += 1;

next:
        do {} while(0);
    }
    printf("safe_count: %d\n", safe_count);// 631
}
