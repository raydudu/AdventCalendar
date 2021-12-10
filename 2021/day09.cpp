#include <fstream>
#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <numeric>
#include <queue>


static const std::vector offs{
        std::pair(1, 0),
        std::pair(-1, 0),
        std::pair(0, 1),
        std::pair(0, -1)
};

#if 1
unsigned int basin_size(std::vector<std::string> &map, bool *visit, std::pair<int, int> dim, std::pair<int, int> p) {

    if (visit[p.first + p.second * dim.first] || map[p.second].c_str()[p.first] == 9) {
        return 0;
    }

    unsigned int size = 1;
    visit[p.first + p.second * dim.first] = true;

    for(auto &o: offs) {
        std::pair np = {p.first + o.first, p.second + o.second};
        if (np.first >= 0 && np.first < dim.first && np.second >= 0 && np.second < dim.second ) {
            size += basin_size(map, visit, dim, np);
        }
    }

    return size;
}
#else
unsigned int basin_size(std::vector<std::string> &map, bool *visited, std::pair<int, int> dim, std::pair<int, int> point) {
    std::queue<typeof(point)> q;

    q.emplace(point);
    int size = 0;

    while (!q.empty()) {
        auto p = q.front();
        q.pop();

        if (visited[p.first + p.second * dim.first]) {
            continue;
        }

        visited[p.first + p.second * dim.first] = true;
        size++;
        for(auto &o: offs) {
            std::pair np = {p.first + o.first, p.second + o.second};
           if (np.first >= 0 && np.first < dim.first && np.second >= 0 && np.second < dim.second ) {
               if (map[np.second].c_str()[np.first] != 9) {
                   q.push(np);
               }
           }
        }
    }

    return size;
}
#endif

int main(int argc, char *argv[]) {
    std::ifstream f("day09.input");
    std::string word;
    std::vector<std::string> map;
    unsigned riskpoint_cnt = 0;
    unsigned basin_area;

    if (!f.good()) {
        std::cerr << "File open error";
        return 1;
    }

    while (f >> word) {
        if (word.length() == 0) {
            continue;
        }
        std::transform(word.begin(), word.end(), word.begin(),
                       [](auto c) -> auto { return  c - '0';});
        map.push_back(word);
    }

    auto w = map[0].length();
    auto h = map.size();
    std::vector<unsigned> areas;
    bool visited[w * h];

    std::memset(visited, 0, sizeof visited);

    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            char p = map[y].c_str()[x];

            if ((x == 0 || (map[y].c_str()[x - 1] > p)) &&
                (x == w - 1 || (map[y].c_str()[x + 1] > p)) &&
                (y == 0 || (map[y - 1].c_str()[x] > p)) &&
                (y == h - 1 || (map[y + 1].c_str()[x] > p)))  {
                riskpoint_cnt += p + 1;
            }

            if (p != 9 && !visited[x + y * w]) {
                auto a = basin_size(map, visited, {w, h}, {x, y});
                if (a > 1) {
                    areas.push_back(a);
                }
            }
        }
    }

    std::cout << "P1 risk: " << riskpoint_cnt << std::endl;

    std::sort(areas.begin(), areas.end());
    basin_area = std::accumulate(areas.rbegin(), areas.rbegin() + 3, 1U, std::multiplies<>());
    std::cout << "P2 area: " << basin_area << std::endl;

    return 0;
}