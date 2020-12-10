#ifndef PLAYER_H_
#define PLAYER_H_

#include "bet.h"
#include <string>
#include <utility>


struct betHash {
    int operator()(const Bet &b) const {
        int hash{};
        // might cause collisions on some cases but should be enough for the unit tests
        for (const auto &number : b.getNumbers()) hash = std::hash<unsigned>()(number);
        return hash;
    }

    bool operator()(const Bet &b1, const Bet &b2) const {
        return b1.getNumbers() == b2.getNumbers();
    }
};


typedef std::unordered_set<Bet, betHash, betHash> tabHBet;

class Player {
    tabHBet bets;
    std::string name;
public:
    explicit Player(std::string nm = "anonymous") : name(std::move(nm)) {}

    void addBet(const Bet &ap);

    unsigned betsInNumber(unsigned num) const;

    tabHBet drawnBets(const tabHInt &draw) const;

    unsigned getNumBets() const { return bets.size(); }
};

#endif 
