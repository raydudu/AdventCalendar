#include <list>
#include <string>
#include <iostream>
#include <cmath>
#include <stack>
#include <fstream>
#include <vector>

//#define TEST

#pragma clang diagnostic push
#pragma ide diagnostic ignored "LocalValueEscapesScope"

#ifdef TEST
static const std::string tests[] = {
        "[1,2]",
        "[[1,2],3]",
        "[9,[8,7]]",
        "[[1,9],[8,5]]",
        "[[[[1,2],[3,4]],[[5,6],[7,8]]],9]",
        "[[[9,[3,8]],[[0,9],6]],[[[3,7],[4,9]],3]]",
        "[[[[1,3],[5,3]],[[1,3],[8,7]]],[[[4,9],[6,9]],[[8,2],[7,3]]]]",
};
static const std::string test_explode[] = {
        "[[[[[9,8],1],2],3],4]",
        "[7,[6,[5,[4,[3,2]]]]]",
        "[[6,[5,[4,[3,2]]]],1]",
        "[[3,[2,[1,[7,3]]]],[6,[5,[4,[3,2]]]]]",
};

static const std::string test_plus[]  = {
        "[1,1]",
        "[2,2]",
        "[3,3]",
        "[4,4]",
        "[5,5]",
        "[6,6]",
};

static const std::string test_plus2[] = {
        "[[[0,[4,5]],[0,0]],[[[4,5],[2,6]],[9,5]]]",
        "[7,[[[3,7],[4,3]],[[6,3],[8,8]]]]",
        "[[2,[[0,8],[3,4]]],[[[6,7],1],[7,[1,6]]]]",
        "[[[[2,4],7],[6,[0,5]]],[[[6,8],[2,8]],[[2,1],[4,5]]]]",
        "[7,[5,[[3,8],[1,4]]]]",
        "[[2,[2,2]],[8,[8,1]]]",
        "[2,9]",
        "[1,[[[9,3],9],[[9,0],[0,7]]]]",
        "[[[5,[7,4]],7],1]",
        "[[[[4,2],2],6],[8,7]]",
};
static const std::string test_mag[] = {
        "[9,1]",
        "[[9,1],[1,9]]",
        "[[1,2],[[3,4],5]]",
        "[[[[0,7],4],[[7,8],[6,0]]],[8,1]]",
        "[[[[1,1],[2,2]],[3,3]],[4,4]]",
        "[[[[3,0],[5,3]],[4,4]],[5,5]]",
        "[[[[5,0],[7,4]],[5,5]],[6,6]]",
        "[[[[8,7],[7,7]],[[8,6],[7,7]]],[[[0,7],[6,6]],[8,7]]]",
};
#endif

class SnailFishNumber {
public:
    explicit SnailFishNumber(const std::string &n) {
        num_node *curr;
        root = nullptr;

        for (unsigned i = 0; i < n.size(); i++) {
            if (n[i] == '[') {
                if (root == nullptr) {
                    root = new num_node(-1);
                    curr = root;
                } else {
                    auto p = curr;
                    if (curr->l != nullptr) {
                        curr = curr->new_r(-1);
                    } else {
                        curr = curr->new_l(-1);
                    }
                    curr->p = p;
                }
            } else if (n[i] == ']') {
                curr = curr->p;
            } else if (n[i] == ',') {
            } else {
                size_t pos = 0;
                auto a = std::stoi(n.c_str() + i, &pos);
                i += pos - 1;
                if (curr->l != nullptr) {
                    assert(curr->r == nullptr);
                    curr->new_r(a);
                } else {
                    curr->new_l(a);
                }
            }
        }
    }

    SnailFishNumber(SnailFishNumber &&s)  noexcept {
        this->root = s.root;
        s.root = nullptr;
    }

    SnailFishNumber &operator=(SnailFishNumber &&s)  noexcept {
        if (this != &s) {
            destroy();
            this->root = s.root;
            s.root = nullptr;
        }

        return *this;
    }

    virtual ~SnailFishNumber() {
        destroy();
    }

    int magnitude() {
        return magnitude(root);
    }

    bool explode() {
        std::pair<int, num_node *> curr{0, root};
        std::stack<std::pair<int, num_node *>> s;
        num_node *prev = nullptr;
        int post = -1;

        while (curr.second != nullptr || !s.empty()) {
            while (curr.second != nullptr) {
                s.push(curr);
                curr = std::make_pair(curr.first + 1, curr.second->l);
            }

            if (curr.second == nullptr) {
                curr = s.top();
                s.pop();
            }

            if (curr.second->n == -1) {
                if (curr.first == 4 && post == -1) {
//                    std::cout << "        E: " << curr.second->l->n << " " << curr.second->r->n << std::endl;
                    if (prev) {
                        prev->n += curr.second->l->n;
                    }
                    post = curr.second->r->n;
                    curr.second->n = 0;
                    delete curr.second->l;
                    delete curr.second->r;
                    curr.second->l = nullptr;
                    curr.second->r = nullptr;
                }
            } else {
                if (curr.first <= 4) {
                    prev = curr.second;
                }
                if (post != -1) {
                    curr.second->n += post;
                    return true;
                }
            }

            curr = std::make_pair(curr.first + 1, curr.second->r);
        }
        return post != -1;
    }

