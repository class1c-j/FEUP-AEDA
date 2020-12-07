#include "veterinary.h"

Veterinary::Veterinary(std::string nome, long cod) : name(std::move(nome)), codOrder(cod) {
}

std::string Veterinary::getName() const {
    return name;
}

std::string Veterinary::getInfo() const {
    std::stringstream ss;
    ss << this->name << ", " << this->codOrder;
    return ss.str();
}


