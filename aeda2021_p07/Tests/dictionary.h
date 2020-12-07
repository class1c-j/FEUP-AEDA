#ifndef _DIC
#define _DIC
#include <string>
#include <fstream>
#include <utility>
#include "bst.h"


class WordMeaning {
        std::string word;
        std::string meaning;
        public:
        WordMeaning() = default;
        WordMeaning(std::string w, std::string m): word(std::move(w)), meaning(std::move(m)) {}
        std::string getWord() const { return word; }
        std::string getMeaning() const { return meaning; }
        void setWord(std::string w) {word=std::move(w); }
        void setMeaning(std::string m) { meaning=std::move(m); }
        bool operator < (const WordMeaning &wm1) const;
};


class Dictionary
{
    BST<WordMeaning> words;
public:
    Dictionary(): words(WordMeaning("","")){};
    BST<WordMeaning> getWords() const;
    void readDictionary(std::ifstream &f);
    std::string searchFor(const std::string& word) const;
    bool correct(const std::string& word, const std::string& newMeaning);
    void print() const;
};


//TODO
class WordNonexistent
{
    WordMeaning m_before;
    WordMeaning m_after;
public:
    WordNonexistent() = default;
    WordNonexistent(WordMeaning before, WordMeaning after) : m_before(std::move(before)), m_after(std::move(after)) {}
    std::string getWordBefore() const {
        return m_before.getWord();
    }
    std::string getMeaningBefore() const {
        return m_before.getMeaning();
    }
    std::string getWordAfter() const {
        return m_after.getWord();
    }
    std::string getMeaningAfter() const {
        return m_after.getMeaning();
    }
};

#endif