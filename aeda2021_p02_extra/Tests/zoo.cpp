#include "zoo.h"
#include <iostream>
#include <sstream>

void utils::removeCarriageReturn(std::string &string) {
    if (!string.empty() && string.back() == '\r') {
        string.erase(string.size() - 1);
    }
}

unsigned Zoo::numAnimals() const {
    return animals.size();
}

unsigned Zoo::numVeterinarians() const {
    return veterinarians.size();
}

void Zoo::addAnimal(Animal *a1) {
    animals.push_back(a1);
}

std::string Zoo::getInfo() const {
    std::stringstream ss;
    std::for_each(animals.begin(), animals.end(), [&ss](const Animal* animal){
        ss << animal->getName() << ", " << animal->getAge() << ", " << animal->getVeterinary();
    });
    return ss.str();
}

bool Zoo::isYoung(std::string nameA) {
    auto found = std::find_if(animals.begin(), animals.end(), [&nameA](Animal* a1) {
        return a1->getName() == nameA && a1->isYoung();
    });
    return found != animals.end();
}

void Zoo::allocateVeterinarians(std::istream &isV) {

    for (std::string line; getline(isV, line);) {
        utils::removeCarriageReturn(line);
        std::string name = line;
        getline(isV, line); long code = stol(line);
        veterinarians.push_back(new Veterinary(name, code));
    }

    for (unsigned i = 0; i < animals.size(); i ++) {
        animals.at(i)->setVeterinary(veterinarians.at(i%veterinarians.size()));
    }

}

bool Zoo::removeVeterinary(std::string nameV) {

    auto found = std::find_if(veterinarians.begin(), veterinarians.end(), [&nameV](const Veterinary* v) {
        return nameV == v->getName();
    });
    if (found == veterinarians.end()) return false;
    auto nextElement = std::next(found);
    std::for_each(animals.begin(), animals.end(), [&found, &nextElement](Animal* animal){
        if (animal->getVeterinary() == *found) {
            animal->setVeterinary(*nextElement);
        }
    });
    veterinarians.erase(found);
    return true;
}

bool Zoo::operator<(Zoo &zoo2) const {
    unsigned sum1 = std::accumulate(animals.begin(), animals.end(), 0, [](unsigned accumulator, const Animal* a1){
        return accumulator + a1->getAge();
    });
    unsigned sum2 = std::accumulate(zoo2.animals.begin(), zoo2.animals.end(), 0, [](unsigned accumulator, const Animal* a1){
        return accumulator + a1->getAge();
    });
    return sum1 < sum2;
}
