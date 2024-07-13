#include "Sub.h"
#include <iostream>
#include <limits>
#include <cmath>

double Sub::getResult() {
    double ret = 0.0;
    ret = getNumberA() - getNumberB();

    // Check for overflow by verifying if the result is infinite
    if (std::isinf(ret)) {
        std::cerr << "Sub Operation Overflow detected!" << std::endl;
        // Handle overflow appropriately, e.g., set to a specific value or throw an exception
        ret = std::numeric_limits<double>::infinity();
    }
    return ret;
}
