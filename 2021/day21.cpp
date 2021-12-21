#include <iostream>
#include <vector>
#include <map>

#if 0
constexpr int p1_start = 4;
constexpr int p2_start = 8;
#else
constexpr int p1_start = 7;
constexpr int p2_start = 9;
#endif

int roll() {
    static int score = 0;
    return ++score;
}

std::vector<int> dice_permutations;
std::map<uint64_t, std::pair<unsigned long, unsigned long> > acache;

constexpr auto id = [](int p1, int s1, int p2, int s2) {
    return (unsigned)p1 << 24 | s1 << 16 | p2 << 8 | s2;
};

std::pair<unsigned long, unsigned long> check4win(int p1, int s1, int p2, int s2) {
    if (s1 >= 21) {
        return {1, 0};
    }
    if (s2 >= 21) {
        return {0, 1};
    }
    auto resp = acache.find(id(p1, s1, p2, s2));
    if (resp != acache.end()) {
        return resp->second;
    }

    std::pair<unsigned long, unsigned long> res{0, 0};
    for (auto d : dice_permutations) {
        auto np1 = (p1 + d) % 10;
        auto ns1 = s1 + np1 + 1;
        auto r = check4win(p2, s2, np1, ns1);
        res.first += r.second; // Swap the results back
        res.second += r.first;
    }
    acache.insert({id(p1, s1, p2, s2), res});
    return  res;
};

int main(int argc, char *argv[]) {
    int s1 = 0;
    int s2 = 0;

    auto p1 = p1_start - 1;
    auto p2 = p2_start - 1;
    while (s1 < 1000 || s2 < 1000) {
        p1 = (p1 + roll() + roll() + roll()) % 10;
        s1 += p1 + 1;
        if (s1 >= 1000) {
            break;
        }

        p2 = (p2 + roll() + roll() + roll()) % 10;
        s2 += p2 +1;
    }
    std::cout << "P1: " << std::min(s1, s2) * (roll() - 1) << std::endl;

    p1 = p1_start - 1;
    p2 = p2_start - 1;
    for (int d1: { 1, 2, 3}) {
        for (int d2: { 1, 2, 3}) {
            for (int d3: {1, 2, 3}) {
                dice_permutations.push_back(d1 + d2 + d3);
            }
        }
    }

    auto wcnt = check4win(p1, 0, p2, 0);
    std::cout << "P2: " << std::max(wcnt.first, wcnt.second);
    return 0;
}