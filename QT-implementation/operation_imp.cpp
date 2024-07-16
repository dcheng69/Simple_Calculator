#include "operation_imp.h"
#include "widget.h"

#include <QDebug>
#include <limits>
#include <cmath>
#include <stdexcept>

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

Operation* OperationFactory::createOperation(operationType type) {
    Operation* p_oper = nullptr;
    switch (type) {
        case Plus:
            p_oper = new class Add();
            break;
        case Minus:
            p_oper = new class Sub();
            break;
        case Multiply:
            p_oper = new class Mul();
            break;
        case Division:
            p_oper = new class Div();
            break;
        case OpenBracket:
        case CloseBreaket:
        defautl:
            throw new std::runtime_error("invalid operations!");
            break;
    }
    return p_oper;
}
