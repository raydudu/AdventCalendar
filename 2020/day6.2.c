
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>

int main(int argc, char *argv[]) {
    FILE *fd;
    char line[81];
    int answers[26];
    int total_ans = 0;
    int people_ingroup = 0;
    bool done = false;

    fd = fopen("day6.input", "r");
    assert(fd != NULL);

    memset(answers, 0, sizeof(answers));

    do {
        if (fgets(line, sizeof line, fd) == NULL) {
            done = true;
        }

        if (line[0] == '\n' || done) {
            int ingroupcnt = 0;
            for (int i = 0; i < sizeof answers/sizeof answers[0]; i++) {
                if (answers[i] == people_ingroup) {
                    ingroupcnt++;
                }
                answers[i] = 0;
            }
            printf("InGroup answers: %d\n\n", ingroupcnt);
            total_ans += ingroupcnt;
            people_ingroup = 0;
            continue;
        }

        printf("%s", line);

        for(int pos = 0; line[pos] != 0; pos++) {
            assert(line[pos] - 'a' < 26);
            answers[line[pos] - 'a'] += 1;
        }
        people_ingroup++;
    } while (!done);

    fclose(fd);
    printf("\nAnswers sum: %d\n", total_ans);
    return 0;
}