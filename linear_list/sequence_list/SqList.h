//
// Created by ACat on 16/11/2017.
//

#ifndef DATASTRUCTURE_SQLIST_H
#define DATASTRUCTURE_SQLIST_H

#include "../LinearList.h"

/**
 * 顺序表 的定义
 */
class SqList : public virtual LinearList {

private:
    Element ** data;
    int _size;
    int _capacity;
    int _next_capacity;
    int _capacity_init = 10;
    int _capacity_increase = 10;

public:

    SqList();

    SqList(int size);

    SqList(const SqList &list);

    ~SqList() override;

    bool clearList() override;

    bool isEmpty() const override;

    int length() const override;

    Element * get(int index) const override;

    int locate(const Element *e) const override;

    Element * prior(const Element *curr) const override;

    Element * next(const Element *curr) const override;

    bool insert(int index, const Element *e) override;

    Element * remove(int index) override;

    bool traverse() const override;

    int capacity() const;

    bool capacity(int size);

    bool increaseCapacity();

};

void testSqList();

#endif //DATASTRUCTURE_SQLIST_H
