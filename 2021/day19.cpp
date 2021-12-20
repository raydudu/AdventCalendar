#include <fstream>
#include <iostream>
#include <vector>
#include <string>

struct Point {
    int x;
    int y;
    int z;

    Point permute(const unsigned level) {
        assert( 1 <= level && level <= 48);
        int arr[] = {x, y, z};

        if (level >> 3) {
            std::sort(arr, arr + 2);
            for (int i = 0; i < (level >> 3); i++) {
                std::next_permutation(arr, arr + 2);
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
        return x == rhs.x &&
               y == rhs.y &&
               z == rhs.z;
    }

    bool operator!=(const Point &rhs) const {
        return !(rhs == *this);
    }

    Point operator-(const Point &rhs) const{
        return Point{x - rhs.x, y - rhs.y, z - rhs.z};
    }

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
    Point rel0{0,0,0};

    bool isRelativeTo(const Scanner &s) {
        for (auto &j : s.beacons) {
            for (auto & i : beacons) {
                Point rel = j + i;
                std::cout << j << " - " << i << " = " << rel << std::endl;
/*
                int match = 0;
                for (auto &own: beacons) {
                    for (auto &their: s.beacons ) {
                        if (own + rel ==  their) {
                            match++;
                        }
                    }
                }
                if (match != 0) {
                    std::cout << match << std::endl;
                }
*/
            }
        }
        return false;
    }
};

int main(int argc, char *argv[]) {
    std::vector<Scanner> scanners;
    std::ifstream f("day19_ex.input");
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

    scanners[0].isRelativeTo(scanners[1]);

    f.close();
    return 0;
}