    friend std::ostream &operator<<(std::ostream &os, const SnailFishNumber &number) {
        os << serialzie(number.root);
        return os;
    }

    SnailFishNumber &operator+=(SnailFishNumber &&r) {
        auto n = new num_node(-1);
        n->l = this->root;
        n->r = r.root;
        r.root = nullptr;
        this->root = n;
        do {
//            std::cout << "    --- " << this->toString() << std::endl;
            if (explode()) {
                continue;
            }
            if (!split()) {
                break;
            }
        } while (true);

        return *this;
    }

private:
    void destroy() {
        if (root == nullptr) {
            return;
        }

        std::stack<num_node *> s;
        s.push(root);
        while (!s.empty())
        {
            auto curr = s.top();
            s.pop();
            if (curr->l) {
                s.push(curr->l);
            }
            if (curr->r) {
                s.push(curr->r);
            }
            delete curr;
        }
        root = nullptr;
    }

    bool split() {
        std::stack<num_node *> s;
        num_node *curr = root;

        while (curr != nullptr || !s.empty())
        {
            while (curr != nullptr)
            {
                s.push(curr);
                curr = curr->l;
            }

            curr = s.top();
            s.pop();

            if (curr->n >= 10) {
                assert(curr->l == nullptr && curr->r == nullptr);
                curr->l = new num_node(curr->n / 2);
                curr->r = new num_node((curr->n + 1) / 2);
                curr->n = -1;
                return true;
            }

            curr = curr->r;

        }

        return false;
    }

    struct num_node {
        explicit num_node(int val) :n(val), l(nullptr), r(nullptr) {
            p = nullptr;
        }

        num_node *new_r(int val) {
            r = new num_node(val);
            return r;
        }

        num_node *new_l(int val) {
            l = new num_node(val);
            return l;
        }

        int n;
        num_node *l;
        num_node *r;
        num_node *p;
    } *root;

    explicit SnailFishNumber(num_node *r) : root(r) {}

    static std::string serialzie(SnailFishNumber::num_node *curr) {
        std::string ret;
        if (curr->n != -1) {
            return std::to_string(curr->n);
        } else {
            return "[" + serialzie(curr->l) + "," + serialzie(curr->r) + "]";
        }
    }
    static int magnitude(num_node *curr) {
        if (curr->n != -1) {
            return curr->n;
        }
        return 3 * magnitude(curr->l) + 2 * magnitude(curr->r);
    }

};

int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[]) {
#ifdef TEST
    for (auto &t : tests) {
        SnailFishNumber n{t};
        std::cout << n << std::endl;
    }
    SnailFishNumber n2("[[3,4],5]");
    n2 += SnailFishNumber(tests[0]);

    std::cout << n2 << std::endl << std::endl;

    for (auto &t : test_explode) {
        SnailFishNumber n(t);
        std::cout << "Exploding: " << n << std::endl;
        while(n.explode());
        std::cout << n << std::endl;
    }
    std::cout << std::endl;

    auto n1 = SnailFishNumber(test_plus[0]);
    for (int i = 1; i < 6; i++) {
        n2 = SnailFishNumber(test_plus[i]);
        std::cout << n1 << " + " << n2 << " = ";
        n1 += std::move(n2);
        std::cout << n1 << std::endl;

    }

    n1 = SnailFishNumber("[[[[4,3],4],4],[7,[[8,4],9]]]");
    n1 += SnailFishNumber("[1,1]");

    std::cout << "t1: " << n1 <<std::endl << std::endl;

    n1 = SnailFishNumber(test_plus2[0]);
    for (int i = 1; i < 10; i++) {
        n2 = SnailFishNumber(test_plus2[i]);
        std::cout << "  " << n1 << std::endl;
        std::cout << "+ " << n2 << std::endl;
        n1 += std::move(n2);
        std::cout << "= " << n1 << std::endl << std::endl;
    }
    for (auto &t: test_mag) {
        n1 = SnailFishNumber(t);
        std::cout << n1 << " = " << n1.magnitude() << std::endl;
    }
#endif

    std::ifstream f("day18.input");
    std::string strnum;
    std::vector<std::string> strnumbers;
    f >> strnum;
    auto res = SnailFishNumber(strnum);
    while (f >> strnum) {
        strnumbers.push_back(strnum);
        res += SnailFishNumber(strnum);
    }
    f.close();
    std::cout << "P1 magnitude: " << res.magnitude() << std::endl;

    int max_mag = -1;
    for (auto &sn1: strnumbers) {
        for(auto &sn2: strnumbers) {
            SnailFishNumber n1(sn1);
            n1 += SnailFishNumber(sn2);

            auto mag = n1.magnitude();
            if (mag > max_mag) {
                max_mag = mag;
            }
        }
    }
    std::cout << "P2: max magnitude: " << max_mag << std::endl;

    return 0;
}
#pragma clang diagnostic pop