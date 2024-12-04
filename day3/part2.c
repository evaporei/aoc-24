#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

#include "../primitives.h"

/* #define TEST */

#ifdef TEST
#define FILE_NAME "sample2.txt"
#else
#define FILE_NAME "input.txt"
#endif

char* read_text_file(const char *path) {
    FILE *file = fopen(path, "r");
    if (!file) {
        fprintf(stderr, "failed to open file: %s\n", path);
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    char *contents = (char*) malloc(file_size + 1);

    size_t amount_read = fread(contents, 1, file_size, file);
    if (file_size != amount_read) {
        fprintf(stderr, "too lazy to do more read syscalls %s\n", path);
        return NULL;
    }
    contents[file_size] = '\0';

    fclose(file);

    return (char*) contents;
}

int main(void) {
    char *input = read_text_file(FILE_NAME);
    char *c = input, *start;
    char n[4];
    u32 n1, n2;
    u64 result = 0;
    bool enable = true;

    while (*c != '\0') {
        start = c;
        if (strncmp(start, "don't()", 7) == 0) {
            enable = false;
            c += 7;
            continue;
        }

        if (enable) {
            start = c;
            // starts with 'm'
            if (*c != 'm')
                goto next;

            // consume all a-z
            while (isalpha(*c))
                c++;

            // input[start:c] == "mul" ?
            if (strncmp(start, "mul", 3) != 0)
                goto next;

            // consume left paren
            if (*c != '(')
                goto next;
            c++;

            if (!isdigit(*c))
                goto next;

            start = c;
            // consume first number
            while (isdigit(*c))
                c++;

            strncpy(n, start, c - start);
            n[c - start] = '\0';
            n1 = atoi(n);

            // consume ','
            if (*c != ',')
                goto next;
            c++;

            if (!isdigit(*c))
                goto next;

            start = c;
            // consume second number
            while (isdigit(*c))
                c++;

            strncpy(n, start, c - start);
            n[c - start] = '\0';
            n2 = atoi(n);

            // consume right paren
            if (*c != ')')
                goto next;

            // successfully parsed
            result += n1 * n2;
        } else {
            start = c;
            if (strncmp(start, "do()", 4) == 0) {
                enable = true;
                c += 4;
                continue;
            }
        }

next:
        c++;
    }

    printf("%llu\n", result); // 75920122
}
