#include <stdio.h>

//#define D

#ifndef D // Real map
static const char map[][32] = {
    ".........#.#.#.........#.#.....",
    "...#......#...#.....#.....#....",
    "#.....#.....#.....#.#........#.",
    "......#..#......#.......#......",
    ".#..........#.............#...#",
    "............#..##.......##...##",
    "....#.....#..#....#............",
    ".#..#.........#....#.#....#....",
    "#.#...#...##..##.#..##..#....#.",
    ".#.......#.#...#..........#....",
    "...#...#........##...#..#.....#",
    "..................#..........#.",
    ".....#.##..............#.......",
    "........#....##..##....#.......",
    "...#.....#.##..........#...##..",
    ".......#.#....#............#...",
    "..............#......#......#..",
    "#.......#...........#........##",
    ".......#.......##......#.......",
    "................#....##...#.#.#",
    "#.......#....................#.",
    ".##.#..##..#..#.#.....#.....#..",
    "#...#............#......##....#",
    ".#....##.#......#.#......#..#..",
    "..........#........#.#.#.......",
    "...#...#..........#..#....#....",
    "..#.#...#...#...##...##......#.",
    "......#...#........#.......###.",
    "....#...............#.###...#.#",
    "..................#.....#..#.#.",
    ".#...#..#..........#........#..",
    "#..........##................##",
    "...#.....#...#......#.#......#.",
    "......#..........#.#......#..#.",
    "..#......#.....................",
    "............#.........##.......",
    "......#.......#........#.......",
    "#.#...#...........#.......#....",
    ".#.#........#.#.#....#........#",
    "#.....##........#.#.....#.#....",
    ".#...#..........##...#.....#..#",
    ".........#....###............#.",
    "..#...#..............#.#.#.....",
    ".....#.#.#..#.#.#.###......#.#.",
    ".#.##...#.......###..#.........",
    ".....##....#.##..#.##..#.......",
    "..#...........##......#..#.....",
    "................##...#.........",
    "##.....................#..#.###",
    "...#..#....#...........#.......",
    ".#.............##.#.....#.#....",
    ".......#.#.#....##..#....#...#.",
    "...##..#..........#....#.......",
    "....##......#.........#........",
    ".##....#...........#.#.......#.",
    "...#...#.##.......#.#..........",
    "..#.........#.##...........#...",
    "....#.##........#.......#...##.",
    "...................#..#..#...##",
    "#...#......###..##.#..###......",
    "#.............#.#........#...#.",
    "...#...#..#..#..............#..",
    "#.....#..#...#...#......#.#..#.",
    "...##.............#........##.#",
    "......#.#.........#.#....#...#.",
    "........##............#...#....",
    "............#.#...#......#.....",
    "...#...........#...#...........",
    ".........#.#......#............",
    "....#.............#..#.....#..#",
    "#.....#...........#.....#.#.#.#",
    ".............#.....##......#...",
    "...................###.#......#",
    "#.##.....#...#..#..#...#....#..",
    "............#.....#....#.#.....",
    "#....#..#..........#....#..#...",
    "..........##..................#",
    "....#.......###..#......###....",
    ".......#...#.##.##..#....##....",
    "...##...............#.....#...#",
    "#...........#...#......#..#..#.",
    "..##....#.......#...#.....#....",
    ".......##..............#.##..#.",
    ".#......#..........#.......#...",
    "....##...................#.#..#",
    "......#....###................#",
    ".#........#...........#........",
    ".#.....##....#..##...........#.",
    "##..............##...#.......#.",
    "......#..........#..........##.",
    "..#.....#.#.........####....#..",
    ".............#......#......#...",
    "..#.............#...........##.",
    "#.#...#........#..........##...",
    "...#....#.....#.....#.....##...",
    "......#........................",
    "......#..#...#......#.....#....",
    "......#....##.....#....#.......",
    "#.#......#.##..#...............",
    "..........#.#.##..##..#........",
    "......#.#..#....###.#..........",
    "........................#....#.",
    "#.#.............#....#.....##.#",
    ".#.#..........#.......#..#....#",
    "..#...#......#..#..#...#.#...#.",
    "...#.##...###..................",
    "........#.#...........#...#....",
    "........#..........#....#......",
    "#....#........#.......##.....#.",
    "......###...##...#......#......",
    "............#.......#.....##..#",
    "....#..#.......##......#.......",
    "#............##................",
    "...............#..#......#...#.",
    ".#....##...#......#............",
    "#...#................#.........",
    "..#....#..#........##......#...",
    "....#....###......##.#.......#.",
    "......#.#..#.#..#....#..#......",
    "....#..........#..#..#.........",
    ".#..#.......#......#........#..",
    ".......#..#..#............#....",
    ".............#...#....#..#.....",
    "..............#.#.#.........#..",
    "#.....##.......#....#..........",
    "...#.....#......#..............",
    "...##.#..#.#........#..##....#.",
    ".......#.#.....##..#...........",
    ".....#.#....#..................",
    ".#......#.###..............##..",
    "..#....#...#..#...##...##....#.",
    "..........##..#...#..#.........",
    "..#............#........#.#...#",
    ".........................#.#.#.",
    "......#........#.#..#......##.#",
    "#.#......#..#.........#........",
    ".....#........#......#...#.#...",
    "........##....##....#.#........",
    "....#....#.#...#...##....#..#..",
    "#.............#.....#..........",
    "#............##..#............#",
    "..#.#......#........#..........",
    ".#......#......#.#.##.##.......",
    "..#.....#..........#......##...",
    "...#......#...#.##....#.....##.",
    "......#......#...........#.#...",
    "....#........#..#..#........#.#",
    "....#.........#.....#...#.#.#..",
    "....#.....###........#.........",
    ".............##........#.#.....",
    "...#............#........#.#.#.",
    "......#....#.......#.#.........",
    ".....#................#........",
    ".#....#..#.#.............#...#.",
    "#..##...#............#......#..",
    "...#..#........................",
    ".#.#...........#.......#.......",
    "#....###............##.........",
    "...##....#.#............##.....",
    ".........####......#........#..",
    ".....#.......#.#...............",
    ".......#...#.###..#....#...#..#",
    "...#.....##..#....#..#.#...###.",
    ".............#........#.#.#..#.",
    "................#..........##..",
    ".......####..##..##........##.#",
    "..#......#..#..#.#.##..........",
    "#....#........#....#...###.#.#.",
    "........##........##.....#.....",
    "...........#.#...........#....#",
    "#.............#...........#....",
    "...#.........#...#....#.....#..",
    "..##......#...#...............#",
    ".............#.........#....#..",
    "..#...........#..#........#.##.",
    ".#.#......#.............##...#.",
    ".#......#.....##.#..#..#.......",
    "....##......#..................",
    ".#.#..##............#....#....#",
    "........#...##.............#..#",
    "........#....##.....#......###.",
    ".........#....#.#..............",
    "#.....#........................",
    ".#..#....#.....#......#.###..#.",
    "..........#...#....##....#..#..",
    "...#.#.#...##..#..#......#..#.#",
    "#............#.....#....#......",
    "#.###...#.#......###..#....#..#",
    "...#.###........#......#....#..",
    "..#.##...#.........#.#.........",
    "............##.................",
    "....#..........#.#.#.#.#....#..",
    "...##.#...#.......#.......##..#",
    "....##.#........#....#...#.....",
    ".............#.#....#...#.....#",
    "...#......................##...",
    "..#...#.....#.....#........#..#",
    "..#..#.......#....#..##.....#..",
    "..#..#.#.......................",
    ".......##..#....#....#..#......",
    "....#......##....#............#",
    ".#...#..#..#.##...#.#...#......",
    ".....#......#....#.........#...",
    ".##......##.........#....#.....",
    "#...........#...##.....#......#",
    ".....#.#.......#.........#.....",
    ".........#..........#..####.##.",
    "............#..#......#.#......",
    ".#.............#........#.#....",
    "......#......#...#..#....#####.",
    ".........##.#..##...###..#....#",
    "....#.#....#.#..#.........#....",
    "..#.............#...##...##....",
    "........#..........#.##..#....#",
    ".....#...#..##........#.#..#...",
    "##..#.#.....#............#.....",
    ".............#........##...##..",
    "#......####.....##.............",
    "..##.....##....###..#.#....#...",
    "......##.##.#...#..#.#..##.....",
    "......#.................#......",
    "#.....#.#...#......#.#....#....",
    "....#.#........#..............#",
    "##........#.......##.#...##...#",
    "..#..................#.#....#..",
    "...........#..........#.#.....#",
    "........##.#.....#......#..#..#",
    ".....#....#..#.....#.........##",
    "#.#..#..#...#......#..........#",
    "#...##.....#..#.#.......#.##...",
    "..#....##...............#......",
    "#..........#.#.........#.#....#",
    "..............#......#....#....",
    ".....#...........#...#...#...#.",
    "...#......#....#....#..........",
    ".#..........#.#....##..##....#.",
    "..............#.........#.#....",
    ".......#.....#.....#...##....#.",
    "##.#.........#....#.....#.#....",
    "....#..#......#................",
    "......##.....#.......##........",
    ".....##...#........#...#...#...",
    "..#...#...#..#..#.#......#..#..",
    "....#...#.......#..............",
    "....#..#.........###........#..",
    "....#.............##..#........",
    "..........##.#.......##..##....",
    "#.##..................#.....#..",
    "#........#........#.....#......",
    ".#...#......#..................",
    "#....##.##......#...#.........#",
    "......#.##..##................#",
    "............#.........##.......",
    "..........####.#........#.....#",
    ".##...#...#....#..#............",
    ".#.##...#..#...#......#......##",
    ".....#.#....#..###......#.#.#..",
    "...#.......................##..",
    "......................#.......#",
    "..#....#.........#..#.#.....#..",
    ".#....#..#....#...#............",
    "..........#...##.....#.#..#....",
    "........#..#..#....#...#...#...",
    ".....#......#.#................",
    ".....#...........#...#.........",
    ".....#...##..#.#....#..#.....#.",
    "#.......#.............##.......",
    "................#....#.#..#....",
    ".#..##...#.#........#......#.#.",
    ".#.##..........#...............",
    "....##......#....#........#....",
    "....#..#....#.##.#.............",
    ".......#..#......##.#.....#....",
    ".......#.....#.............#...",
    ".....#....#.......#............",
    "........#.#...##..##..##.......",
    "#.........##....##...##........",
    "........#..#.#..........###.#..",
    "..........................#.#..",
    "#.....#.......#..#........#....",
    "...##.....#.......#......#.....",
    ".#.#..#...........#...........#",
    ".....##..#........#...####.....",
    ".#.#...##.#.#..#..#.#..#.......",
    "..#.##.#...#.#.#...#..#........",
    "............#..........#..#....",
    "...............#..##.#.........",
    ".............#.....#....#......",
    "...##..##......##..........#...",
    "..#.......#....#..........#...#",
    ".##................#.#.#.......",
    ".....##.....#..#.....#.........",
    "......#.#.......#......#..#....",
    ".....#.....#........#.......##.",
    "......#.......##......#...#...#",
    "....#...........###.........#..",
    "...#.....#.........##........#.",
    "..#.....#..............#.......",
    "....#.......#...#....#....#..##",
    "......#...........#...........#",
    ".##......#......#.#.....#.##...",
    "....#..##......#...#..#.#.###..",
    ".......#.#....#......#..#......",
    "..........#........#...........",
    "#.##.........#.#.#...#...#.#...",
    ".#......###.....#....#.#....#..",
    "...................##..#.......",
    "....#..#..............#.#.....#",
    "#..................#.....#.....",
    "...........##.##.......#..#.#..",
    "........#.#......#...........#.",
    "#..#.......#...#...........#.#.",
    "......##...........#...........",
    ".........#.#........#........#.",
    "#......#....#.#.....#..#.......",
    "............#..#.....##...#....",
    ".#......#..#......#.........#..",
    ".......#...#.........#.##.....#",
    "........................#..#...",
    ".###..............#.#..#.......",
    ".....#.........#.......#......#",
    "..##..##....#.....#.......#.#..",
    "...###.#..#.##............#....",

};
#else // Test map
static char map[][12] = {
    "..##.......",
    "#...#...#..",
    ".#....#..#.",
    "..#.#...#.#",
    ".#...##..#.",
    "..#.##.....",
    ".#.#.#....#",
    ".#........#",
    "#.##...#...",
    "#...##....#",
    ".#..#...#.#",
};
#endif

