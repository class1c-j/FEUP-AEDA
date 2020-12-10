#include "player.h"

void Player::addBet(const Bet &b) {
    bets.insert(b);
}

unsigned Player::betsInNumber(unsigned num) const {
    return std::count_if(bets.begin(), bets.end(), [&num](const Bet &b) {
        return b.contains(num);
    });
}

tabHBet Player::drawnBets(const tabHInt &draw) const {
    tabHBet res;
    std::for_each(bets.begin(), bets.end(), [&draw, &res](const Bet &b) {
        if (b.countRights(draw) > 3) res.insert(b);
    });
    return res;
}
