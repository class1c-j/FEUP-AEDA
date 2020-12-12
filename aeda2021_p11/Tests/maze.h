#ifndef MAZE_H
#define MAZE_H

#include "disjointSets.h"

class Maze {
    DisjointSets maze;
    int nRows = 0;
    int nCols = 0;
    std::vector<std::pair<int, int> > noWalls;

    std::vector<int> getNeighbours(int x) const;

public:
    Maze(int rows, int cols);

    void buildRandomMaze();

    DisjointSets getSets() const;

    void printMaze() const;
};

#endif
