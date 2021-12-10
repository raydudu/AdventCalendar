#include <iostream>
#include <cstring>
#include <numeric>

static int  subs[] = {
#include "day07.input"
};

constexpr int subsn() {
    return sizeof subs / sizeof subs[0];
}


int main(int argc, char *argv[]) {

    std::sort(subs, subs + subsn());

    assert(subsn() % 2 == 0);
    int median = (subs[(subsn() - 1) / 2] + subs[subsn() / 2]) / 2;
    int fuel = 0;

    std::for_each(subs, subs + subsn(), [&fuel, &median](auto s) {
        fuel += std::abs(s - median);
    });

    std::cout << "P1 fuel: " << fuel << std::endl;

    int mean = std::accumulate(subs, subs + subsn(), 0) / subsn();
    int fuel2 = 0;

    std::for_each(subs, subs + subsn(), [&fuel2, &mean](auto s) {
        int range = std::abs(s - mean);
        fuel2 += range * (range + 1) / 2;
    });

    std::cout << "P2 fuel: " << fuel2 << std::endl;

    return 0;
}