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
    u8 numbers[8], i;
    u16 safe_count = 0;
    bool inc;

    while(fgets(line, buf_len, file)) {
        i = 0;
        for (char *p = strtok(line, " "); p != NULL; p = strtok(NULL, " ")) {
            if ((atoi_ret = atoi(p))) {
                numbers[i] = atoi_ret;
                if (i > 0) {
                    if (numbers[i-1] > numbers[i]) {
                        if (i == 1) {
                            inc = false;
                        } else if (i > 1 && inc) {
                            goto next;
                        }
                        if (numbers[i-1] - numbers[i] > 3)
                            goto next;
                    } else if (numbers[i] > numbers[i-1]) {
                        if (i == 1) {
                            inc = true;
                        } else if (i > 1 && !inc) {
                            goto next;
                        }
                        if (numbers[i] - numbers[i-1] > 3)
                            goto next;
                    } else {
                        goto next;
                    }
                }
                i++;
            }
        }
        if (i != 0)
            safe_count += 1;
next:
        do {} while(0);
    }
    printf("safe_count: %d\n", safe_count);// 631
}
