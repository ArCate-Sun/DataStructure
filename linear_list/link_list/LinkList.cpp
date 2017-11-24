//
// Created by ACat on 24/11/2017.
//

#include <iostream>
#include "LinkList.h"

using namespace std;
using namespace DataStructure;

template <class T>
LinkList<T>::LinkList() {
    this->__head = new LinkList::Node();
    this->__length = 0;
}

template <class T>
LinkList<T>::LinkList(const LinkList<T> &list) {
    LinkList::Node *nodeT = this->__head;
    LinkList::Node *nodeR = list.__head;
    while ((nodeR = nodeR->next)) {
        nodeT->next = new LinkList::Node();
        nodeT = nodeT->next;
        nodeT->data = nodeR->data;
    }
    this->__length = list.__length;
}

template <class T>
LinkList<T>::~LinkList<T>() {
    LinkList::Node *nodeTemp;
    while (this->__head) {
        nodeTemp = this->__head->next;
        delete this->__head;
        this->__head = nodeTemp;
    }
}

template <class T>
bool LinkList<T>::isEmpty() const {
    return !this->__length;
}

template <class T>
int LinkList<T>::length() const {
    return this->__length;
}

template <class T>
bool LinkList<T>::insert(int index, T &e) {

    // 判断index的范围
    if (index < 0) return false;

    LinkList::Node *pos = this->__head;

    // 找到待插入位置
    for (int i = 0; i < index; ++i) {
        if (!pos->next) {
            pos->next = new LinkList::Node();
            ++this->__length;
        }
        pos = pos->next;
    }

    // 插入数据
    LinkList::Node *temp = pos->next;
    pos->next = new LinkList::Node();
    pos = pos->next;
    pos->data = e;
    pos->next = temp;


    // 表长加一
    ++this->__length;

    return true;
}

template <class T>
bool LinkList<T>::remove(int index, T &get_e) {

    // 判断index的范围
    if (index < 0 || index >= this->__length) return false;

    LinkList::Node *pos = this->__head;

    // 找到待删除的位置
    for (int i = 0; i < index; ++i) {
        pos = pos->next;
    }

    LinkList::Node *del = pos->next;
    LinkList::Node *temp = del->next;
    get_e = del->data;
    delete del;
    pos->next = temp;

    --this->__length;

    return true;
}

template <class T>
bool LinkList<T>::clearList() {

    LinkList::Node *nodeDel;
    LinkList::Node *nodeTemp;

    while ((nodeDel = this->__head->next)) {
        nodeTemp = nodeDel->next;
        delete nodeDel;
        this->__head->next = nodeTemp;
    }

    this->__length = 0;

    return true;
}

template <class T>
T &LinkList<T>::operator[](int index) {

    // 判断index的范围
    if (index < 0 || index >= this->__length) {
        throw "错误的下标范围";
    }

    LinkList::Node *pos = this->__head->next;

    // 找到index位置
    for (int i = 0; i < index; ++i) {
        pos = pos->next;
    }

    return pos->data;
}

template <class T>
bool LinkList<T>::get(int index, T &e) const {

    // 判断index的范围
    if (index < 0 || index >= this->__length) return false;

    LinkList::Node *pos = this->__head->next;

    // 找到index位置
    for (int i = 0; i < index; ++i) {
        pos = pos->next;
    }

    e = pos->data;

    return true;
}

template <class T>
int LinkList<T>::locate(const T &e, bool (*fp_compare)(const T &, const T &)) const {

    LinkList::Node *node = this->__head;
    for (int i = 0; i < this->__length; ++i) {
        node = node->next;
        if (fp_compare(node->data, e)) {
            return i;
        }
    }

    return -1;
}

template <class T>
bool LinkList<T>::prior(const T &curr, T &get_e, bool (*fp_compare)(const T &, const T &)) const {
    return this->get(this->locate(curr, fp_compare) - 1, get_e);
}

template <class T>
bool LinkList<T>::next(const T &curr, T &get_e, bool (*fp_compare)(const T &, const T &)) const {
    return this->get(this->locate(curr, fp_compare) + 1, get_e);;
}

template <class T>
bool LinkList<T>::traverse(void (*fp_visit)(const T &)) const {

    LinkList::Node *node = this->__head;
    cout << "[";
    for (int i = 0; i < this->__length; ++i) {
        node = node->next;
        fp_visit(node->data);
        cout << ", ";
    }
    cout << "]" << endl;
    return true;
}

template <class T>
void listInfo_ll(LinkList<T> &list) {
    cout << "empty: " << boolalpha << list.isEmpty() << endl
         << "length: " << list.length() << endl;
}

bool compare_ll(int const &a, int const &b) {
    return a == b;
}

void visit_ll(const int & a) {
    cout << a;
}

void testLinkList() {

    int elem, get_elem;
    LinkList<int> list;

    cout << "顺序表初始化." << endl;
    listInfo_ll(list);
    cout << endl;

    cout << "插入10个元素." << endl;
    for (int i = 0; i < 10; ++i) {
        list.insert(0, i);
    }
    cout << "遍历: ";
    list.traverse(visit_ll);
    listInfo_ll(list);
    cout << endl;

    cout << "list[5]: " << list[5] << endl;
    list[5] = 100;
    cout << "list[5] = 100: " << list[5] << endl << endl;

    cout << "在位置15插入5个元素." << endl;
    for (int i = 10; i < 15; ++i) {
        list.insert(15, i);
    }
    cout << "遍历: ";
    list.traverse(visit_ll);
    listInfo_ll(list);
    cout << endl;

    cout << "再插入30个元素." << endl;
    for (int i = 0; i < 10; ++i) {
        list.insert(30, i);
    }
    cout << "遍历: ";
    list.traverse(visit_ll);
    listInfo_ll(list);
    cout << endl;

    elem = 5;
    cout << "定位元素5的位置: " << list.locate(elem, compare_ll) << endl;
    elem = 15;
    cout << "定位元素15的位置: " << list.locate(elem, compare_ll) << endl << endl;

    cout << "获取第5个位置的元素: ";
    list.get(5, get_elem);
    cout << get_elem << endl;
    cout << "获取第15个位置的元素: ";
    list.get(15, get_elem);
    cout << get_elem << endl << endl;

    cout << "获取元素5之前的元素: ";
    elem = 5;
    list.prior(elem, get_elem, compare_ll);
    cout << get_elem << endl;
    cout << "获取元素5之后的元素: ";
    elem = 5;
    list.next(elem, get_elem, compare_ll);
    cout << get_elem << endl << endl;

    for (int i = 0; i < 5; ++i) {
        cout << "删除下标为20个元素元素: ";
        list.remove(20, get_elem);
        cout << get_elem << endl;
    }
    listInfo_ll(list);
    cout << endl;

    cout << "清除顺序表." << endl;
    list.clearList();
    listInfo_ll(list);
}
