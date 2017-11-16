//
// Created by ACat on 16/11/2017.
//

#ifndef DATASTRUCTURE_LINEARLIST_H
#define DATASTRUCTURE_LINEARLIST_H


#include "../element/Element.h"

class LinearList {
public:
    virtual bool initList() = 0;
    virtual bool DestroyList() = 0;
    virtual bool ClearList() = 0;
    virtual bool isEmpty() const = 0;
    virtual int length() const = 0;
    virtual bool get(int index, Element &e) const = 0;
    virtual int locate(Element &e) const = 0;
    virtual bool prior(Element curr, Element &prev) const = 0;
    virtual bool next(Element curr, Element &next) const = 0;
    virtual bool insert(int index, Element e) = 0;
    virtual bool remove(int index, Element &e) = 0;
    virtual bool traverse() const = 0;
};


#endif //DATASTRUCTURE_LINEARLIST_H
