//
// Created by ACat on 16/11/2017.
//

#ifndef DATASTRUCTURE_LINEARLIST_H
#define DATASTRUCTURE_LINEARLIST_H

#include "../global/config.h"

/**
 * 线性表 抽象函数定义
 */

template<class T>
class DataStructure::LinearList {
public:
    virtual ~LinearList() {}

    virtual bool clearList() = 0;
    virtual bool isEmpty() const = 0;
    virtual int length() const = 0;

    virtual bool insert(int index, T &e) = 0;
    virtual bool remove(int index, T &get_e) = 0;

    virtual T &operator[](int index) = 0;
    virtual bool get(int index, T &e) const = 0;
    virtual int locate(const T &e, bool (*fp_compare)(const T &, const T &)) const = 0;
    virtual bool prior(const T &curr, T &get_e, bool (*fp_compare)(const T &, const T &)) const = 0;
    virtual bool next(const T &curr, T &get_e, bool (*fp_compare)(const T &, const T &)) const = 0;
    virtual bool traverse(void (*fp_visit)(const T &)) const = 0;
};


#endif //DATASTRUCTURE_LINEARLIST_H
