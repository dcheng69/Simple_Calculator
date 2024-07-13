#ifndef OPERATION_H
#define OPERATION_H

class Operation {
    private:
        double _numberA = 0;
        double _numberB = 0;

    public:
        bool setNumberA(double num);
        double getNumberA();
        bool setNumberB(double num);
        double getNumberB();
        virtual double getResult() {
            // inline virtual function
            double result = 0;
            return result;
        };
};

#endif // ! OPERATION_H
