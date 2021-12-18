#include <iostream>
#if 0
int target_x1 = 20;
int target_x2 = 30;
int target_y1 = -10;
int target_y2 = -5;
#else
int target_x1 = 56;
int target_x2 = 76;
int target_y1 = -162;
int target_y2 = -134;
#endif
//int ovx_min = 1000000;
//int ovx_max = -1;
//int ovy_min = 1000000;
//int ovy_max = -1000000;

int ymax = 0;
unsigned count = 0;

void simulate(int vx, int vy) {
    int x = 0;
    int y = 0;
    int lmax = 0;
//    auto ovx = vx;
//    auto ovy = vy;

    while (x <= target_x2 && y > target_y1) {
        x += vx;
        y += vy;

        if (y > lmax) {
            lmax = y;
        }
        if (target_x1 <= x && x <= target_x2 && target_y1 <= y && y <= target_y2) {
            ymax = std::max(lmax, ymax);
//            ovx_max = std::max(ovx, ovx_max);
//            ovx_min = std::min(ovx, ovx_min);
//            ovy_max = std::max(ovy, ovy_max);
//            ovy_min = std::min(ovy, ovy_min);
            count++;
            break;
        }
        if (vx > 0) {
            vx -= 1;
        }
        vy -= 1;
    }
}


int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[]) {
    for (int vx = 0; vx <= target_x2; vx++) {
        for (int vy = target_y1; vy <= -target_y1 - 1; vy++) {
            simulate(vx, vy);
        }
    }

    std::cout << "P1 ymax: " << ymax << std::endl;
    std::cout << "P2 count: " << count << std::endl;
    return 0;
}