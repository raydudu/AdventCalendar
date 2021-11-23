#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>

static bool byr_validate(const char *s) {
    long val;
    char *endptr = NULL;

    errno = 0;    /* To distinguish success/failure after call */
    val = strtol(s, &endptr, 10);

    /* Check for various possible errors */
    if ((errno == ERANGE && (val == LONG_MAX || val == LONG_MIN)) || (errno != 0 && val == 0)) {
        return false;
    }

    if (endptr == s) {
        return false;
    }
    if (val >= 1920 && val <= 2002) {
        return true;
    }

    return false;
}
static bool iyr_validate(const char *s) {
    long val;
    char *endptr = NULL;

    errno = 0;    /* To distinguish success/failure after call */
    val = strtol(s, &endptr, 10);

    /* Check for various possible errors */
    if ((errno == ERANGE && (val == LONG_MAX || val == LONG_MIN)) || (errno != 0 && val == 0)) {
        return false;
    }

    if (endptr == s) {
        return false;
    }
    if (val >= 2010 && val <= 2020) {
        return true;
    }

    return false;
}
static bool eyr_validate(const char *s) {
    long val;
    char *endptr = NULL;

    errno = 0;    /* To distinguish success/failure after call */
    val = strtol(s, &endptr, 10);

    /* Check for various possible errors */
    if ((errno == ERANGE && (val == LONG_MAX || val == LONG_MIN)) || (errno != 0 && val == 0)) {
        return false;
    }

    if (endptr == s) {
        return false;
    }
    if (val >= 2020 && val <= 2030) {
        return true;
    }

    return false;
}
static bool hgt_validate(const char *s) {
    unsigned hgt = 0;
    char *endptr = NULL;

    errno = 0;    /* To distinguish success/failure after call */
    hgt = strtol(s, &endptr, 10);

    /* Check for various possible errors */
    if ((errno == ERANGE && (hgt == LONG_MAX || hgt == LONG_MIN)) || (errno != 0 && hgt == 0)) {
        return false;
    }

    if (endptr == s) {
        return false;
    }
    if (strcmp(endptr, "cm") == 0) {
        if (hgt >= 150 && hgt <= 193) {
            return true;
        }
    } else if (strcmp(endptr, "in") == 0) {
        if (hgt >= 59 && hgt <= 76) {
            return true;
        }
    }
    return false;
}
static bool hcl_validate(const char *s) {
    if (strlen(s) != 7) {
        return false;
    }
    if (s[0] != '#') {
        return false;
    }
    for (int i = 1; i < 7; i++) {
        if (!(isdigit(s[i]) || (s[i] >= 'a' && s[i] <= 'f'))) {
            return false;
        }

    }
    return true;
}

static bool ecl_validate(const char *s) {
    const char *gecl[] = { "amb", "blu", "brn", "gry", "grn", "hzl", "oth", NULL};
    int i = 0;
    while(gecl[i] != NULL) {
        if (strcmp(s, gecl[i]) == 0 )
            return true;
        i++;
    }
    return false;
}

static bool pid_validate(const char *s) {
    for (int i = 0; i < 9; i++) {
        if (s[i] == 0 || !isdigit(s[i])) {
            return false;
        }
    }

    if (s[9] != 0) {
        return false;
    }
    return true;
}


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

static bool (*fvalidate[])(const char *s) = {
    byr_validate,
    iyr_validate,
    eyr_validate,
    hgt_validate,
    hcl_validate,
    ecl_validate,
    pid_validate,
};

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

    memset(fpresent, -1, sizeof(fpresent));

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
                    fpresent[i] = fvalidate[i](pch + 4);
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

    checkent();

    fclose(fd);

    printf("\n\nGood passports: %d\n", good);
    return 0;
}