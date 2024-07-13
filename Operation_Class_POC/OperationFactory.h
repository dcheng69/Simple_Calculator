#ifndef OPERATIONFACTORY_H

#include "Operation.h"
#include <string>

typedef enum {
    Add = 0,
    Sub,
    Mul,
    Div
} operatorType;

class OperationFactory {
    public:
        static Operation* createOperation(operatorType type);
};

#endif // !OPERATIONFACTORY_H
