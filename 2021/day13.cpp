#include <fstream>
#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>
#include <cstring>


int main(int argc, char *argv[]) {
    std::ifstream f("day13.input");
    std::vector<std::pair<int, int>> dots;

    if (!f.good()) {
        std::cerr << "File open error" << std::endl;
        return 1;
    }

    std::string word;

    while(f >> word) {
        auto pos = strchr(word.c_str(), ',');
        if (pos != nullptr) {
            word[pos - word.c_str()] = 0;
            int x = std::stoi(word);
            int y = std::stoi(pos + 1);

            dots.emplace_back(std::make_pair(x, y));
        } else {
            pos = strchr(word.c_str(), '=');
            if (pos == nullptr) {
                continue;
            }

            const char fold = pos[-1];
            int line = std::stoi(pos + 1);
            if (fold == 'x') {
                for(auto &d : dots) {
                    if (d.first > line) {
                        d.first = line - (d.first - line);
                    }
                }
            } else {
                assert(fold == 'y');
                for(auto &d : dots) {
                    if (d.second > line) {
                        d.second = line - (d.second - line);
                    }
                }
            }


            static bool p1_ans;
            if (!p1_ans) {
                std::sort(dots.begin(), dots.end());
                auto last = std::unique(dots.begin(), dots.end());

                dots.erase(last, dots.end());

                std::cout << "P1 dots: " << dots.size() << std::endl;
                p1_ans = true;
            }

        }
    }

    f.close();

    bool drawn;
    int ln = 0;
    do {
        drawn = false;
        std::string ol;

        for (auto &d: dots) {
            if (d.second == ln) {
                drawn = true;
                if (ol.length() <= d.first) {
                    ol.append(d.first - ol.length() + 1, ' ');
                }
                ol[d.first] = '#';
            }
        }

        std::cout << ol << std::endl;

        ln++;
    } while (drawn);

    return 0;
}