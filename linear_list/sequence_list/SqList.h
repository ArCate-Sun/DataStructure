//
// Created by ACat on 16/11/2017.
//

#ifndef DATASTRUCTURE_SQLIST_H
#define DATASTRUCTURE_SQLIST_H

#include "../../global/core.h"

/**
 * 顺序表 的定义
 */
template <class T>
class DataStructure::SqList : public virtual LinearList<T>, public virtual ArrayImpl {

protected:
    T * __data;
    int __size;
    int __capacity;
    int __next_capacity;
    int __init_capacity = 10;
    int __capacity_increase = 10;

public:

    SqList();
    SqList(int size);
    SqList(const SqList<T> &list);
    ~SqList() override;

    bool isEmpty() const override;
    int length() const override;

    bool insert(int index, T &e) override;
    T remove(int index) override;
    bool clearList() override;

    T &operator[](int index) override;
    T &get(int index) const override;
    int locate(const T &e, bool (*fp_compare)(const T &, const T &)) const override;
    T &prior(const T &curr, bool (*fp_compare)(const T &, const T &)) const override;
    T &next(const T &curr, bool (*fp_compare)(const T &, const T &)) const override;
    bool traverse(void (*fp_visit)(const T &)) const override;

    int capacity() const override ;
    bool capacity(int size) override ;
    bool ensureCapacity() override ;

};

void testSqList();

#endif //DATASTRUCTURE_SQLIST_H
