#ifndef FLEET_H_
#define FLEET_H_

#include <vector>
#include <algorithm>
#include <string>

#include "vehicle.h"

class Fleet {
	std::vector<Vehicle *> vehicles;
public:

    std::vector<Vehicle *> getVehicles() const;
    int numVehicles() const;    // retorna o nº de veículos no vector veiculos
    void addVehicle(Vehicle*v1);
    std::vector<Vehicle *> operator () (int yearM) const;
    int lowestYear() const; // retorna o menor ano dos veículos presentes no vetor veículos;
                            // retorna 0 se não existir nenhum veículo
	friend std::ostream & operator<<(std::ostream & o, const Fleet & f);
    float totalTax()const;
    unsigned removeOldVehicles(int y1);
};


#endif /*FLEET_H_*/
