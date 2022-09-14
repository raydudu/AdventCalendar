#include <map>
#include <iostream>
#include <vector>
#include <stack>

static const std::map<char, int> costs = {
        {'A', 1},
        {'B', 10},
        {'C', 100},
        {'D', 1000}
};

struct Amphoid {
    char type;
    int y;
    int x;
};

static const std::vector<Amphoid> map_p2 = {
    {'C', 1, 2},
    {'D', 2, 2},
    {'D', 3, 2},
    {'B', 4, 2},

    {'D', 1, 4},
    {'C', 2, 4},
    {'B', 3, 4},
    {'A', 4, 4},

    {'A', 1, 6},
    {'B', 2, 6},
    {'A', 3, 6},
    {'D', 4, 6},

    {'B', 1, 8},
    {'A', 2, 8},
    {'C', 3, 8},
    {'C', 4, 8}
};


static const std::vector<Amphoid> map_p1 = {
        {'C', 1, 2},
        {'B', 2, 2},

        {'D', 1, 4},
        {'A', 2, 4},

        {'A', 1, 6},
        {'D', 2, 6},

        {'B', 1, 8},
        {'C', 2, 8}
};

static const std::map<char, int> targetX = {
        {'A', 2},
        {'B', 4},
        {'C', 6},
        {'D', 8}
};

static const std::vector<int> corridorCoords = {0, 1, 3, 5, 7, 9, 10};

struct Hash {
    char x[16];

    Hash() {
        memset(x, 0, 16);
    }

    bool operator<(const Hash &rhs) const {
        return memcmp(x, rhs.x, 16) < 0;
    }
    bool operator==(const Hash &rhs) const {
        return memcmp(x, rhs.x, 16) == 0;
    }
};
Hash amphypod_hash(const std::vector<Amphoid> &amphipods) {
    Hash hash;
    const auto divider = amphipods.size() / 4;
    char positions[4] = {0, 0, 0, 0};

    for (auto &a : amphipods) {
        auto anr = a.type - 'A';
        hash.x[positions[anr] + anr * divider] = (a.y & 0xF) << 4 | a.x;
        positions[anr]++;
    }

    for (unsigned i = 0; i < amphipods.size() - 1; i += divider) {
        std::sort(hash.x + i, hash.x + i + divider);
    }

    return hash;
}

unsigned long home(const std::vector<Amphoid> &map, int maxY) {
    std::map<Hash, std::pair<unsigned long, std::vector<Amphoid>>> acache;
    std::stack<Hash> q;
    unsigned long ret = std::numeric_limits<unsigned long>::max();
    auto h = amphypod_hash(map);
    q.push(h);
    acache.insert({h, {0, map}});


    while (!q.empty()) {
        h = q.top();
        auto s = acache.at(h).second;
        auto currentCost = acache.at(h).first;
        q.pop();

        bool everybodyHome = true;
        for (auto &a : s ) {
           auto hx = targetX.at(a.type);
           if (a.x != hx) {
               everybodyHome = false;
               break;
           }
        }

        if (everybodyHome) { // we are done?
            if (currentCost < ret) {
                ret = currentCost;
                std::cout << ret << std::endl;
            }
        }

        for (auto &a: s) {
            auto hx = targetX.at(a.type);
            bool isHomeFree = true;
            bool isBlocked = false;
            bool atHome = (hx == a.x);
            int freeHomeYPos = maxY;
            for (auto &hc: s) {
                if (hc.x == hx) {
                    if (isHomeFree && hc.type != a.type) {
                        isHomeFree = false;
                        continue;
                    }
                    if (hc.y <= freeHomeYPos) {
                        freeHomeYPos = hc.y - 1;
                    }
                } else if (hc.x == a.x) {
                    if (hc.y < a.y) {
                        isBlocked = true;
                    }
                    if (atHome && hc.type != a.type && hc.y > a.y) {
                        atHome = false;
                    }
                }
            }

            std::vector<std::pair<int, int> > moves;
            if (a.y == 0) { // In a corridor
                if (!isHomeFree) {
                    continue;
                }
                moves.emplace_back(std::make_pair(freeHomeYPos, hx));
            } else { // In a room
                if (atHome || isBlocked) {
                    continue;
                }
                // move to all corridor spaces
                std::for_each(corridorCoords.begin(), corridorCoords.end(), [&moves](auto &cc) {
                    moves.emplace_back(std::make_pair(0, cc));
                });
            }
            for (auto &m: moves) {
                bool isPathBlocked = false;
                int xMin;
                int xMax;
                if (m.second > a.x) {
                    xMax = m.second;
                    xMin = a.x;
                } else {
                    xMax = a.x;
                    xMin = m.second;
                }
                for (auto &hc: s) {
                    if (hc.y != 0 || hc.x == a.x) {
                        continue;
                    }
                    if (xMin <= hc.x && hc.x <= xMax) {
                        isPathBlocked = true;
                        break;
                    }
                }
                if (isPathBlocked) {
                    continue;
                }

             //   std::cout << "move: " << m.second << "," << m.first << std::endl;
                auto futureCost = currentCost + (std::abs(a.x - m.second) + std::abs(a.y - m.first)) * costs.at(a.type);
                auto tmp = a;
                a.x = m.second;
                a.y = m.first;
                auto futureState = s;
                a = tmp;

                auto new_h = amphypod_hash(futureState);
                auto ce = acache.find(new_h);
                if (ce != acache.end()) {
                    if (ce->second.first > futureCost) {
                        ce->second.first = futureCost;
                    } else {
                        continue;
                    };
                } else {
                    acache.insert({new_h, {futureCost, futureState}});
                }
                q.push(new_h);
            }
        }
    }

    return ret;
}

int main(int argc, char *argv[]) {


    auto p1 = home(map_p1, 2);
    std::cout << "P1: " << p1  << std::endl;

/*
    auto p2 = home(map_p2, 4);
    std::cout << "P2: " << p2 << std::endl;
*/
     return 0;
}