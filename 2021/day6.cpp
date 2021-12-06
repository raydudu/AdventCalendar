#include <iostream>
#include <algorithm>
#include <cstring>
#include <numeric>

static constexpr char  fish[] = {
#include "day6.input"
};
static constexpr auto counts = 9;

int main(int argc, char *argv[]) {
    unsigned long fishcount[counts] = {0, };
    unsigned long sum80 = 0;
    unsigned long sum = 0;

    for (auto &f: fish) {
        fishcount[f]++;
    }

    for(int d = 0; d < 256; d++) {
        if (d == 80) {
            sum80 = std::accumulate(fishcount, fishcount + counts, sum80);
        }

        unsigned long newcount[counts] = {0, };
        newcount[8] = fishcount[0];
        newcount[6] = fishcount[0];
        for (int i = 1; i <= 8; i++) {
            newcount[i - 1] += fishcount[i];
        }
        std::memcpy(fishcount, newcount, sizeof(fishcount));
    }

    std::cout << "P1 fishcount: " << sum80 << std::endl;
    sum = std::accumulate(fishcount, fishcount + counts, sum);
    std::cout << "P2 fishcount: " << sum << std::endl;

    return 0;
}