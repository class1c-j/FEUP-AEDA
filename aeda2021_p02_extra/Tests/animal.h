#ifndef SRC_ANIMAL_H_
#define SRC_ANIMAL_H_

#include "veterinary.h"
#include <string>
#include <algorithm>


class Animal {
protected:
    std::string name;
    int age;
    Veterinary *vet;
    static int youngest;
public:
    Animal(std::string name, int age);
    virtual ~Animal()= default;;
    std::string getName() const;
    int getAge() const;
    Veterinary *getVeterinary() const;
    void setVeterinary(Veterinary *vet);
    static int getYoungest();
    bool operator<(const Animal& other) const;
    virtual std::string getInfo() const;  // info concerning name, age, name of the veterinary (if any)
    virtual bool isYoung() const = 0;
};


class Dog: public Animal {
    std::string breed;
public:
   Dog(std::string name, int age, std::string breed);
   bool isYoung() const override;
   std::string getInfo() const override;
// to complete
};


class Flying {
    int maxVelocity;
    int maxAltitude;
public:

   Flying(int maxv, int maxa);

    int getMaxVelocity() const;

    int getMaxAltitude() const;

//to complete
};


class Bat: public Animal, public Flying {
public:
    Bat(std::string name, int age, int maxv, int maxa);
    bool isYoung() const override;
    std::string getInfo() const override;
// to complete
};

#endif /* SRC_ANIMAL_H_ */
