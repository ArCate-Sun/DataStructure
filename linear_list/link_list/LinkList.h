//
// Created by ACat on 24/11/2017.
//

#ifndef DATASTRUCTURE_LINKLIST_H
#define DATASTRUCTURE_LINKLIST_H


#include "../LinearList.h"

template <class T>
class DataStructure::LinkList : public virtual LinearList<T> {

private:


protected:
    static const static struct Node {
        T data;
        Node *next;
    };
    Node *__head;
    int __length;

public:

    LinkList();
    LinkList(const LinkList<T> &list);
    ~LinkList() override;

    bool isEmpty() const override;
    int length() const override;

    bool insert(int index, T &e) override;
    bool remove(int index, T &get_e) override;
    bool clearList() override;

    T &operator[](int index) override;
    bool get(int index, T &e) const override;
    int locate(const T &e, bool (*fp_compare)(const T &, const T &)) const override;
    bool prior(const T &curr, T &get_e, bool (*fp_compare)(const T &, const T &)) const override;
    bool next(const T &curr, T &get_e, bool (*fp_compare)(const T &, const T &)) const override;
    bool traverse(void (*fp_visit)(const T &)) const override;

};

void testLinkList();


#endif //DATASTRUCTURE_LINKLIST_H
