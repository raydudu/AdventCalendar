#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <stack>
#include <algorithm>

static const std::map<char, unsigned> score = {
        {')', 3 },
        {']',57 },
        {'}', 1197 },
        {'>', 25137 },
};

static const std::map<char, unsigned> ascore = {
        {'(', 1},
        {'[', 2},
        {'{', 3},
        {'<', 4}
};

int main(int argc, char *argv[]) {
    std::ifstream f("day10.input");
    std::string word;
    unsigned corrupt_score = 0;
    std::vector<unsigned long> ac_score{};

    if (!f.good()) {
        std::cerr << "File open error" << std::endl;
        return 1;
    }

    while (f >> word) {
        bool corrupt = false;
        std::stack<char> h{};

        for (auto c: word) {
            switch (c) {
                case '(':
                case '[':
                case '{':
                case '<':
                    h.push(c);
                    break;
                case ')':
                    if (h.top() != '(') {
                        corrupt = true;
                    } else {
                        h.pop();
                    }
                    break;
                case ']':
                    if (h.top() != '[') {
                        corrupt = true;
                    } else {
                        h.pop();
                    }
                    break;
                case '}':
                    if (h.top() != '{') {
                        corrupt = true;
                    } else {
                        h.pop();
                    }
                    break;
                case '>':
                    if (h.top() != '<') {
                        corrupt = true;
                    } else {
                        h.pop();
                    }
                    break;
                default:
                    exit(2);
            }
            if (corrupt) {
                corrupt_score += score.at(c);
                break;
            }
        }
        if (!corrupt) {
            unsigned long lscore = 0;
            while(!h.empty()) {
                lscore = lscore * 5 + ascore.at(h.top());
                h.pop();
            }
            ac_score.push_back(lscore);
        }
    }
    f.close();

    std::cout << "P1 score: " << corrupt_score << std::endl;

    std::sort(ac_score.begin(), ac_score.end());
    std::cout << "P2 score: " << ac_score[ac_score.size() / 2] << std::endl;

    return 0;
}