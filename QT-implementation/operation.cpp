#include "operation.h"
#include <QDebug>

bool Operation::setNumberA(double num) {
    try {
        _numberA = num;
    } catch (const std::runtime_error &e) {
        qCritical() << "Exception assigning value to _numberA:" << e.what();
        return false;
    }
    return true;
}

bool Operation::setNumberB(double num) {
    try {
        _numberB = num;
    } catch (const std::runtime_error &e) {
        qCritical() << "Exception assigning value to _numberB:" << e.what();
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

