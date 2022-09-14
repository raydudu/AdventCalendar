#include <fstream>
#include <iostream>
#include <vector>
#include <string>

struct Point {
    int x;
    int y;
    int z;

    [[nodiscard]] Point permute(const unsigned level) const { // 1 to 48 inclusive
        int arr[] = {x, y, z};

        if (level >> 3) {
            int p[] = {0, 0, 0};

            int i = 1;
            int j = 0;
            int pc = 0;

            while (i < 3) {
                if (p[i] < i) {
                    j = (i % 2) * p[i];

                    std::swap(arr[j], arr[i]);

                    if (++pc == level >> 3) {
                        break;
                    }

                    p[i]++;
                    i = 1;
                } else {
                    p[i] = 0;
                    i++;
                }
            }
        }

        for (int i = 0; i < 3; i++) {
            if (level & (0x1 << i)) {
                arr[i] = -arr[i];
            }
        }

        return Point{arr[0], arr[1], arr[2]};
    }

    bool operator==(const Point &rhs) const {
        return std::tie(x, y, z) == std::tie(rhs.x, rhs.y, rhs.z);
    }
    bool operator<(const Point &rhs) const {
        return std::tie(x, y, z) < std::tie(rhs.x, rhs.y, rhs.z);
    }

    bool operator!=(const Point &rhs) const {
        return !(rhs == *this);
    }

    Point operator-(const Point &rhs) const {
        return Point{x - rhs.x, y - rhs.y, z - rhs.z};
    }

    Point& operator=(const Point &rhs) = default;

    Point operator+(const Point &rhs) const{
        return Point{x + rhs.x, y + rhs.y, z + rhs.z};
    }

    friend std::ostream &operator<<(std::ostream &os, const Point &point) {
        os << "{" << point.x << "," << point.y << "," << point.z << "}";
        return os;
    }
};

struct Scanner {
    std::vector<Point> beacons;
    Point relativePos;
    int orientation;

    bool relativeTo(Scanner &to) {
        for (auto &their : to.beacons) {
            for (int p = 1; p <= 48; p++) {
                auto perm = their.permute(p);
                for (auto &own : beacons) {
                    Point rel = own - perm;
                    int matches = 0;
                    for (auto &ct: to.beacons) {
                        matches += std::find(beacons.begin(), beacons.end(),  ct.permute(p) + rel) != beacons.end();
                    }
                    if (matches >= 12) {
                        std::cout << "Offset: " << rel << " m: " << matches << " perm: " << p << std::endl;
                        to.relativePos = rel;
                        to.orientation = p;
                        return true;
                    }
                }
            }
        }
        return false;
    }

    void merge(Scanner &src) {
        for (auto &b: src.beacons) {
            auto nb = b.permute(src.orientation) + src.relativePos;
            auto idx = std::find(beacons.begin(), beacons.end(), nb);
            if (idx == beacons.end()) {
//                std::cout << "MATCH" << nb << std::endl;
                beacons.emplace_back(nb);
            }
        }
        src.beacons.clear();
    }
};

int main(int argc, char *argv[]) {
    std::vector<Scanner> scanners;
    std::ifstream f("day19.input");
    std::string line;

    if (!f.good()) {
        std::cerr << "File read error" << std::endl;
        return 1;
    }

    while (f >> line) {
        if (line.rfind("---") != std::string::npos) {
            scanners.emplace_back(Scanner{});
            f >> line;
            f >> line;
            f >> line;
            continue;
        }
        Point p{0,0,0};
        sscanf(line.c_str(), "%d,%d,%d", &p.x, &p.y, &p.z);
        scanners.back().beacons.emplace_back(p);
    }

    f.close();

#if 0
    Point tp = { 2, 3, 1};
    for (int p = 0; p <= 49; p++) {
        //if ( p % 8 == 0)
        std::cout << p << " " << tp.permute(p) << std::endl;
    }
    return 0;
#endif

    auto s0 = scanners.begin();
again:
    for (auto s = s0 + 1; s != scanners.end(); s++) {
        if (s->beacons.empty()) {
            continue;
        }
        if (s0->relativeTo(*s)) {
            std::cout << "Scanner " << s0 - scanners.begin() << " relative to " << s - scanners.begin() << std::endl;
            s0->merge(*s);
            goto again;
        }
    }
    std::cout << "P1: " << s0->beacons.size() << std::endl;

    unsigned max_dist = 0;
    for (auto &x : scanners) {
        for (auto &y: scanners) {
            auto dist = std::abs(x.relativePos.x - y.relativePos.x) + std::abs(x.relativePos.y - y.relativePos.y) +
                    std::abs(x.relativePos.z - y.relativePos.z);
            if (dist > max_dist) {
                max_dist = dist;
            }
        }
    }
    std::cout << "P2: " << max_dist << std::endl;
    return 0;
}
