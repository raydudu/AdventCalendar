

#include <fstream>
#include <iostream>
#include <map>
#include <cstring>

int main(int argc, char *argv[]) {
    std::ifstream f("day14.input");
    std::string word;
    std::map<std::string, char> map;
    std::map<std::string, unsigned long > paircount;
    unsigned long count10[26];
    unsigned long count40[26];


    if (!f.good()) {
        std::cerr << "File open error" << std::endl;
    }

    memset(count10, 0, sizeof count10);

    f >> word;
    for(int i = 0; i < word.length() - 1; i++) {
        std::string pair = word.substr(i, 2);
        auto p = paircount.find(pair);
        if (p == paircount.end()) {
            paircount.emplace(pair, 1);
        } else {
            p->second++;
        }
        count10[word[i] - 'A'] += 1;
    }
    count10[word[word.length() - 1] - 'A'] += 1;

    memcpy(count40, count10, sizeof count40);

    while (std::getline(f, word)) {
        char pair[3];
        char result;
        if (word.length() == 0) {
            continue;
        }

        sscanf(word.c_str(), "%c%c -> %c", &pair[0], &pair[1], &result);
        pair[2] = 0;
        map.emplace(std::string{pair}, result);
    }

    f.close();

    for(int cycle = 0; cycle < 40; cycle++) {
        typeof paircount paircount_new{};

        for (auto &p : paircount) {

            auto e = map.at(p.first);
            if (cycle < 10) {
                count10[e - 'A'] += p.second;
            }
            count40[e - 'A'] += p.second;

            auto name = std::string({p.first[0], e});
            auto np = paircount_new.find(name);
            if (np == paircount_new.end()) {
                paircount_new.insert({name, p.second});
            } else {
                np->second += p.second;
            }

            name[0] = e;
            name[1] = p.first[1];
            np = paircount_new.find(name);
            if (np == paircount_new.end()) {
                paircount_new.insert({name, p.second});
            } else {
                np->second += p.second;
            }
        }
        paircount = std::move(paircount_new);
    }

    auto min = std::numeric_limits<unsigned long>::max();
    auto max = std::numeric_limits<unsigned long>::min();
    for (auto c : count10) {
        if (c == 0) {
            continue;
        }
        min = std::min(min, c);
        max = std::max(max, c);
    }
    std::cout << "P1 diff: " << max - min << std::endl;

    min = std::numeric_limits<unsigned long>::max();
    max = std::numeric_limits<unsigned long>::min();
    for (auto c : count40) {
        if (c == 0) {
            continue;
        }
        min = std::min(min, c);
        max = std::max(max, c);
    }
    std::cout << "P2 diff: " << max - min << std::endl;

    return 0;
}