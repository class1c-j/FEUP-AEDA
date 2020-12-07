#include <iostream>
#include <string>
#include <fstream>
#include "dictionary.h"
#include "bst.h"


BST<WordMeaning> Dictionary::getWords() const {
    return words;
}


bool WordMeaning::operator<(const WordMeaning &wm1) const {
    return this->word < wm1.getWord();
}


void Dictionary::readDictionary(std::ifstream &f) {
    for (std::string word; std::getline(f, word, '\n');) {
        std::string meaning{};
        std::getline(f, meaning, '\n');
        words.insert(WordMeaning(word, meaning));
    }

}


std::string Dictionary::searchFor(const std::string &word) const {
    BSTItrIn<WordMeaning> current(words);
    WordMeaning before{};
    WordMeaning after{};
    for (; !current.isAtEnd(); current.advance()) {
        if (current.retrieve().getWord() == word) {
            return current.retrieve().getMeaning();
        }
        auto next = current;
        next.advance();
        if (next.isAtEnd()) throw WordNonexistent(current.retrieve(), current.retrieve());
        else if (next.retrieve().getWord() > word) throw WordNonexistent(current.retrieve(), next.retrieve());
    }
    return std::string();
}


bool Dictionary::correct(const std::string& word, const std::string& newMeaning) {
    BSTItrIn<WordMeaning> current(words);
    for (; !current.isAtEnd(); current.advance()) {
        if (current.retrieve().getWord() == word) {
            words.remove(current.retrieve());
            words.insert(WordMeaning(word, newMeaning));
            return true;
        }
    }
    words.insert(WordMeaning(word, newMeaning));
    return false;
}


void Dictionary::print() const {
    for (auto it = words.begin(); it != words.end(); it++) {
        std::cout << (*it).getWord() << " - " << (*it).getMeaning() << '\n';
    }
}
