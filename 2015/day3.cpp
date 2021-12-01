#include <algorithm>
#include <string>
#include <fstream>
#include <vector>
#include <iostream>

static void part_one(const std::string &fn) {
    std::vector<std::pair<int, int>> houses;
    std::ifstream f(fn);
    std::string line;
    int x = 0;
    int y = 0;
    bool unknown = false;

    houses.emplace_back(std::pair<int, int>(x,  y));
    while(f >> line) {
        for (char c : line) {
            switch (c) {
                case '<':
                    x--;
                    break;
                case '>':
                    x++;
                    break;
                case '^':
                    y++;
                    break;
                case 'v':
                    y--;
                    break;
                default:
                    unknown= true;
                    break;
            }
            if (!unknown &&
                std::find(houses.begin(), houses.end(), std::pair<int, int>(x, y)) == houses.end()) {
                houses.emplace_back(std::pair<int, int>(x, y));

            }
        }
    }

    f.close();
    std::cout << "P1: Visited unique houses: " << houses.size() << std::endl;
}

static void part_two(const std::string &fn) {
    std::vector<std::pair<int, int>> houses;
    std::ifstream f(fn);
    std::string line;
    int x1 = 0, x2 = 0;
    int y1= 0, y2 = 0;
    bool unknown = false;

    houses.emplace_back(std::pair<int, int>(x1, y1));

    while(f >> line) {
        for (int i = 0; i < line.size(); i += 2) {

            switch (line[i]) {
                case '<':
                    x1--;
                    break;
                case '>':
                    x1++;
                    break;
                case '^':
                    y1++;
                    break;
                case 'v':
                    y1--;
                    break;
                default:
                    unknown= true;
                    break;
            }
            if (!unknown &&
                std::find(houses.begin(), houses.end(), std::pair<int, int>(x1, y1)) == houses.end()) {
                    houses.emplace_back(std::pair<int, int>(x1, y1));

            }
            unknown = false;

            switch (line[i + 1]) {
                case '<':
                    x2--;
                    break;
                case '>':
                    x2++;
                    break;
                case '^':
                    y2++;
                    break;
                case 'v':
                    y2--;
                    break;
                default:
                    unknown= true;
                    break;
            }
            if (!unknown &&
                std::find(houses.begin(), houses.end(), std::pair<int, int>(x2, y2)) == houses.end()) {
                houses.emplace_back(std::pair<int, int>(x2, y2));

            }
            unknown = false;

        }
    }

    f.close();
    std::cout << "P2: Visited unique houses: " << houses.size() << std::endl;
}

int main(int argc, char *argv[]) {
    part_one("day3.input");
    part_two("day3.input");
    return 0;
}