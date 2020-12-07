#ifndef SRC_VETERINARY_H_
#define SRC_VETERINARY_H_

#include <string>
#include <sstream>
#include <utility>


class Veterinary {
    std::string name;
    long codOrder;
public:
    Veterinary(std::string nome, long cod);
    std::string getName() const;
    std::string getInfo() const;
};


#endif /* SRC_VETERINARY_H_ */
