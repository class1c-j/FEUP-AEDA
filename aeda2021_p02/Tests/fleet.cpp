#include "fleet.h"

std::vector<Vehicle *> Fleet::getVehicles() const {
    return vehicles;
}

void Fleet::addVehicle(Vehicle *v1) {
    vehicles.push_back(v1);
}

int Fleet::numVehicles() const {
    return vehicles.size();
}

int Fleet::lowestYear() const {
    if (vehicles.empty()) return 0;
    auto min = std::min_element(vehicles.begin(), vehicles.end(), [](const Vehicle* v1, const Vehicle* v2) {
        return v1->getYear() < v2->getYear();
    });
    return (*min)->getYear();
}

std::vector<Vehicle *> Fleet::operator()(int yearM) const {
    std::vector<Vehicle *> result{};
    std::for_each(vehicles.begin(), vehicles.end(), [&yearM, &result](Vehicle* v){
        if (v->getYear() == yearM) result.push_back(v);
    });
    return result;
}

std::ostream &operator<<(std::ostream &o, const Fleet &f) {
    std::for_each(f.vehicles.begin(), f.vehicles.end(), [&o](const Vehicle* v1){
        v1->info(o);
    });
    return o;
}

float Fleet::totalTax() const {
    float total = 0;
    std::for_each(vehicles.begin(), vehicles.end(), [&total](Vehicle* v){
       total += v->calculateTax();
    });
    return total;
}

unsigned Fleet::removeOldVehicles(int y1) {
    unsigned initialSize = vehicles.size();
    vehicles.erase(std::remove_if(vehicles.begin(), vehicles.end(), [&y1](Vehicle* v1){
        return v1->getYear() <= y1;
    }), vehicles.end());
    return initialSize-vehicles.size();
}

