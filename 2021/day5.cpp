
#include <fstream>
#include <iostream>

static const auto edge_len = 1000;

static int map[edge_len * edge_len];
#define pmap(_x, _y) map[(_y) * edge_len + (_x)]

static int map2[edge_len * edge_len];
#define pmap2(_x, _y) map2[(_y) * edge_len + (_x)]

int main(int argc, char *argv[]) {
    std::ifstream f("day5.input");
    std::string line;

    while (std::getline(f, line)) {
        int x1, x2, y1, y2;
        std::sscanf(line.c_str(), "%d,%d -> %d,%d", &x1, &y1, &x2, &y2);

        if (x1 == x2) { // horisontal
            for (int y = std::min(y1, y2); y <= std::max(y1, y2); y++) {
                pmap(x1, y)++;
            }
        } else if (y1 == y2) {
            for (int x = std::min(x1, x2); x <= std::max(x1, x2); x++) {
                pmap(x, y1)++;
            }
        }
        {  // diagonal
            int dx = x2 - x1;
            int dy = y2 - y1;
            int xshift = dx == 0 ? 0 : dx < 0 ? -1 : 1;
            int yshift = dy == 0 ? 0 : dy < 0 ? -1 : 1;
            dx = std::abs(dx);
            dy = std::abs(dy);
            for (int i = 0; i <= std::max(dx, dy); i++) {
                pmap2(x1 + xshift * i, y1 + yshift * i)++;
            }

        }
    }

    int count1 = 0;
    int count2 = 0;

    for (int m = 0; m < edge_len * edge_len; m++) {
        if (map[m] > 1) {
            count1++;
        }
        if (map2[m] > 1) {
            count2++;
        }
    }

    std::cout << "P1 count: " << count1 << std::endl;
    std::cout << "P2 count: " << count2 << std::endl;

    return 0;
}