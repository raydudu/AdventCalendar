
#include <fstream>
#include <iostream>

template <class T, unsigned size_x, unsigned size_y> class Grid {
public:
    void toggle(unsigned x, unsigned y) {
        grid[y * size_x + x] = !grid[y * size_x + x];
    }
    void toggle(unsigned x, unsigned y, unsigned x1, unsigned y1) {
        for (unsigned i = x; i <= x1; i++) {
            for(unsigned j = y; j <= y1; j++) {
                toggle(i, j);
            }
        }
    }

    void set(unsigned x, unsigned y, T &val) {
        grid[y * size_x +x] = val;
    }

    void set(unsigned x, unsigned y, unsigned x1, unsigned y1, T val) {
        for (unsigned i = x; i <= x1; i++) {
            for(unsigned j = y; j <= y1; j++) {
                set(i, j, val);
            }
        }
    }

    void add(unsigned x, unsigned y, T &val) {
        grid[y * size_x +x] += val;
    }

    void add(unsigned x, unsigned y, unsigned x1, unsigned y1, T val) {
        for (unsigned i = x; i <= x1; i++) {
            for(unsigned j = y; j <= y1; j++) {
                add(i, j, val);
            }
        }
    }

    void dec(unsigned x, unsigned y, T &val) {
        if (val > grid[y * size_x + x]) {
            grid[y * size_x + x] = 0;
        } else {
            grid[y * size_x + x] -= val;
        }
    }

    void dec(unsigned x, unsigned y, unsigned x1, unsigned y1, T val) {
        for (unsigned i = x; i <= x1; i++) {
            for(unsigned j = y; j <= y1; j++) {
                dec(i, j, val);
            }
        }
    }


    unsigned total() {
        unsigned count = 0;
        for(unsigned i = 0; i < size_y * size_x; i++) {
            count += grid[i];
        }
        return count;
    }

    void display() {
        for(unsigned i = 0; i < size_y * size_x; i++) {
            if (i % size_x == 0) {
                std::cout << std::endl;
            }
            std::cout << (grid[i] ? '*' : 'O');
        }

    }

private:
    T grid[size_x * size_y] = {0, };
};

enum actions {
    ON,
    OFF,
    TOGGLE
};

//#define TEST

#ifdef TEST
int main(int argc, char *argv[]) {
    Grid<bool, 10, 10> g;
    g.set(0, 0, 2, 2, true);
   // g.set(0, 0, 9, 9, true);
   // g.set(0, 0, 9, 0, true);
   // g.set(4, 4, 5, 5, true);
    g.display();

    return 0;
}
#else
int main(int argc, char *argv[]) {
    std::ifstream f("day6.input");
    std::string line;
    actions act;
    Grid<bool, 1000, 1000> leds{};
    Grid<unsigned, 1000, 1000> aleds{};
    unsigned x,y,x1,y1;
    int stage = 0;

    while (f >> line) {
        if (stage == 0) {
            if (line == "turn") {
                continue;
            }
            if (line == "on") {
                act = ON;
            } else if (line == "off") {
                act = OFF;
            } else if (line == "toggle") {
                act = TOGGLE;
            } else {
                std::cout << "Unknown action: " << act << std::endl;
                exit(1);
            }
            stage = 1;
            continue;
        } else if (stage == 1) {
            x = std::stoi(line);
            auto pos = line.find(',');
            y = std::stoi(line.substr(pos + 1));
            stage = 2;
            continue;
        } else if (stage == 2) {
            if (line != "through") {
                std::cout << "Coords parse error: " << line << std::endl;
                exit(1);
            }
            stage = 3;
            continue;
        } else if (stage == 3) {
            x1 = std::stoi(line);
            auto pos = line.find(',');
            y1 = std::stoi(line.substr(pos + 1));
            stage = 0;

            // Parse complete
            switch (act) {
                case ON:
                    leds.set(x,y,x1,y1, true);
                    aleds.add(x,y,x1,y1, 1);
                    break;
                case OFF:
                    leds.set(x,y,x1,y1, false);
                    aleds.dec(x,y,x1,y1, 1);
                    break;
                case TOGGLE:
                    leds.toggle(x,y,x1,y1);
                    aleds.add(x,y,x1,y1, 2);
                    break;
            }
            std::cout << "Do: " << act << " (" << x << ", " << y << ") -> (" << x1 << ", " << y1 << ")"
                      << std::endl;
        }
    }

    f.close();

    std::cout << "P1: Number of leds on: " << leds.total() << std::endl;
    std::cout << "P2: Number of analog leds on: " << aleds.total() << std::endl;

    return 0;
}
#endif