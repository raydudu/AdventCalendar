#include <fstream>
#include <vector>
#include <sstream>
#include <iostream>
#include <algorithm>

static const auto boardwidth = 5;

int main(int argc, char *argv[]) {
    std::ifstream f("day04.input");
    std::string word;
    std::vector<int> draw;
    int fwin_score;
    int fwin_pos = std::numeric_limits<int>::max();

    int lwin_score;
    int lwin_pos = 0;

    f >> word;

    std::stringstream parser(word);
    for (int i = 0; parser >> i;){
        draw.push_back(i);
        if (!isdigit(parser.peek())) {
            parser.ignore();
        }
    }

    do {
        std::vector<int> board(boardwidth * boardwidth);
        int vscore[boardwidth] = {0, };
        int hscore[boardwidth] = {0, };
        for (auto& i : board) {
            f >> word;
            i = std::stoi(word);
        }
        for (auto d = draw.begin(); d != draw.end(); d++) {
            auto pos = std::find(board.begin(), board.end(), *d);
            if (pos != board.end()) {
                *pos = -1;
                auto idx = std::distance(board.begin(), pos);
                vscore[idx % 5]++;
                hscore[idx / 5]++;
                if (vscore[idx % 5] == 5 || hscore[idx / 5] == 5) {
                    int sum = 0;
                    int step = static_cast<int>(std::distance(draw.begin(), d));
                    std::for_each(board.begin(), board.end(),
                                  [&sum](auto b) {
                        sum += b == -1 ? 0 : b;
                    } );
                    std::cout << "Win On step: " << step << ", Sum: " << sum << ", Nr: " << *d << std::endl;

                    if (std::min(fwin_pos, step) == step) {
                        fwin_score = sum * *d;
                        fwin_pos = step;
                    }

                    if (std::max(lwin_pos, step) == step) {
                        lwin_score = sum * *d;
                        lwin_pos = step;
                    }

                    break;
                }

            }
        }

    } while (!f.eof());

    f.close();

    std::cout << "P1 score: " << fwin_score << std::endl;
    std::cout << "P2 score: " << lwin_score << std::endl;

    return 0;
}