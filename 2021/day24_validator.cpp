#include <iostream>

int main(int argc, char *argv[]) {
    for (int c0 = 9; c0 > 0; c0--) {
/*
        inp w     # w = c0
        mul x 0   # x = 0
        add x z   # x = 0
        mod x 26  # x = 0
        div z 1   # z = 0
        add x 11  # x = 11
        eql x w   # x = c0 == 11 -> (0)
        eql x 0   # X1 = 1
        mul y 0   # y = 0
        add y 25  # y = 25
        mul y x   # y = 25
        add y 1   # y = 26
        mul z y   # z = 0
        mul y 0   # y = 0
        add y w   # y = c0
        add y 7   # y = c0+7
        mul y x   # Y1 = c0+7
        add z y   # Z1 = c0+7
*/
        auto x1 = 1;
        auto y1 = c0 + 7;
        auto z1 = c0 + 7;

        for (int c1 = 9; c1 > 0; c1--) {

            auto x2 = x1;
            auto y2 = c1 + 8;
            auto z2 = y1 * 26  + c1 + 8;

            for (int c2 = 9; c2 > 0; c2--) {
                auto x3 = ;
                auto y3 = ;
                auto z3 = ;

                for (int c3 = 9; c3 > 0; c3--) {
                    auto x4 = x;
                    auto y4 = y;
                    auto z4 = z;

                    for (int c4 = 9; c4 > 0; c4--) {
                        auto x5 = x;
                        auto y5 = y;
                        auto z5 = z;

                        for (int c5 = 9; c5 > 0; c5--) {
                            auto x6 = x;
                            auto y6 = y;
                            auto z6 = z;

                            for (int c6 = 9; c6 > 0; c6--) {
                                auto x7 = x;
                                auto y7 = y;
                                auto z7 = z;

                                for (int c7 = 9; c7 > 0; c7--) {
                                    auto x8 = x;
                                    auto y8 = y;
                                    auto z8 = z;

                                    for (int c8 = 9; c8 > 0; c8--) {
                                        auto x9 = x;
                                        auto y9 = y;
                                        auto z9 = z;

                                        for (int c9 = 9; c9 > 0; c9--) {
                                            auto x10 = x;
                                            auto y10 = y;
                                            auto z10 = z;

                                            for (int c10 = 9; c10 > 0; c10--) {
                                                auto x11 = x;
                                                auto y11 = y;
                                                auto z11 = z;

                                                for (int c11 = 9; c11 > 0; c11--) {
                                                    auto x12 = x;
                                                    auto y12 = y;
                                                    auto z12 = z;

                                                    for (int c12 = 9; c12 > 0; c12--) {
                                                        auto x13 = x;
                                                        auto y13 = y;
                                                        auto z13 = z;

                                                        for (int c13 = 9; c13 > 0; c13--) {

                                                            if (z == 0) {
                                                                std::cout << c0 << c1 << c2 << c3 << c4 << c5 << c6 << c7 << c8 << c9 << c10 << c11 << c12 << c13 << std::endl;
                                                                return 0;
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return 0;
}