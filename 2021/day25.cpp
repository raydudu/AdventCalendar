#include <string>
#include <iostream>
#include <fstream>
#include <vector>

int main(int argc, char *argv[]) {
    std::ifstream f("day25.input");
    std::string line;
    std::vector<std::string> map;

    if (!f.good()) {
        std::cerr << "File open error" << std::endl;
        return 1;
    }

    while(f >> line) {
        map.emplace_back(line);
    }

    f.close();

    auto width = map[0].size();
    auto height = map.size();

    bool moved;
    unsigned steps = 0;
    do {
        steps++;
        moved = false;
        auto newmap = map;

        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                if (map[y][x] == '>' && map[y][ (x + 1) % width] == '.') {
                    moved = true;
                    newmap[y][x] = '.';
                    newmap[y][(x + 1) % width] = '>';
                 }
            }
        }
        map = newmap;
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                if (map[y][x] == 'v' && map[(y + 1) % height][x] == '.') {
                    moved = true;
                    newmap[y][x] = '.';
                    newmap[(y + 1) % height][x] = 'v';
                }
            }
        }
        map = newmap;
    } while (moved);

    std::cout << "P1: " << steps << std::endl;
    return 0;
}