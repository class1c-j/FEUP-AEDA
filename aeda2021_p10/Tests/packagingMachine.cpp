#include "packagingMachine.h"
#include <sstream>

PackagingMachine::PackagingMachine(int boxCap) : boxCapacity(boxCap) {}

unsigned PackagingMachine::numberOfBoxes() {
    return boxes.size();
}

unsigned PackagingMachine::addBox(Box &b1) {
    boxes.push(b1);
    return boxes.size();
}

HeapObj PackagingMachine::getObjects() const {
    return this->objects;
}

HeapBox PackagingMachine::getBoxes() const {
    return this->boxes;
}


unsigned PackagingMachine::loadObjects(std::vector<Object> &objs) {
    unsigned totalObjects(objs.size());
    for (auto current = objs.begin(); current != objs.end(); ++current) {
        if (current->getWeight() <= boxCapacity) {
            objects.push(*current);
            objs.erase(current);
            --current;
        }
    }
    return totalObjects - objs.size();
}


Box PackagingMachine::searchBox(Object &obj) {
    Box b(boxCapacity);
    HeapBox auxBoxes{};
    bool found = false;
    while (!boxes.empty()) {
        Box current = boxes.top();
        if (!found && current.getFree() >= obj.getWeight()) {
            b = current;
            found = true;
        } else auxBoxes.push(current);
        boxes.pop();
    }
    boxes = auxBoxes;
    return b;
}


unsigned PackagingMachine::packObjects() {
    HeapObj auxObjects{};
    while (!objects.empty()) {
        Object current = objects.top();
        Box found = searchBox(current);
        if (current.getWeight() <= found.getFree()) {
            found.addObject(current);
        } else auxObjects.push(current);
        boxes.push(found);
        objects.pop();
    }
    objects = auxObjects;
    return boxes.size();
}


std::string PackagingMachine::printObjectsNotPacked() const {
    std::stringstream ss{};
    if (objects.empty()) ss << "No objects!\n";
    else {
        HeapObj copy(objects);
        while (!copy.empty()) {
            ss << copy.top() << '\n';
            copy.pop();
        }
    }
    return ss.str();
}


Box PackagingMachine::boxWithMoreObjects() const {
    if (boxes.empty()) throw MachineWithoutBoxes();
    Box b(boxCapacity);
    HeapBox copy(boxes);
    while (!copy.empty()) {
        if (copy.top().getSize() > b.getSize()) b = copy.top();
        copy.pop();
    }
    return b;
}