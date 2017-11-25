//
// Created by ACat on 25/11/2017.
//

#ifndef DATASTRUCTURE_OUTOFINDEXERROR_H
#define DATASTRUCTURE_OUTOFINDEXERROR_H


#include <iostream>
#include "../core.h"

using namespace std;

class DataStructure::OutOfIndexError : public virtual Error {

protected:
    void initialize() override {
        this->__err_name = "OutOfIndexError";
    }
public:
    OutOfIndexError() {
        this->initialize();
    }

    explicit OutOfIndexError(string msg) {
        this->initialize();
        this->__err_msg = std::move(msg);
    }
};


#endif //DATASTRUCTURE_OUTOFINDEXERROR_H
