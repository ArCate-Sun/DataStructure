//
// Created by ACat on 24/11/2017.
//

#ifndef DATASTRUCTURE_ARRAYIMPL_H
#define DATASTRUCTURE_ARRAYIMPL_H

#include "../global/config.h"

class DataStructure::ArrayImpl {
public:
    virtual int capacity() const = 0;
    virtual bool capacity(int size) = 0;
    virtual bool ensureCapacity() = 0;

};

#endif //DATASTRUCTURE_ARRAYIMPL_H
