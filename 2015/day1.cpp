#include <iostream>
#include <fstream>

static void part_one(const std::string &fn) {
    std::ifstream f(fn);
    int floor = 0;
    std::string line;

    while(f >> line) {
        for(char c: line) {
            if (c == '(') {
                floor++;
            } else if (c == ')') {
                floor--;
            }
        }
    }

    f.close();

    std::cout << "P1: Target Floor: " << floor << std::endl;
}

static void part_two(const std::string &fn) {
    std::ifstream f(fn);
    int floor = 0;
    int step = 1;
    std::string line;

    while(f >> line) {
        for(char c: line) {
            if (c == '(') {
                floor++;
                step++;
            } else if (c == ')') {
                floor--;
                step++;
            }
            if (floor == -1) {
                step--;
                break;
            }
        }
    }

    f.close();

    std::cout << "P2: Basement enter step: " << step << std::endl;
}

int main() {
    part_one("day1.input");
    part_two("day1.input");
    return 0;
}
