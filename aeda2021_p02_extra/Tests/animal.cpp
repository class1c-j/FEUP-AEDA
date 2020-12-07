#include "animal.h"
#include <sstream>
#include <utility>


int Animal::youngest = INT32_MAX;

std::string Animal::getName() const {
	return name;
}

int Animal::getAge() const {
    return age;
}

void Animal::setVeterinary(Veterinary *vet) {
    this->vet = vet;
}

Veterinary *Animal::getVeterinary() const {
    return vet;
}

Animal::Animal(std::string name, int age) : name(std::move(name)), age(age), vet() {
    if (this->age < Animal::youngest) Animal::youngest = this->age;
}

int Animal::getYoungest() {
    return Animal::youngest;
}

bool Animal::operator<(const Animal& other) const {
    return this->age < other.age;
}

std::string Animal::getInfo() const {
    std::stringstream info{};
    std::string vetInfo = this->getVeterinary() ? this->getVeterinary()->getInfo() + ", " : "";
    info << this->name << ", " << this->age << ", " << vetInfo;
    return info.str();
}


Dog::Dog(std::string name, int age, std::string breed) : Animal(std::move(name), age), breed(std::move(breed)) {

}

bool Dog::isYoung() const {
    return this->age <= 5;
}

std::string Dog::getInfo() const {
    std::stringstream info{};
    info << Animal::getInfo() << this->breed;
    return info.str();
}

Flying::Flying(int maxv, int maxa) : maxVelocity(maxv), maxAltitude(maxa) {

}

int Flying::getMaxVelocity() const {
    return maxVelocity;
}

int Flying::getMaxAltitude() const {
    return maxAltitude;
}

Bat::Bat(std::string name, int age, int maxv, int maxa) : Animal(std::move(name), age), Flying(maxv, maxa) {

}

std::string Bat::getInfo() const {
    std::stringstream info{};
    info << Animal::getInfo() << this->getMaxVelocity() << ", " << this->getMaxAltitude();
    return info.str();
}

bool Bat::isYoung() const {
    return this->age <=4;
}


