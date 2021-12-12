#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

static const std::vector offs{
    std::pair(-1, -1),
    std::pair(0, -1),
    std::pair(1, -1),
    std::pair(-1, 0),
    std::pair(1, 0),
    std::pair(-1, 1),
    std::pair(0, 1),
    std::pair(1, 1),
};

int flash(std::vector<std::string> &map, std::pair<int, int> point) {
    std::queue<typeof(point)> q{};
    int flashcnt = 0;

    q.push(point);
    map[point.second][point.first] = std::numeric_limits<char>::min();

    while (!q.empty()) {
        auto p = q.front();
        q.pop();

        flashcnt++;

        for(auto &o: offs) {
            std::pair np{p.first + o.first, p.second + o.second};
            if (np.first >= 0 && np.first < map[0].length() && np.second >= 0 && np.second < map.size()) {
                if (map[np.second][np.first] != std::numeric_limits<char>::min()) {
                    map[np.second][np.first]++;
                    if (map[np.second][np.first] >= 10`) {
                        map[np.second][np.first] = std::numeric_limits<char>::min();
                        q.push(np);
                    }
                }
            }
        }
    }

    return flashcnt;
}

int main(int argc, char *argv[]) {
    std::ifstream f("day11.input");
    std::string word;
    std::vector<std::string> map;
    int flashes = 0;

    if (!f.good()) {
        std::cerr << "File open error";
        return 1;
    }

    while (f >> word) {
        if (word.length() == 0) {
            continue;
        }
        std::transform(word.begin(), word.end(), word.begin(),
                       [](auto c) -> auto { return c - '0'; });
        map.push_back(word);
    }

    int i = 0;
    int flashes100;
    bool fullflash = false;

    while(!fullflash) {
        for (int y = 0; y < map.size(); y++) {
            for (int x = 0; x < map[0].length(); x++) {
                map[y][x] += 1;
            }
        }
        for (int y = 0; y < map.size(); y++) {
            for (int x = 0; x < map[0].length(); x++) {
                if (map[y][x] == 10) {
                    flashes += flash(map, {x, y});
                }
            }
        }

        fullflash = true;
        for (int y = 0; y < map.size(); y++) {
            for (int x = 0; x < map[0].length(); x++) {
                if (map[y][x] == std::numeric_limits<char>::min()) {
                    map[y][x] = 0;
                } else {
                    fullflash = false;
                }
            }
        }

        if (i == 99) {
            flashes100 = flashes;
        }
        i++;
    }

    std::cout << "P1 flashes: " << flashes100 << std::endl;
    std::cout << "P2 cycles: " << i << std::endl;

    return 0;
}