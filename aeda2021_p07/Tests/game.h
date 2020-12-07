#ifndef GAME_H_
#define GAME_H_

#include "binaryTree.h"
#include <iostream>
#include <cstdlib>

class Circle {
    int points;
    bool state;
    int nVisits;
public:
    explicit Circle(int p = 0, bool s = false) : points(p), state(s), nVisits(0) {}

    int getPoints() const { return points; }

    bool getState() const { return state; }

    void changeState() { if (!state) state = true; else state = false; }

    int getNVisits() const { return nVisits; }

    void incrementVisits() { ++nVisits; }

    friend std::ostream &operator<<(std::ostream &os, Circle &c1);
};


class Game {
    BinaryTree<Circle> game;
public:
    Game(int h, std::vector<int> &points, std::vector<bool> &states);

    BinaryTree<Circle> generateTree(int pos, int height, const std::vector<int> &points, const std::vector<bool> states);

    std::string writeGame();

    int move();

    int mostVisited();

    BinaryTree<Circle> &getGame() { return game; }
};

#endif
