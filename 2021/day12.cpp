#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <iostream>
#include <queue>
#include <algorithm>


int traverse(std::map<std::string, std::vector<std::string>> &map, bool dvisit) {
    auto start = map.find("start");
    int paths = 0;
    std::queue<std::pair<typeof start, std::vector<std::string>>> q;

    q.push(std::pair{start, std::vector<std::string>()});
    q.front().second.emplace_back("start");

    while(!q.empty()) {
        auto node = q.front();
        q.pop();

        if (node.first->first == "end") {
            paths++;
            continue;
        }

        for (auto &child: node.first->second) {
            if (std::find(node.second.begin(), node.second.end(), child) == node.second.end()) {
                if (child != "end" && std::tolower(child[0]) == child[0]) {
                    std::vector<std::string> small(node.second);
                    small.emplace_back(child);
                    q.push({map.find(child), small});
                } else {
                    q.push({map.find(child), node.second});
                }
            } else if (dvisit && child != "start" && child != "end" &&
                    std::find(node.second.begin(), node.second.end(), "~") == node.second.end()) {
                std::vector<std::string> small(node.second);
                small.emplace_back("~");
                q.push({map.find(child), small});
            }
        }
    }

    return paths;
}

int main(int argc, char *argv[]) {
    std::map<std::string, std::vector<std::string>> map;
    std::ifstream f("day12.input");
    std::string word;

    if (!f.good()) {
        std::cerr << "File open error" << std::endl;
        return 1;
    }

    while(f >> word) {
        auto div = word.find('-');
        auto src = word.substr(0, div);
        auto dst = word.substr(div + 1);

        auto node = map.find(src);
        if (node == map.end()) {
            std::vector<std::string> child{dst};
            map.emplace(src, child);

        } else {
            node->second.emplace_back(dst);
        }

        node = map.find(dst);
        if (node == map.end()) {
            std::vector<std::string> child{src};
            map.emplace(dst, child);
        } else {
            node->second.emplace_back(src);
        }
    }

    std::for_each(map.begin(), map.end(), [](auto &m) {
       std::cout << "Key: " << m.first << " -> ";
       std::for_each(m.second.begin(), m.second.end(), [](auto &s){
           std::cout << s << ", ";
       });
       std::cout << std::endl;
    });

    std::cout << "P1: " << traverse(map, false) << std::endl;
    std::cout << "P2: " << traverse(map, true) << std::endl;

    return 0;
}