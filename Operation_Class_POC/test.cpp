#include "Operation.h"
#include "OperationFactory.h"
#include <iostream>

/**
 * The following code is a simple test.
 * Can be implemented with CMake and Google Test framework
 * to perform the unit test functionality!
 */
int main (int argc, char *argv[]) {
    Operation* p_oper = nullptr;
    double ret = 0.0;

    // test Add operation
    p_oper = OperationFactory::createOperation(Add);
    p_oper->setNumberA(1.0);
    p_oper->setNumberB(1.0);
    ret = p_oper->getResult();
    std:: cout << "Add ret: " << ret << std::endl;

    // test Sub operation
    p_oper = OperationFactory::createOperation(Sub);
    p_oper->setNumberA(0.0);
    p_oper->setNumberB(1.0);
    ret = p_oper->getResult();
    std:: cout << "Sub ret: " << ret << std::endl;

    // test Mul operation
    p_oper = OperationFactory::createOperation(Mul);
    p_oper->setNumberA(3.0);
    p_oper->setNumberB(4.0);
    ret = p_oper->getResult();
    std:: cout << "Mul ret: " << ret << std::endl;

    // test Div operation
    p_oper = OperationFactory::createOperation(Div);
    p_oper->setNumberA(3.0);
    p_oper->setNumberB(0.0);
    ret = p_oper->getResult();
    std:: cout << "Div ret: " << ret << std::endl;

    return 0;
}
