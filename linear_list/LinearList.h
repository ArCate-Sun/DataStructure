//
// Created by ACat on 16/11/2017.
//

#ifndef DATASTRUCTURE_LINEARLIST_H
#define DATASTRUCTURE_LINEARLIST_H

#include "../element/Element.h"

/**
 * 线性表 抽象函数定义
 */

class LinearList {
public:
    virtual ~LinearList() {}
    virtual bool clearList() = 0;
    virtual bool isEmpty() const = 0;
    virtual int length() const = 0;
    virtual Element * get(int index) const = 0;
    virtual int locate(const Element *e) const = 0;
    virtual Element * prior(const Element *curr) const = 0;
    virtual Element * next(const Element *curr) const = 0;
    virtual bool insert(int index, const Element *e) = 0;
    virtual Element * remove(int index) = 0;
    virtual bool traverse() const = 0;
};


#endif //DATASTRUCTURE_LINEARLIST_H
