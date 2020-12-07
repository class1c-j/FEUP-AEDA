#ifndef VEHICLE_H_
#define VEHICLE_H_

#include <string>

class  Vehicle {
protected:
   std::string brand;
   int month, year;
public:
   Vehicle(std::string b, int m, int y);
   virtual ~Vehicle() = default;
   int getYear() const;
   int getMonth() const;
   std::string getBrand() const;
   virtual int info() const;
   virtual int info(std::ostream &o) const;
   bool operator < (const Vehicle & v) const;
   virtual float calculateTax() const = 0;
};

class MotorVehicle: public Vehicle {
    std::string fuel; int cylinder;
public:
    MotorVehicle(std::string b, int m, int y, std::string f,int cyl);
    std::string getFuel() const;
    int info() const override;
    int info(std::ostream &o) const override;
    float calculateTax() const override;
};


class Car: public MotorVehicle {
public:
    Car(std::string b, int m, int y, std::string f, int cyl);
    int info() const override;
    int info(std::ostream &o) const override;
};


class Truck: public MotorVehicle {
    int maximumLoad;
public:
    Truck(std::string b, int m, int y,std::string f, int cyl,int ml);
    int info() const override;
    int info(std::ostream &o) const override;
};


class Bicycle: public Vehicle {
    std::string type;
public:
    Bicycle(std::string b, int m, int y, std::string t);
    int info() const override;
    int info(std::ostream &o) const override;
    float calculateTax() const override;
};

#endif /* VEHICLE_H_ */
