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
class SqList : public virtual LinearList {

private:
    T *data;
    int _size;
    int _capacity;
    int _next_capacity;
    int _capacity_init = 10;
    int _capacity_increase = 10;

public:

    bool initList() override;

    bool initList(int size);

    bool DestroyList() override;

    bool ClearList() override;

    bool isEmpty() const override;

    int length() const override;

    T get(int index) const override;

    int locate(T &e, bool *fp_compare(T, T)) const override;

    T prior(T curr, bool *fp_compare(T, T)) const override;

    T next(T curr, bool *fp_compare(T, T)) const override;

    bool insert(int index, T e) override;

    T remove(int index) override;

    bool traverse(void *fp_visit(T)) const override;

    int capacity() const;

    bool capacity(int size);

    bool increaseCapacity();

};


#endif //DATASTRUCTURE_SQLIST_H
