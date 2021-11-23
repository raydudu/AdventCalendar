#include <stdio.h>
#include <assert.h>
#include <string.h>

static const char *fields[] = {
        "byr:",
        "iyr:",
        "eyr:",
        "hgt:",
        "hcl:",
        "ecl:",
        "pid:",
//        "cid:"
};
#define fieldsnr (sizeof(fields) / sizeof(fields[0]))


static int fpresent[fieldsnr];

static unsigned good = 0;

static void checkent() {
    int nogood = 0;
    printf("    |");
    for (int i = 0; i < fieldsnr; i++) {
        if (fpresent[i] == -1) {
            printf(" -%s", fields[i]);
            nogood = 1;
        } else if (fpresent[i] == 0) {
            printf(" ~%s", fields[i]);
            nogood = 1;
        }
    }
    if (!nogood) {
        good++;
    }
    memset(fpresent, -1, sizeof(fpresent));
    printf("\n");
}

int main(int argc, char *argv[]) {
    char line[1024];
    FILE *fd;
    char *pch;

    fd = fopen("day4.input", "r");
    assert(fd != NULL);

    while (fgets(line, sizeof(line), fd) != NULL) {
        line[strlen(line) - 1] = 0;

        if (line[0] == 0) {
            checkent();
            continue;
        }

        pch = strtok(line, " ");
        while (pch != NULL) {
            for (int i = 0; i < fieldsnr; i++) {
                if (strncmp(pch, fields[i], 4) == 0) {
                    fpresent[i] = 1;
                    if (fpresent[i]) {
                        printf("*");
                    }
                    break;
                }
            }
            printf("%s ", pch);
            pch = strtok(NULL, " ");
        }

    }

    fclose(fd);

    checkent();
    printf("\n\nGood passports: %d\n", good);
    return 0;
}