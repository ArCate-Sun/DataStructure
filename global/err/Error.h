//
// Created by ACat on 25/11/2017.
//

#ifndef DATASTRUCTURE_ERROR_H
#define DATASTRUCTURE_ERROR_H


#include <iostream>
#include "../core.h"

using namespace std;

class DataStructure::Error {

protected:
    string __err_name;
    string __err_msg;
    virtual void initialize() {
        this->__err_name = "Error";
    }

public:
    Error() {
        this->initialize();
    }
    Error(string msg) {
        this->initialize();
        this->__err_msg = msg;
    }

    virtual void printMessage() {
        cerr << "[" << this->__err_name << "] " << this->__err_msg << endl;
    }
};


#endif //DATASTRUCTURE_ERROR_H
