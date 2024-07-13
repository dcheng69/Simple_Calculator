#include "Operation.h"
#include <stdexcept>
#include <iostream>

bool Operation::setNumberA(double num) {
    try {
        _numberA = num;
    } catch (const std::runtime_error &e) {
        std::cerr << "Cauget an exception while assign value:" << num << " to _numberA: " << e.what() << std::endl;
        return false;
    }
    return true;
}

bool Operation::setNumberB(double num) {
    try {
        _numberB = num;
    } catch (const std::runtime_error &e) {
        std::cerr << "Cauget an exception while assign value:" << num << " to _numberB: " << e.what() << std::endl;
        return false;
    }
    return true;
}

double Operation::getNumberA() {
    return _numberA;
}

double Operation::getNumberB() {
    return _numberB;
}
