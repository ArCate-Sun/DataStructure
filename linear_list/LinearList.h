//
// Created by ACat on 16/11/2017.
//

#ifndef DATASTRUCTURE_LINEARLIST_H
#define DATASTRUCTURE_LINEARLIST_H

/**
 * 线性表 抽象函数定义
 */

template <class T>
class LinearList<T> {
public:
    virtual bool initList() = 0;
    virtual bool DestroyList() = 0;
    virtual bool ClearList() = 0;
    virtual bool isEmpty() const = 0;
    virtual int length() const = 0;
    virtual T get(int index) const = 0;
    virtual int locate(T &e, bool *fp_compare(T, T)) const = 0;
    virtual T prior(T curr, bool *fp_compare(T, T)) const = 0;
    virtual T next(T curr, bool *fp_compare(T, T)) const = 0;
    virtual bool insert(int index, T e) = 0;
    virtual T remove(int index) = 0;
    virtual bool traverse(void *fp_visit(T)) const = 0;
};


#endif //DATASTRUCTURE_LINEARLIST_H
