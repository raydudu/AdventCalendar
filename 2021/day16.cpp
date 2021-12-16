
#include <climits>
#include <iostream>

static unsigned char test1[] = {0x8A, 0x00, 0x4A, 0x80, 0x1A, 0x80, 0x02, 0xF4, 0x78};

class BitStream {
public:
    BitStream(unsigned char *data, unsigned long len) : data(data), len(len * CHAR_BIT), pos(0) {
    }
    unsigned pull(unsigned bitnr) {
        unsigned ret = 0;
        for (int b = 0; b < bitnr; b++) {
            ret <<= 1;
            ret |= !!(data[pos / 8] & 1 << (7 - (pos & 0x07)));
            pos++;
        }
        return ret;
    }
    bool eos() {
        return pos == len;
    }
    void padd4() {
        if (pos & 0x3) {
            pos += 4 - (pos & 0x3);
        }
    }

private:
    unsigned char *data;
    unsigned long len;
    unsigned pos;
};

int main(int argc, char *argv[]) {

    BitStream b(test1, sizeof test1);


    while (!b.eos()) {
        auto version = b.pull(3);
        auto tag = b.pull(3);
        if (tag == 4) { // literal
            bool  isLast;
            do {
                isLast = b.pull(1);
                auto nible = b.pull(4);
            } while (isLast);
        } else { //operator
            auto length = b.pull(1);
            if (length) {
                length = b.pull(11);
            } else {
                length = b.pull(15);
            }

        }

        b.padd4();
    }
    return 0;
}
