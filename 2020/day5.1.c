
#include <stdio.h>
#include <assert.h>
#include <string.h>

int bd_decode(const char *in, char upper, char lower, int range) {
    int pos = 0;
    int bottom =0;
    int top = range - 1;

    while(top != bottom && range != 1) {
        range /= 2;
        if (in[pos] == upper) {
            bottom = bottom + range;
        } else {
            assert(in[pos] == lower);
            top = top - range;
        }
        pos++;
    }
    assert(top == bottom);

    return top;
}

int main(int argc, char *argv[]) {
    FILE *fd;
    char line[32];
    int max = 0;
#if 0
    const char testline[] = "FBFBBFFRLR";

    printf("Row: %d\n", bd_decode(testline, 'B', 'F', 128));
    printf("Column: %d\n", bd_decode(testline + 7, 'R', 'L', 8));

    return 0;
#endif
    fd = fopen("day5.input", "r");
    assert(fd != NULL);

    while(fgets(line, sizeof line, fd) != NULL) {
        if (strlen(line) != 11) {
            printf("Wrong input: %s\n", line);
            continue;
        }

        int row = bd_decode(line, 'B', 'F', 128);
        int seat = bd_decode(line + 7, 'R', 'L', 8);
        line[10] = 0;
        printf("%s: %d,%d ID:%d\n", line, row, seat, row * 8 + seat);
        if (row * 8 + seat > max) {
            max = row * 8 + seat;
        }
    }
    fclose(fd);

    printf("\nWhat is the highest seat ID on a boarding pass?\n%d\n", max);

    return 0;
}