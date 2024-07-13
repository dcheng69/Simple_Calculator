#ifndef ADD_H
#define ADD_H

#include "Operation.h"

class Add : public Operation {
    public:
        double getResult() override;
};

#endif // !ADD_H
