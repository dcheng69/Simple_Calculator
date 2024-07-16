#include "operation_imp.h"

#include <QDebug>
#include <limits>
#include <cmath>

double Add::getResult() {
    double ret = 0.0;
    ret = getNumberA() + getNumberB();

    // check for overflow
    if (std::isinf(ret)) {
        qDebug() << "Add Operation Overflow!";
        ret = std::numeric_limits<double>::infinity();
    }
    return ret;
}

double Sub::getResult() {
    double ret = 0.0;
    ret = getNumberA() - getNumberB();

    // check for overflow
    if (std::isinf(ret)) {
        qDebug() << "Sub Operation Overflow!";
        ret = std::numeric_limits<double>::infinity();
    }
    return ret;
}

double Mul::getResult() {
    double ret = 0.0;
    ret = getNumberA() * getNumberB();

    // check for overflow
    if (std::isinf(ret)) {
        qDebug() << "Mul Operation Overflow!";
        ret = std::numeric_limits<double>::infinity();
    }
    return ret;
}

double Div::getResult() {
    double ret = 0.0;
    if (getNumberB() == 0.0) {
        qCritical() << "Divided by zero!";
        throw std::runtime_error("Divided by zero!");
        return ret;
    }
    ret = getNumberA() / getNumberB();
    return ret;
}

Operation* OperationFactory::createOperation(operationImpType type) {
    Operation* p_oper = nullptr;
    switch (type) {
        case Add:
            p_oper = new class Add();
            break;
        case Sub:
            p_oper = new class Sub();
            break;
        case Mul:
            p_oper = new class Mul();
            break;
        case Div:
            p_oper = new class Div();
            break;
    }
    return p_oper;
}
