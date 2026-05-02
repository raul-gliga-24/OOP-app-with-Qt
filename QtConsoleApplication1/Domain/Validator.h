//
// Created by raulg on 3/28/2026.
//

#ifndef LAB67_VALIDATOR_H
#define LAB67_VALIDATOR_H
#include "../Domain/Masina.h"
#include <stdexcept>
class ValidationError : public std::runtime_error{

private:
public:
    explicit ValidationError(const char* msg) : std::runtime_error(msg)
    {};
};

class MasinaValidator {
private:
public:
    void validator(const Masina& m);

};

#endif //LAB67_VALIDATOR_H