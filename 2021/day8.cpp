#include <iostream>
#include <algorithm>
#include <cstring>
#include <fstream>

void decode(std::string *d, int *map) {
    int rmap[10];

    std::memset(map, 0xff, sizeof(rmap));
    std::memset(rmap, 0xff, sizeof(map));

    for (int i = 0; i < 10; i++) {
        switch (d[i].length()) {
            case 2 :
                map[i] = 1;
                rmap[1] = i;
                break;
            case 4:
                map[i] = 4;
                rmap[4] = i;
                break;
            case 3:
                map[i] = 7;
                rmap[7] = i;
                break;
            case 7:
                map[i] = 8;
                break;
            default:
                break;
        }
    }

    for (int i = 0; i < 10; i++) {
        if (map[i] != -1) {
            continue;
        }
        if (d[i].length() == 6) { //0,6,9
            if ((d[i].find(d[rmap[1]].c_str()[0]) != std::string::npos) !=
                (d[i].find(d[rmap[1]].c_str()[1]) != std::string::npos)) { //6
                map[i] = 6;
                rmap[6] = i;
                continue;
            }
            if (d[i].find(d[rmap[4]].c_str()[0]) != std::string::npos &&   // 9
                d[i].find(d[rmap[4]].c_str()[1]) != std::string::npos &&
                d[i].find(d[rmap[4]].c_str()[2]) != std::string::npos &&
                d[i].find(d[rmap[4]].c_str()[3]) != std::string::npos) {
                map[i] = 9;
                rmap[9] = i;
                continue;
            }
        } else if (d[i].length() == 5) { // 2,3,5
            if (d[i].find(d[rmap[1]].c_str()[0]) != std::string::npos &&
                d[i].find(d[rmap[1]].c_str()[1]) != std::string::npos) { //3
                map[i] = 3;
                rmap[3] = i;
                continue;
            }
        }
    }
    for (int i = 0; i < 10; i++) {
        if (map[i] != -1) {
            continue;
        }
        if (d[i].length() == 5) { // 2,5
            if (d[rmap[9]].find(d[i].c_str()[0]) != std::string::npos && //5
                d[rmap[9]].find(d[i].c_str()[1]) != std::string::npos &&
                d[rmap[9]].find(d[i].c_str()[2]) != std::string::npos &&
                d[rmap[9]].find(d[i].c_str()[3]) != std::string::npos &&
                d[rmap[9]].find(d[i].c_str()[4]) != std::string::npos) {
                map[i] = 5;
                rmap[5] = i;
                continue;
            }
        } else if (d[i].length() == 6 && rmap[6] != -1 && rmap[9] != -1) { //0
            map[i] = 0;
            rmap[0] = i;
        }
    }

    for (int i = 0; i < 10; i++) {
        if (map[i] == -1) { //2
            map[i] = 2;
            break;
        }
    }
}

int main(int argc, char *argv[]) {

    std::ifstream f("day8.input");
    std::string word;
    int sum = 0;

    if (!f.good()) {
        std::cerr << "File open error: " << strerror(errno) << std::endl;
        return 1;
    }

    do {
        std::string cd[10];
        int map[10];
        int dnum = 0;
        std::string val;


        for (auto &c: cd) {
            f >> c;
            std::sort(c.begin(), c.end());
        }
        decode(cd, map);
        f >> val;

        for (int i = 0; i < 4; i++) {
            f >> val;
            std::sort(val.begin(), val.end());
            auto id = std::find(cd, cd + 10, val);
            dnum = dnum * 10 + map[id - cd];
        }

        sum += dnum;
    } while (!f.eof());

    f.close();

    std::cout << "P2 sum: " << sum << std::endl;
    return 0;
}