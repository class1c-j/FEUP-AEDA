#include "vehicle.h"
#include <iostream>
#include <utility>


Vehicle::Vehicle(std::string b, int m, int y) : brand(std::move(b)), month(m), year(y) {

}

int Vehicle::getYear() const {
    return this->year;
}

std::string Vehicle::getBrand() const {
    return this->brand;
}

bool Vehicle::operator<(const Vehicle &v) const {
    return (this->year < v.getYear()) || (year == v.getYear() && month < v.getMonth());
}

int Vehicle::info() const {
    return 3;
}

int Vehicle::info(std::ostream &o) const {
    std::cout << "Vehicle info";
    std::cout << "\nbrand: " << this->brand << "\nmonth: " << this->month << "\nyear: " << this->year << '\n';
    return 3;
}

int Vehicle::getMonth() const {
    return this->month;
}

MotorVehicle::MotorVehicle(std::string b, int m, int y, std::string f, int cyl) : Vehicle(std::move(b), m, y), fuel(std::move(f)), cylinder(cyl) {
}

std::string MotorVehicle::getFuel() const {
    return this->fuel;
}

int MotorVehicle::info() const {
    return Vehicle::info() + 2;
}

int MotorVehicle::info(std::ostream &o) const {
    o << "MotorVehicle info";
    o << "\nfuel: " << this->fuel << "\ncylinder: " << this->cylinder << '\n';
    return Vehicle::info() + 2;
}

float MotorVehicle::calculateTax() const {
    if (fuel == "gas" && cylinder <= 1000 || fuel != "gas" && cylinder <=1500)
        return year > 1995 ? 14.56 : 8.10;
    else if (fuel == "gas" && cylinder <= 1300 || fuel != "gas" && cylinder <=2000)
        return year > 1995 ? 29.06 : 14.56;
    else if (fuel == "gas" && cylinder <= 1750 || fuel != "gas" && cylinder <=3000)
        return year > 1995 ? 45.15 : 22.65;
    else if (fuel == "gas" && cylinder <= 2600 || fuel != "gas" && cylinder > 3000)
        return year > 1995 ? 113.98 : 54.89;
    else if (fuel == "gas" && cylinder <= 3500)
        return year > 1995 ? 181.17 : 87.13;
    else
        return year > 1995 ? 320.89 : 148.37;
}


Car::Car(std::string b, int m, int y, std::string f, int cyl) : MotorVehicle(std::move(b), m, y, std::move(f), cyl) {
}

int Car::info() const {
    return MotorVehicle::info();
}

int Car::info(std::ostream &o) const {
    std::cout << "Car info\n";
    return MotorVehicle::info(o);
}


Truck::Truck(std::string b, int m, int y, std::string f, int cyl, int ml) : MotorVehicle(std::move(b), m, y, std::move(f), cyl), maximumLoad(m) {
}

int Truck::info() const {
    return MotorVehicle::info() + 1;
}

int Truck::info(std::ostream &o) const {
    std::cout << "Truck info\n";
    std::cout << "maximum load: " << this->maximumLoad << '\n';
    return MotorVehicle::info(o) + 1;
}


Bicycle::Bicycle(std::string b, int m, int y, std::string t) : Vehicle(std::move(b), m, y), type(std::move(t)) {
}

int Bicycle::info() const {
    return Vehicle::info() + 1;
}

int Bicycle::info(std::ostream &o) const {
    std::cout << "Bicycle info\n";
    std::cout << "type: " << this->type << '\n';
    return Vehicle::info() + 1;
}

float Bicycle::calculateTax() const {
    return 0;
}


