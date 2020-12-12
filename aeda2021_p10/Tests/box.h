#ifndef BOX_H_
#define BOX_H_

#include <stack>
#include <iostream>

class Object {
    unsigned id;
    unsigned weight;
public:
    Object(unsigned i, unsigned w);

    unsigned getID() const;

    unsigned getWeight() const;

    friend std::ostream &operator<<(std::ostream &os, Object obj);

    bool operator<(const Object &o1) const;
};


typedef std::stack<Object> StackObj;

class Box {
    StackObj objects;
    unsigned id;
    unsigned capacity;
    unsigned free;
    static unsigned lastId;
public:
    explicit Box(unsigned cap = 10);

    unsigned getID() const;

    unsigned getFree() const;

    void addObject(Object &obj);

    static void resetID();

    unsigned getSize() const;

    std::string printContent() const;

    bool operator<(const Box &b1) const;

};

#endif