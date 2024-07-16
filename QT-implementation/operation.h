#ifndef OPERATION_H
#define OPERATION_H


class Operation
{
private:
    double _numberA = 0.0;
    double _numberB = 0.0;

public:
    bool setNumberA(double num);
    bool setNumberB(double num);
    double getNumberA();
    double getNumberB();
    virtual double getResult() {
        // inline virtual function
        return 0.0;
    }
};

#endif // OPERATION_H
