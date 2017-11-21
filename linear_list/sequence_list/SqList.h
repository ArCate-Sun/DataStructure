//
// Created by ACat on 16/11/2017.
//

#ifndef DATASTRUCTURE_SQLIST_H
#define DATASTRUCTURE_SQLIST_H

#include "../LinearList.h"

/**
 * 顺序表 的定义
 */
template <class T>
class SqList : public virtual LinearList<T> {

private:
    T * data;
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

    bool get(int index, T &get_e) const override;

    int locate(const T &e, bool (*fp_compare)(const T &, const T &)) const override;

    bool prior(const T &curr, T &get_e, bool (*fp_compare)(const T &, const T &)) const override;

    bool next(const T &curr, T &get_e, bool (*fp_compare)(const T &, const T &)) const override;

    bool insert(int index, T &e) override;

    bool remove(int index, T &get_e) override;

    bool traverse(void (*fp_visit)(const T &)) const override;

    int capacity() const;

    bool capacity(int size);

    bool increaseCapacity();

    T &operator[](int index);

};

void testSqList();

#endif //DATASTRUCTURE_SQLIST_H
