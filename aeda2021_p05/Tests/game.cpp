#include "game.h"
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <random>

using namespace std;


unsigned int Game::numberOfWords(string phrase)
{
    if ( phrase.length() == 0 ) return 0;

    unsigned n=1;
    size_t pos = phrase.find(' ');
    while (pos != string::npos) {
        phrase = phrase.substr(pos+1);
        pos = phrase.find(' ');
        n++;
    }
    return n;
}

Game::Game() = default;

Game::Game(list<Kid>& l2) {
    kids = l2;
}

void Game::addKid(const Kid &k1) {
    kids.insert(kids.end(), k1);
}

list<Kid> Game::getKids() const {
    return kids;
}

string Game::write() const {
    std::string result{};
    std::for_each(kids.begin(), kids.end(), [&](const Kid& kid) {result += kid.write() += "\n";});
    return result;
}

Kid& Game::loseGame(string phrase) {

    unsigned wordCount = numberOfWords(phrase);
    unsigned numberOfKidsInGame = kids.size();

    std::list<Kid> kidsCopy = kids;
    auto current = kidsCopy.begin();

    while (numberOfKidsInGame > 1) {
        for (unsigned i = 1; i < wordCount; i++) {
            current++;
            if (current == kidsCopy.end()) current = kidsCopy.begin();
        }
        current = kidsCopy.erase(current);
        if (current == kidsCopy.end()) current = kidsCopy.begin();
        numberOfKidsInGame--;
    }

    return kidsCopy.front();
}

list<Kid>& Game::reverse() {
    std::reverse(kids.begin(), kids.end());
    return kids;
}

list<Kid> Game::removeOlder(unsigned id) {
    list<Kid> newList{};
    auto remove = std::remove_if(kids.begin(), kids.end(), [&id, &newList](Kid kid){
        if (kid.getAge() > id) {
            newList.insert(newList.end(), kid);
            return true;
        } else return false;
    });
    kids.erase(remove, kids.end());
    return newList;
}


void Game::setKids(const list<Kid>& l1) {
    list<Kid> replaced = l1;
    kids.splice(kids.end(), replaced);
}

bool Game::operator==(Game& g2) {
    if (kids.size() != g2.getKids().size()) return false;
    auto g1Iter = kids.begin();
    auto g2Iter = g2.kids.begin();
    while (g1Iter != kids.end()) {
        if (!(*g1Iter == *g2Iter)) return false;
        std::advance(g1Iter, 1); std::advance(g2Iter, 1);
    }
    return true;
}

list<Kid> Game::shuffle() const {
    list<Kid> shuffled{};
    for (const auto &i : kids) {
        std::size_t pos = rand() % kids.size() - 1;
        auto iter = shuffled.begin();
        std::advance(iter, pos);
        shuffled.insert(iter, i);
    }
    return shuffled;
}
