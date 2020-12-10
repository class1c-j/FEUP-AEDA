#include "bet.h"

bool Bet::contains(unsigned num) const {
    return numbers.find(num) != numbers.end();
}

void Bet::generateBet(const std::vector<unsigned> &values, unsigned n) {
    for (auto curr = values.begin(); numbers.size() < n; curr++) numbers.insert(*curr);
}

unsigned Bet::countRights(const tabHInt &draw) const {
    return std::count_if(numbers.begin(), numbers.end(), [&draw](const unsigned elem) {
        return draw.count(elem);
    });
}