//
// Created by ACat on 25/11/2017.
//

#ifndef DATASTRUCTURE_ALLOCATEMEMORYERROR_H
#define DATASTRUCTURE_ALLOCATEMEMORYERROR_H


#include <iostream>
#include "../core.h"
#include "Error.h"

using namespace std;

class DataStructure::AllocateMemoryError : public virtual Error {

protected:
    void initialize() override {
        this->__err_name = "AllocateMemoryError";
    }
public:
    AllocateMemoryError() {
        this->initialize();
    }

    explicit AllocateMemoryError(string msg) {
        this->initialize();
        this->__err_msg = std::move(msg);
    }
};

#endif //DATASTRUCTURE_ALLOCATEMEMORYERROR_H
