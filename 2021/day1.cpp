#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include <vector>
#include <numeric>

template <class T> class MovingSum {
public:
    MovingSum(std::initializer_list<T> init) : values(init) {
    }

    void append(T newVal) {
        values.erase(values.begin());
        values.push_back(newVal);
    }

    T sum() {
        return std::accumulate(values.begin(), values.end(), 0);
    }
private:
    std::vector<T> values;
};


static int nextMeasurement(std::ifstream &f) {
    std::string line;
    int value = -1;
    if (f >> line) {
        std::istringstream(line) >> value;
    }
    return value;
}

static void part_one(const std::string &fn) {
    std::ifstream f(fn);
    std::string line;
    int head;
    int prev_head = std::numeric_limits<int>::max();
    unsigned count = 0;
    while((head = nextMeasurement(f)) != -1) {
        if (head > prev_head) {
            count++;
        }
        prev_head = head;
    }

    f.close();
    std::cout << "Increase Count:" << count << std::endl;
}

static void part_two(const std::string &fn) {
    std::ifstream f(fn);
    int count = 0;
    MovingSum<int> m({nextMeasurement(f), nextMeasurement(f), nextMeasurement(f)});
    int prev_head = m.sum();
    int head;

    while ((head = nextMeasurement(f)) != -1) {
        m.append(head);
        if (m.sum() > prev_head) {
            count++;
        }
        prev_head = m.sum();
    }

    f.close();
    std::cout << "Window increases count: " << count <<std::endl;
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[]) {
    part_one("day1.input");
    part_two("day1.input");
    return 0;
}