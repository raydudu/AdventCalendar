#include <fstream>
#include <string>
#include <iostream>
#include <list>
#include <vector>

class Paralelepiped {
    int xStart;
    int xEnd;
    int yStart;
    int yEnd;
    int zStart;
    int zEnd;

public:
    Paralelepiped(int xStart, int xEnd, int yStart, int yEnd, int zStart, int zEnd) : xStart(xStart), xEnd(xEnd),
                                                                                      yStart(yStart), yEnd(yEnd),
                                                                                      zStart(zStart), zEnd(zEnd) {}
    [[nodiscard]] bool isIntersects(const Paralelepiped &c) const {
        return std::max(xStart, c.xStart) < std::min(xEnd, c.xEnd) &&
                std::max(yStart, c.yStart) < std::min(yEnd, c.yEnd) &&
                std::max(zStart, c.zStart) < std::min(zEnd, c.zEnd);
    }

    [[nodiscard]] Paralelepiped intersection(const Paralelepiped &c) const {
        return {std::max(xStart, c.xStart), std::min(xEnd, c.xEnd),
                std::max(yStart, c.yStart), std::min(yEnd, c.yEnd),
                std::max(zStart, c.zStart), std::min(zEnd, c.zEnd)};;
    }

    [[nodiscard]] std::vector<Paralelepiped> split_subtract(const Paralelepiped &ic) const {
        std::vector<Paralelepiped> ret;

        int xArr[] = {xStart, xEnd, ic.xStart, ic.xEnd};
        std::sort(xArr, xArr + 4);

        int yArr[] = {yStart, yEnd, ic.yStart, ic.yEnd};
        std::sort(yArr, yArr + 4);

        int zArr[] = {zStart, zEnd, ic.zStart, ic.zEnd};
        std::sort(zArr, zArr + 4);

        for (int x = 0; x < 3; x++) {
            if (xArr[x] == xArr[x + 1]) {
                continue;
            }
            Paralelepiped slice(xArr[x], xArr[x + 1], 0, 0, 0, 0);
            for (int y = 0; y < 3; y++) {
                if (yArr[y] == yArr[y + 1]) {
                    continue;
                }
                slice.yStart = yArr[y];
                slice.yEnd = yArr[y + 1];
                for (int z = 0; z < 3; z++) {
                    if (zArr[z] == zArr[z + 1]) {
                        continue;
                    }
                    slice.zStart = zArr[z];
                    slice.zEnd = zArr[z + 1];

                    if (slice == ic) {
                        continue;
                    }
                    ret.push_back(slice);
                }
            }
        }

        return ret;
    }

    [[nodiscard]] unsigned long volume() const {
        return (unsigned long)std::abs(xEnd - xStart) * std::abs(yEnd - yStart) * std::abs(zEnd - zStart);
    }

    friend std::ostream &operator<<(std::ostream &os, const Paralelepiped &cube) {
        os << "{" << cube.xStart << ".." << cube.xEnd << "," << cube.yStart << ".."
           << cube.yEnd << "," << cube.zStart << ".." << cube.zEnd << "}";
        return os;
    }

    bool operator==(const Paralelepiped &rhs) const {
        return xStart == rhs.xStart &&
               xEnd == rhs.xEnd &&
               yStart == rhs.yStart &&
               yEnd == rhs.yEnd &&
               zStart == rhs.zStart &&
               zEnd == rhs.zEnd;
    }

    bool operator!=(const Paralelepiped &rhs) const {
        return !(rhs == *this);
    }
};

std::list<Paralelepiped> space;

void toggle_emplace(Paralelepiped &p, bool isOn) {
    std::list<Paralelepiped *> intersections;
    for (auto &s: space) {
        if (s.isIntersects(p)) {
       //     std::cout << (isOn ? "On ": "Off ") << p << " intersects with: " << s << " == " << s.intersection(p) << std::endl;
            intersections.push_back(&s);
        }
    }
    if (isOn) {  // Split source cube
        std::list<Paralelepiped> pieces;
        pieces.push_back(p);
        for (auto ic: intersections) {
again:
            for (auto &piece : pieces) {
                if (piece.isIntersects(*ic)) {
                    auto tmp = piece.split_subtract(ic->intersection(piece));
                    pieces.insert(pieces.end(), tmp.begin(), tmp.end());
                    pieces.remove(piece);
                    goto again;
                }
            }
        }
        space.insert(space.end(), pieces.begin(), pieces.end());
    } else {
        for (auto ic: intersections) {
            auto tmp = ic->split_subtract(ic->intersection(p));
            space.remove(*ic);
            space.insert(space.end(), tmp.begin(), tmp.end());
        }
    }
}

int main(int argc, char *argv[]) {
    std::fstream f(argv[1]);
    std::string line;

    if (!f.good()) {
        std::cerr << "File open error";
        return 1;
    }

    while (f >> line) {
        int x1, x2, y1, y2, z1, z2;
        bool isOn = line == "on";
        f >> line;
        sscanf(line.c_str(), "x=%d..%d,y=%d..%d,z=%d..%d", &x1, &x2, &y1, &y2, &z1, &z2);
        Paralelepiped c{x1, x2 + 1, y1, y2 + 1, z1, z2 + 1};

        toggle_emplace(c, isOn);
    }

    f.close();

    unsigned long sum = 0;
    std::for_each(space.begin(), space.end(), [&sum](auto &s) {
        sum += s.volume();
    });
    std::cout << "Volume: " << sum << std::endl;

    return 0;
}