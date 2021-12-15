#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <list>

struct Node {
    bool visited;
    unsigned totalRisk;
    int x;
    int y;
};

static const std::vector offs{
        std::pair(1, 0),
        std::pair(-1, 0),
        std::pair(0, 1),
        std::pair(0, -1)
};


int traverse(std::vector<std::string> &map) {
    auto width = map[0].length();
    auto height = map.size();

    Node nodes[height * width];

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++ ){
            nodes[y * width + x].visited = false;
            nodes[y * width + x].totalRisk = std::numeric_limits<typeof nodes[y * width + x].totalRisk>::max();
            nodes[y * width + x].x = x;
            nodes[y * width + x].y = y;
        }
    }

    auto node = &nodes[0];
    auto target = &node[(height - 1) * width + width - 1];
    node->totalRisk = 0;

    std::list<Node *> q;

    q.push_back(node);

    while (!q.empty() && node != target) {
        q.sort([](const Node *l, const Node *r){ return l->totalRisk < r->totalRisk; } );

        node = q.front();
        q.pop_front();
        node->visited = true;

        for (const auto &o : offs) {
            int nx = node->x + o.first;
            int ny = node->y + o.second;

            if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
                Node *neighbour = &nodes[ny * width + nx];
                auto nRisk = node->totalRisk + map[ny][nx];

                if (!neighbour->visited) {
                    auto it = std::find_if(q.begin(), q.end(), [&nx, &ny](const Node *i){
                        return i->x == nx && i->y == ny;
                    });

                    if (it == q.end()) {
                        q.push_back(neighbour);
                    } else if ((*it)->totalRisk > nRisk){
                        (*it)->totalRisk = nRisk;
                    }
                }
                if (nRisk < neighbour->totalRisk) {
                    neighbour->totalRisk = nRisk;
                }
            }
        }
    }

    return target->totalRisk;
}

int main(int argc, char *argv[]) {
    std::ifstream f("day15.input");
    std::string line;
    std::vector<std::string> map;

    if (!f.good()) {
        std::cerr << "File open error" << std::endl;
        return 1;
    }

    while (f >> line) {
        std::transform(line.begin(), line.end(),line.begin(), [](auto &c) {
            return c - '0';
        });
        map.emplace_back(std::move(line));
    }

    f.close();

    std::cout << "P1 risk: " << traverse(map) << std::endl;

    for (auto &s: map) {
        auto l = s.length();
        s.resize(l * 5);
        for (unsigned i = 0; i < l; i++) {
            for(unsigned st = 1; st < 5; st++) {
                char nv = s[i + l * (st - 1)] + 1;
                if (nv > 9) {
                    s[i + l * st] = 1;
                } else {
                    s[i + l * st] = nv;
                }
            }
        }
    }

    auto l = map.size();
    map.resize(l * 5);
    for (unsigned i = 0; i < l; i++) {
        std::string nl{map[i]};
        for(unsigned st = 1; st < 5; st++) {
            std::transform(nl.begin(), nl.end(), nl.begin(), [](auto &c) {
                return (c + 1) > 9 ? 1 : c + 1;
            });
            map[i + l * st] = nl;
        }
    }

    std::cout << "P2 risk: " << traverse(map) << std::endl;
    return 0;
}
