#ifndef OPERATION_IMP_H
#define OPERATION_IMP_H

#include "operation.h"
#include "widget.h"

class Add : public Operation {
public:
    double getResult() override;
};

class Sub : public Operation {
public:
    double getResult() override;
};

class Mul : public Operation {
public:
    double getResult() override;
};

class Div : public Operation {
public:
    double getResult() override;
};

typedef enum {
    Add = 0,
    Sub,
    Mul,
    Div
} operationImpType;

class OperationFactory {
public:
    static Operation* createOperation(operationImpType type);
};


#endif // OPERATION_IMP_H
