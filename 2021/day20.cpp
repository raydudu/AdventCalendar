#include <fstream>
#include <vector>
#include <iostream>
#include <algorithm>

static const std::pair<int, int> offs[] = {
        std::pair{-1,-1},
        std::pair{0,-1},
        std::pair{1,-1},
        std::pair{-1,0},
        std::pair{0,0},
        std::pair{1,0},
        std::pair{-1,1},
        std::pair{0,1},
        std::pair{1,1},
};

void enhance(std::vector<std::string> &map, std::string &algo, char infval) {
    typeof map res;
    for (int i = 0; i < map.size() + 2; i++) {
        std::string l;
        l.append(map[0].length() + 2, ' ');
        res.emplace_back(l);
    }

    for (int y = 0; y < res.size(); y++) {
        for(int x = 0; x < res[0].size(); x++) {
            unsigned bitmask = 0;
            for (int bit = 0; bit < 9; bit++) {
                auto dx = x + offs[bit].first;
                auto dy = y + offs[bit].second;
                if (0 <= dx - 1 && dx -1 < map[0].length() &&  0 <= dy - 1 && dy - 1 < map.size()) {
                    if (map[dy - 1][dx - 1] == '#') {
                        bitmask |= 1 << (8 - bit);
                    }
                } else if (infval == '#') {
                    bitmask |= 1 << (8 - bit);
                }
            }
            res[y][x] = algo[bitmask];
        }
    }
    map = std::move(res);
}
void print(std::vector<std::string> &map) {
    for (auto &l : map) {
        std::cout << l << std::endl;
    }
    std::cout << std::endl;
}

unsigned count(std::vector<std::string> &map) {
    unsigned ret = 0;
    for (auto & l : map) {
        ret += std::count(l.begin(), l.end(), '#');
    }
    return ret;
}
int main(int argc, char *argv[]) {
    std::vector<std::string> map;
    std::string algo;
    std::string line;

    std::ifstream f("day20.input");
    if (!f.good()) {
        std::cerr << "File open error" << std::endl;
        return 1;
    }
    f >> algo;
    while (f >> line) {
        map.emplace_back(line);
    }
    f.close();

    print(map);

    for (int i = 0; i < 2; i++) {
        char infval = '.';
        if (algo[0] == '#' && (i & 0x1)) {
            infval = algo[0];
        }
        enhance(map, algo, infval);
        print(map);
    }

    std::cout << "P1 pixel count: " << count(map) << std::endl;

    for (int i = 2; i < 50; i++) {
        char infval = '.';
        if (algo[0] == '#' && (i & 0x1)) {
            infval = algo[0];
        }
        enhance(map, algo, infval);
    }

    std::cout << "P2 pixel count: " << count(map) << std::endl;

    return 0;
}