#ifndef PACKAGINGMACHINE_H_
#define PACKAGINGMACHINE_H_

#include <queue>
#include <vector>
#include <stack>
#include <iostream>
#include "box.h"


typedef std::priority_queue<Object> HeapObj;
typedef std::priority_queue<Box> HeapBox;

class PackagingMachine {
    HeapObj objects;
    HeapBox boxes;
    unsigned boxCapacity;
public:
    explicit PackagingMachine(int boxCap = 10);

    unsigned numberOfBoxes();

    unsigned addBox(Box &b1);

    HeapObj getObjects() const;

    HeapBox getBoxes() const;

    unsigned loadObjects(std::vector<Object> &objs);

    Box searchBox(Object &obj);

    unsigned packObjects();

    std::string printObjectsNotPacked() const;

    Box boxWithMoreObjects() const;

    class MachineWithoutBoxes {
    };
};

#endif