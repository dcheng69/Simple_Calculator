#include "Div.h"
#include <iostream>
#include <limits>

double Div::getResult() {
    double ret = 0.0;
    if (getNumberB() == 0.0) {
        std::cerr << "Div Operation divided by zero detected!" << std::endl;
        ret = std::numeric_limits<double>::infinity();
        return ret;
    }

    ret = getNumberA() / getNumberB();

    return ret;
}
