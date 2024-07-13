#include "Add.h"
#include "Div.h"
#include "Mul.h"
#include "Operation.h"
#include "Sub.h"
#include "OperationFactory.h"

Operation* OperationFactory::createOperation(operatorType type) {
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
