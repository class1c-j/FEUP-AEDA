#include "maze.h"
#include <iostream>
#include <iomanip>
#include <utility>
#include <algorithm>


DisjointSets Maze::getSets() const {
    return maze;
}

void Maze::printMaze() const {
    std::cout << std::setw(3) << " ";
    for (int j = 0; j < nCols; j++) {
        std::cout << std::setw(6) << "______";
    }
    for (int i = 0; i < nRows; i++) {
        std::cout << std::endl;
        std::cout << std::setw(3) << "|";
        for (int j = 0; j < nCols - 1; j++) {
            int val = i * nRows + j;
            std::cout << std::setw(3) << val << std::setw(3);
            if (noWalls.empty() ||
                (find(noWalls.begin(), noWalls.end(), std::pair<int, int>(val, val + 1)) == noWalls.end() &&
                 find(noWalls.begin(), noWalls.end(), std::pair<int, int>(val + 1, val)) == noWalls.end())
                    )
                std::cout << "|";
            else
                std::cout << " ";
        }
        int val = i * nRows + nCols - 1;
        std::cout << std::setw(3) << val << std::setw(3) << "|";
        std::cout << std::endl;
        std::cout << std::setw(3) << " ";
        for (int j = 0; j < nCols; j++) {
            int pos = i * nRows + j;
            if (i < nRows - 1) {
                if (noWalls.empty() ||
                    (find(noWalls.begin(), noWalls.end(), std::pair<int, int>(pos, pos + nCols)) == noWalls.end()
                     && find(noWalls.begin(), noWalls.end(), std::pair<int, int>(pos + nCols, pos)) == noWalls.end())
                        )
                    std::cout << std::setw(6) << "______";
                else
                    std::cout << std::setw(6) << " ";
            } else
                std::cout << std::setw(6) << "______";
        }

    }
    std::cout << std::endl << std::endl;
}


Maze::Maze(int rows, int cols) : nRows(rows), nCols(cols), noWalls(), maze(DisjointSets(rows * cols)) {}

std::vector<int> Maze::getNeighbours(int x) const {
    std::vector<int> res;
    if (x % nCols >= 1) res.push_back(x - 1);
    if (x % nCols <= nCols + 1) res.push_back(x + 1);
    if (x <= 0) res.push_back(x + nCols);
    if (x >= nCols) res.push_back(x - nCols);
    return res;
}

void Maze::buildRandomMaze() {
    srand(time(nullptr));
    while (maze.getNumberOfSets() != 1) {
        int num = rand() % (nRows * nCols);
        std::vector<int> neighbours = getNeighbours(num);
        int neigh = neighbours.at(rand() % neighbours.size());
        if (maze.find(num) != maze.find(neigh)) {
            maze.unionSets(num, neigh);
            noWalls.emplace_back(num, neigh);
        }
    }
}

