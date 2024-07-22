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

class OperationFactory {
public:
    static Operation* createOperation(operationType type);
};

class SmartOperation {
private:
    Operation* p_opr = nullptr;
public:
    SmartOperation(Operation* p_opr): p_opr(p_opr){}
    ~SmartOperation() {
        if (p_opr)
            delete p_opr;
        p_opr = nullptr;
    }
    Operation* getPointer() {
        return p_opr;
    }
};


#endif // OPERATION_IMP_H
