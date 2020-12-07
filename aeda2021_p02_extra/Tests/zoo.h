#ifndef ZOO_H_
#define ZOO_H_

#include "animal.h"
#include <vector>
#include <numeric>

class Zoo {
	std::vector<Animal *> animals;
	std::vector<Veterinary *> veterinarians;
public:
    Zoo() = default;
	unsigned numAnimals() const;
	unsigned numVeterinarians() const;
    void addAnimal(Animal *a1);
    std::string getInfo() const;
    bool isYoung(std::string nameA);
    void allocateVeterinarians(std::istream &isV);
    bool removeVeterinary(std::string nameV);
    bool operator < (Zoo& zoo2) const;
};

namespace utils {

    void removeCarriageReturn(std::string &string);

}


#endif /* ZOO_H_ */
