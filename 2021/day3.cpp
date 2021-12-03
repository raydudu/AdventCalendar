

#include <fstream>
#include <iostream>
#include <vector>
#if 0
static const auto bitnr = 5;
static const auto fn = "day3_ex.input";
#else
static const auto bitnr = 12;
static const auto fn = "day3.input";
#endif

static void count_part2(std::vector<unsigned int> &bytes) {
    int bitpos = bitnr - 1;
    unsigned mask = 0;
    unsigned oxygen_filter = 0;
    unsigned co2_filter = 0;
    unsigned oxygen_last;
    unsigned co2_last;

    while (bitpos >= 0) {
        int one_cnt = 0;
        int oxygen_count = 0;

        int zero_cnt = 0;
        int co2_count = 0;

        for (auto &b: bytes) {
            if ((b & mask) == oxygen_filter) {
                oxygen_count++;
                if ((b >> bitpos) & 0x01) {
                    one_cnt++;
                    oxygen_last = b;
                }
            }
            if ((b & mask) == co2_filter) {
                co2_count++;
                if (((b >> bitpos) & 0x1) == 0) {
                    zero_cnt++;
                    co2_last = b;
                }
            }
        }
        if (one_cnt == 1) {
            std::cout << "Oxygen rating: " << oxygen_last << std::endl;
        } else {
            if (one_cnt >= oxygen_count - one_cnt) {
                oxygen_filter |= 0x1 << bitpos;
            }
        }
        if (zero_cnt == 1) {
            std::cout << "CO2 rating: " << co2_last << std::endl;
        } else {
            if (zero_cnt > co2_count - zero_cnt) {
                co2_filter |= 0x1 << bitpos;
            }
        }
        mask |= 0x01 << bitpos;
        bitpos--;
    }
    std::cout << "P2 result: " << oxygen_last * co2_last << std::endl;
}

int main(int argc, char *argv[]) {
    std::ifstream f(fn);
    std::string line;
    std::vector<unsigned> bytes;
    unsigned one_cnt[bitnr] = {0, };
    while(f >> line) {
        unsigned byte = std::stoul(line, nullptr, 2);
        bytes.push_back(byte);

        for(int pos = 0; byte != 0; pos++, byte >>=1) {
            if (byte & 0x01) {
                one_cnt[pos]++;
            }
        }
    }
    f.close();

    std::cout << "Total bytes: " << bytes.size() << std::endl;
    std::cout << "OnesCount(gamma:" << std::endl;
    unsigned gamma = 0;
    unsigned epsilon = 0;
    for(int pos = bitnr - 1; pos >= 0; pos-- ) {
        std::cout << (one_cnt[pos] > bytes.size() / 2) << "";
        gamma <<= 1;
        epsilon <<= 1;
        if (one_cnt[pos] > bytes.size() / 2) {
            gamma |= 0x1;
        } else {
            epsilon |= 0x1;
        }
    }
    std::cout << std::endl << "Gamma: " << gamma << ", Epsilon: " << epsilon << std::endl;
    std::cout << "P1 result: " << gamma * epsilon << std::endl << std::endl;

    count_part2(bytes);
    return 0;
}