#define mapwidth (sizeof(map[0]) - 1)
#define mapheight (sizeof(map) / sizeof(map[0]))

typedef struct v_t {
    int x;
    int y;
} v_t;

static const v_t steps[] = { {1, 1},
                             {3, 1},
                             {5, 1},
                             {7, 1},
                             {1, 2}
};

int main(int argc, char *argv[]) {
    unsigned result = 1;

    printf("Map: %ldx%ld\n", mapwidth, mapheight);

    for (int s = 0; s < sizeof(steps)/ sizeof(steps[0]); s++) {
        unsigned x = 0;
        unsigned y = 0;
        unsigned treecnt = 0;

        while (y < mapheight) {
            x = (x + steps[s].x) % mapwidth;
            y += steps[s].y;
            if (map[y][x] == '#') {
                treecnt++;
#ifdef D1
                map[y][x] = 'X';
            } else {
                map[y][x] = 'O';
#endif
            }
        }
#ifdef D1
        for (int i = 0; i < mapheight; i++) {
        printf("%s\n", map[i]);
    }
#endif

        printf("Steps: %d/%d, Encountered trees: %d\n", steps[s].x, steps[s].y, treecnt);
        result *= treecnt;
    }

    printf("\nMul of eTrees: %u\n", result);

    return 0;
}