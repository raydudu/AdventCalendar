
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <iostream>
#include <algorithm>

struct dim_t {
    int l;
    int w;
    int h;
};


static void part_one(const std::vector<dim_t> &dim) {
    long area_ft = 0;
    for (dim_t d: dim) {
//        std::cout << d.l << "*" << d.w << "*" << d.h << std::endl;
        area_ft += 2 * d.l * d.w + 2 * d.w * d.h + 2 * d.h * d.l + std::min({d.l * d.w, d.w * d.h, d.h * d.l});
    }

    std::cout << "P1: Total Area: " << area_ft << std::endl;
}

static void part_two(const std::vector<dim_t> &dim) {
    long ribbon_ft = 0;

    for(dim_t d: dim) {
        int wrap_ft = std::min({d.w * 2 + d.l * 2, d.w  * 2 + d.h * 2, d.l * 2 + d.h * 2});
        int bow_ft = d.w * d.h * d.l;
        ribbon_ft += wrap_ft + bow_ft;
    }

    std::cout << "P2: Total Ribbon len: " << ribbon_ft << std::endl;
}

int main(int argc, char *argv[]) {
    std::vector<dim_t> dim;
    std::string line;
    std::ifstream f("day2.input");
    while (f >> line) {
        std::istringstream d(line);
        char tmp;
        dim_t nd{};
        d >> nd.l;
        d.get(tmp);
        d >> nd.w;
        d.get(tmp);
        d >> nd.h;
        dim.emplace_back(nd);
    }
    f.close();

    part_one(dim);
    part_two(dim);

   // std::vector<dim_t> test_dim({dim_t{2,3,4}, dim_t{1,1,10}});
   // part_two(test_dim);

    return 0;
}