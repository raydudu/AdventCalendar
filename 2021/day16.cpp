#include <climits>
#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <numeric>


//static unsigned char test[] = {0xD2, 0xFE, 0x28};
//static unsigned char test[] = {0x38, 0x00, 0x6F, 0x45, 0x29, 0x12, 0x00};
//static unsigned char test[] = {0xEE, 0x00, 0xD4, 0x0C, 0x82, 0x30, 0x60};
//static unsigned char test[] = {0x8A, 0x00, 0x4A, 0x80, 0x1A, 0x80, 0x02, 0xF4, 0x78};
//static unsigned char test[] = {0x62, 0x00, 0x80, 0x00, 0x16, 0x11, 0x56, 0x2C, 0x88,0x02, 0x11, 0x8E, 0x34};
//static unsigned char test[] = {0xC0, 0x01, 0x50, 0x00, 0x01, 0x61, 0x15, 0xA2, 0xE0, 0x80, 0x2F, 0x18, 0x23, 0x40};
static unsigned char test[] = {0xA0, 0x01, 0x6C, 0x88, 0x01, 0x62, 0x01, 0x7C, 0x36, 0x86, 0xB1, 0x8A, 0x3D, 0x47, 0x80};

class BitStream {
public:
    BitStream(unsigned char *data, unsigned long len) : data(data), len(len * CHAR_BIT), pos(0), mark(0) {
    }

    unsigned long pull(unsigned bitnr) {
        unsigned long ret = 0;
        for (int b = 0; b < bitnr; b++) {
            ret <<= 1;
            ret |= !!(data[pos / 8] & 1 << (7 - (pos & 0x07)));
            pos++;
        }
        return ret;
    }

    [[nodiscard]] bool eos() const {
        return len - pos < 8;
    }

    void makeMark() {
        mark = pos;
    };

    [[nodiscard]] unsigned long measure() const {
        return pos - mark;
    }

private:
    unsigned char *data;
    unsigned long len;
    unsigned long pos;
    unsigned long mark;
};

struct bracket {
    bool bits;
    unsigned count;
    unsigned taken_bits;
    int op;
    std::vector<unsigned long> literals;
};


int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[]) {
    std::list<bracket> grp;
    unsigned long version = 0;
    unsigned long result;

#if 0
    BitStream b(test, sizeof test);
#else
    std::ifstream f("day16.input");
    std::string line;
    f >> line;
    f.close();

    unsigned char data[line.length() / 2];

    for (int i = 0; i < line.length(); i+=2) {
        std::string nr{{line[i], line[i + 1]}};
        data[i/2] = (unsigned char)std::stoul(nr, nullptr, 16);
    }
    BitStream b{data, sizeof data};

#endif
    while (!b.eos()) {
        b.makeMark();
        version += b.pull(3);
        char tag = (char)b.pull(3);
        if (tag == 4) { // literal
            bool  isLast;
            unsigned long literal = 0;
            do {
                isLast = b.pull(1);
                literal <<= 4;
                literal |= b.pull(4);
            } while (isLast);
            std::cout << literal << " ";
            if (!grp.empty()) {
                grp.back().literals.emplace_back(literal);
            }
        } else { //operator
            unsigned length = b.pull(1);
            if (length) {
                length = b.pull(11);
                std::cout << "(";
                grp.emplace_back(bracket{false, length + 1, 0, tag, {}});
            } else {
                length = b.pull(15);
                std::cout << "(";
                grp.emplace_back(bracket{true, length + 15 + 1 + 3 + 3, 0, tag, {}});
            }
        }
        if (!grp.empty()) {
            auto m = b.measure();
            bool discarded = false;
            do {
                auto &g = grp.back();
                if (discarded) {
                    g.literals.push_back(result);
                }
                discarded = false;

                if (g.bits) {
                    g.count -= m;
                } else {
                    g.count--;
                }
                g.taken_bits += m;

                if (g.count == 0) {
                    switch (g.op) {
                        case 0:
                            std::cout << "+";
                            result = std::accumulate(g.literals.begin(), g.literals.end(), 0UL);
                            break;
                        case 1:
                            std::cout << "*";
                            result = std::accumulate(g.literals.begin(), g.literals.end(), 1UL, std::multiplies());
                            break;
                        case 2:
                            std::cout << "m";
                            result = *std::min_element(g.literals.begin(), g.literals.end());
                            break;
                        case 3:
                            std::cout << "M";
                            result = *std::max_element(g.literals.begin(), g.literals.end());
                            break;
                        case 5:
                            std::cout << ">";
                            assert(g.literals.size() == 2);
                            result = g.literals[0] > g.literals[1];
                            break;
                        case 6:
                            std::cout << "<";
                            assert(g.literals.size() == 2);
                            result = g.literals[0] < g.literals[1];
                            break;
                        case 7:
                            std::cout << "=";
                            assert(g.literals.size() == 2);
                            result = g.literals[0] == g.literals[1];
                            break;

                    }
                    m = g.taken_bits;
                    grp.pop_back();
                    std::cout << ")";
                    discarded = true;
                }
            } while (!grp.empty() && discarded);

        }
    }
    std::cout << std::endl;

    std::cout << "P1 versum: " << version << std::endl;
    std::cout << "P2 result: " << result << std::endl;

    return 0;
}
