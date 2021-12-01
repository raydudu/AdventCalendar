
#include <string>
#include <fstream>
#include <iostream>

static void part_one(const std::string &fn) {
    std::ifstream f(fn);
    std::string line;
    int nice_cnt = 0;

    while (f >> line) {
        int vovels = 0;
        char pletter = 0;
        bool double_present = false;

        for (char &c: line) {
            if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
                vovels++;
            }
            if (c == pletter) {
                double_present = true;
            }
            pletter = c;
        }
        if (!double_present || vovels < 3) {
            continue;
        }
        if (line.find("ab") != std::string::npos ||
                line.find("cd") != std::string::npos ||
                line.find("pq") != std::string::npos ||
                line.find("xy") != std::string::npos) {
            continue;
        }
        nice_cnt++;
    }

    f.close();

    std::cout << "P1: Nice words count: " << nice_cnt << std::endl;
}


static void part_two(const std::string &fn) {
    std::ifstream f(fn);
    std::string line;
    int nice_cnt = 0;

    while (f >> line) {
        bool good1 = false;
        bool good2 = false;
        for (int i = 0; i < line.size() - 2; i++) {
            std::string d = line.substr(i, 2);
            if (line.find(d, i + 2) != std::string::npos) {
                good1 = true;
                if (good2) break;
            }
            if(line[i] == line[i + 2]) {
                good2 = true;
                if (good1) break;
            }
        }
        if (good1 && good2) {
            nice_cnt++;
        }
    }

    f.close();

    std::cout << "P2: Nice words count: " << nice_cnt << std::endl;
}


int main(int argc, char *argv[]) {
    part_one("day5.input");
    part_two("day5.input");
    return 0;
}
