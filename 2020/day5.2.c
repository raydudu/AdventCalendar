
#include <stdio.h>
#include <assert.h>
#include <string.h>

static int bd_decode(const char *in, char upper, char lower, int range) {
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

static int prevseatid(int (*seatmap)[8], int r, int c) {
    if (c == 0) {
        if (r > 0) {
            r--;
            c = 7;
        } // else  corner case r/c == 0 no previous seat
    } else {
        c--;
    }

    return seatmap[r][c];
}

static int nextseatid(int (*seatmap)[8], int r, int c) {
    if (c == 7) {
        if (r < 127) {
            r++;
            c = 0;
        } // else corner case r/c at max no next seat
    } else {
        c++;
    }

    return seatmap[r][c];
}


int main(int argc, char *argv[]) {
    FILE *fd;
    char line[32];
    int max = 0;
    int seatmap[128][8];

    memset(seatmap, 0, sizeof(seatmap));

    fd = fopen("day5.input", "r");
    assert(fd != NULL);

    while(fgets(line, sizeof line, fd) != NULL) {
        if (strlen(line) != 11) {
            printf("Wrong input: %s\n", line);
            continue;
        }

        int row = bd_decode(line, 'B', 'F', 128);
        int col = bd_decode(line + 7, 'R', 'L', 8);
        line[10] = 0;
        assert(seatmap[row][col] == 0);
        seatmap[row][col] = row * 8 + col;
        printf("%s: %d,%d ID:%d\n", line, row, col, seatmap[row][col]);
        if (seatmap[row][col] > max) {
            max = seatmap[row][col];
        }
    }
    fclose(fd);

    printf("\nWhat is the highest seat ID on a boarding pass?\n%d\n", max);
    for (int i = 0; i < 128; i++) {
        for(int j = 0; j < 8; j++) {
            if (seatmap[i][j] == 0) {
                printf("O");
            } else {
                printf("X");
            }
        }
        printf("\n");
    }

    for (int i = 0; i < 128; i++) {
        for(int j = 0; j < 8; j++) {
            if (seatmap[i][j] == 0) {
                if (prevseatid(seatmap, i, j) != 0 && nextseatid(seatmap, i, j) != 0) {
                    printf("Free sit at %d, %d ID:%d\n", i, j, i * 8 +j);
                }
            }
        }
    }

    return 0;
}