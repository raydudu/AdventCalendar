#include <iostream>
#include <fstream>
#include <algorithm>

extern "C" {
#include "day02cc.h"
    int yylex(void);
    void yyerror(const char *msg);
    int yyparse(void);

    void print_part_one(unsigned depth, unsigned distance);
    void print_part_two(unsigned depth, unsigned distance, unsigned aim);
}

static std::ifstream f("day02.input");

void yyerror(const char *msg) {
    std::cout << "Parse error: " << msg << std::endl;
    exit(1);
}

int yylex() {
    std::string word;

    f >> word;
    if (word.empty()) {
        return -1;
    }

    if (word == "up") {
        return UP;
    } else if (word == "down") {
        return DOWN;
    } else if (word == "forward") {
        return FORWARD;
    } else if(std::find_if(word.begin(), word.end(), [](char c) { return isdigit(c);}) != word.end()) {
        yylval.steps = std::stoul(word);
        return STEP;
    } else {
        return -1;
    }
}

void print_part_one(unsigned int depth, unsigned int distance) {
    std::cout << "P1: depth: " << depth << ", distance: " << distance << std::endl;
    std::cout << "P1: result: " << depth * distance << std::endl;
}

void print_part_two(unsigned int depth, unsigned int distance, unsigned int aim) {
    std::cout << "P2: depth: " << depth << ", distance: " << distance << ", aim: " << aim << std::endl;
    std::cout << "P2: result: " << depth * distance << std::endl;

}

int main(int argc, char *argv[]) {
    if (!f.is_open()) {
        std::cout << "File not open" << std::endl;
        return 1;
    }

    return yyparse();
}