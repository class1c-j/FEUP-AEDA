#include "game.h"
#include <sstream>


std::ostream &operator<<(std::ostream &os, Circle &c1) {
    std::string state = c1.getState() ? "true" : "false";
    os << c1.getPoints() << '-' << state << '-' << c1.getNVisits() << '\n';
    return os;
}


Game::Game(int h, std::vector<int> &points, std::vector<bool> &states) {
    game = generateTree(0, h, points, states);
}


std::string Game::writeGame() {
    BTItrLevel<Circle> current(game);
    std::stringstream ss{};
    for (; !current.isAtEnd(); current.advance()) {
        ss << current.retrieve();
    }
    return ss.str();
}


int Game::move() {
    BTItrLevel<Circle> current(game);
    int score = current.retrieve().getPoints(), pos = 0;
    while (!current.isAtEnd()) {
        int toGo = current.retrieve().getState() ? 2 * pos + 2 : 2 * pos + 1;
        current.retrieve().changeState();
        current.retrieve().incrementVisits();
        for (; pos < toGo && !current.isAtEnd(); pos++) current.advance();
        if (current.isAtEnd()) break;
        score = current.retrieve().getPoints();
    }
    return score;
}


int Game::mostVisited() {
    BTItrLevel<Circle> current(game);
    current.advance();  // do not consider the tree root
    int max{};
    for (; !current.isAtEnd(); current.advance()) {
        if (current.retrieve().getNVisits() > max) max = current.retrieve().getNVisits();
    }
    return max;
}

BinaryTree<Circle>
Game::generateTree(int pos, int height, const std::vector<int> &points, const std::vector<bool> states) {
    Circle centre(points.at(pos), states.at(pos));
    if (height == 0) return BinaryTree<Circle>(centre);
    BinaryTree<Circle> left = generateTree(2 * pos + 1, height - 1, points, states);
    BinaryTree<Circle> right = generateTree(2 * pos + 2, height - 1, points, states);
    return BinaryTree<Circle>(centre, left, right);
}
