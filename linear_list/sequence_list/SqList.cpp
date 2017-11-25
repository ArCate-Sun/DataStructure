//
// Created by ACat on 16/11/2017.
//

#include <iostream>
#include "SqList.h"

using namespace std;
using namespace DataStructure;

template <class T>
SqList<T>::SqList() {

    try {
        this->__data = new T[this->__init_capacity];
    } catch (bad_alloc &e) {
        e.what();
    }

    this->__capacity = this->__init_capacity;
    this->__size = 0;
}

template <class T>
SqList<T>::SqList(int size) {

    try {
        this->__data = new T[size];
    } catch (bad_alloc &e) {
        e.what();
    }

    this->__capacity = size;
    this->__size = 0;
}

template <class T>
SqList<T>::SqList(const SqList<T> &list) {

    try {
        this->__data = new T[list.__capacity];
    } catch (bad_alloc &e) {
        e.what();
    }

    for (int i = 0; i < list.length(); ++i) {
        this->__data[i] = list.__data[i];
    }

    this->__init_capacity = list.__init_capacity;
    this->__capacity = list.__capacity;
    this->__next_capacity = list.__next_capacity;
    this->__capacity_increase = list.__capacity_increase;
    this->__size = list.__size;
}

template <class T>
SqList<T>::~SqList() {
    delete[] this->__data;
}

template <class T>
bool SqList<T>::clearList() {

    this->__size = 0;
    return true;
}

template <class T>
bool SqList<T>::isEmpty() const {
    return !this->length();
}

template <class T>
int SqList<T>::length() const {
    return this->__size;
}

template <class T>
T &SqList<T>::get(int index) const {

    // 若表不存在或指定位置超出表的范围, 则不能获取元素
    if (index >= this->__size || index < 0) throw OutOfIndexError();

    return this->__data[index];
}

/**
 * 顺序遍历, 定位元素在表中第一次出现的位置
 * @param e 元素
 * @param fp_compare 比较函数
 * @return 若在表中成功定位元素, 则返回元素的位置; 若未成功定位元素, 则返回 -1
 */
template <class T>
int SqList<T>::locate(const T &e, bool (*fp_compare)(const T &, const T &)) const {

    for (int i = 0; i < this->length(); ++i) {
        if (fp_compare(this->__data[i], e)) return i;
    }
    return -1;
}

template <class T>
T &SqList<T>::prior(const T &curr, bool (*fp_compare)(const T &, const T &)) const {
    return this->get(this->locate(curr, fp_compare) - 1);
}

template <class T>
T &SqList<T>::next(const T &curr, bool (*fp_compare)(const T &, const T &)) const {
    return this->get(this->locate(curr, fp_compare) + 1);
}

/**
 * 在表的指定位置插入元素
 * @param index 指定位置
 * @param e 带插入元素
 * @return 是否插入成功
 */
template <class T>
bool SqList<T>::insert(int index, T &e) {

    // 若表不存在或index < 0, 则不能插入元素
    if (index < 0) throw OutOfIndexError();

    if (index < this->length()) {
        // index小于表长的情况

        // 储存空间已满, 必须扩容, 若扩容失败, 则不能插入元素
        if (this->length() == this->capacity() && !this->ensureCapacity()) return false;

        // 插入元素位置后的所有元素后移一位
        for (int i = this->length(); i > index; --i) {
            this->__data[i] = this->__data[i - 1];
        }
        // 插入元素到指定位置
        this->__data[index] = e;
        ++this->__size;

    } else {
        // index不小于表容量的情况
        if (index >= this->__capacity) {
            // 扩容, 若index不小于下一次扩容的容量, 则重新计算下一次扩容的容量
            if (index >= this->__next_capacity) {
                this->__next_capacity = index + 1;
            }
            // 若扩容失败, 则不能插入元素
            if (!this->ensureCapacity()) return false;
        }

        // 插入元素
        for (int i = index - 1; i >= this->length(); --i) {
            this->__data[i] = 0;
        }
        this->__data[index] = e;
        this->__size = index + 1;
    }

    return true;
}

template <class T>
T SqList<T>::remove(int index) {

    // 若位置超出表的范围, 则不能产出元素
    if (index < 0 || index >= this->length()) throw OutOfIndexError();

    T e = this->__data[index];
    for (int i = index; i < this->length() - 1; ++i) {
        this->__data[i] = this->__data[i + 1];
    }
    --this->__size;

    return e;
}

template <class T>
bool SqList<T>::traverse(void (*fp_visit)(const T &)) const {

    cout << "[";
    for (int i = 0; i < this->length(); ++i) {
        fp_visit(this->__data[i]);
        cout << ", ";
    }
    cout << "]" << endl;

    return true;
}

template <class T>
int SqList<T>::capacity() const {
    return this->__capacity;
}

/**
 * 设置下一次扩容容量
 * @param size 下一次扩容容量
 * @return 操作是否成功
 */
template <class T>
bool SqList<T>::capacity(int size) {

    // 若指定的容量不大于表的当前容量, 则此次操作不生效
    if (size <= this->capacity()) return false;

    this->__next_capacity = size;
    return true;
}

/**
 * 让表的容量扩增.
 * 若下一次扩容容量比当前容量大, 则扩容后的容量与计划的下一次扩容容量相同;
 * 若下一次扩容容量不比当前容量大, 则扩容后的容量为当前容量加每次扩容容量值.
 * 调用这个方法后, 下一次扩容容量将清零.
 * @return 操作十分成功
 */
template <class T>
bool SqList<T>::ensureCapacity() {


    // 计算扩容后储存空间的大小
    int nextCapacity = this->__next_capacity;
    if (nextCapacity <= this->capacity()) {
        nextCapacity = this->capacity() + this->__capacity_increase;
    }

    T *temp;
    try {
        temp = new T[nextCapacity];
    } catch (bad_alloc &e) {
        e.what();
        return false;
    }

    for (int i = 0; i < this->length(); ++i) {
        temp[i] = this->__data[i];
    }

    this->__data = temp;
    this->__capacity = nextCapacity;
    this->__next_capacity = 0;
    return true;
}

template <class T>
T &SqList<T>::operator[](int index) {
    return this->__data[index];
}

//////////////////////////////////////
// 测试
//////////////////////////////////////
template <class T>
void listInfo_sql(SqList<T> list) {
    cout << "empty: " << boolalpha << list.isEmpty() << endl
         << "length: " << list.length() << endl
         << "capacity: " << list.capacity() << endl;
}

bool compare_sql(int const &a, int const &b) {
    return a == b;
}

void visit_sql(const int &a) {
    cout << a;
}

void testSqList() {

    int elem;
    SqList<int> list;

    cout << "顺序表初始化." << endl;
    listInfo_sql(list);
    cout << endl;

    cout << "插入10个元素." << endl;
    for (int i = 0; i < 10; ++i) {
        list.insert(0, i);
    }
    cout << "遍历: ";
    list.traverse(visit_sql);
    listInfo_sql(list);
    cout << endl;

    cout << "list[5]: " << list[5] << endl;
    list[5] = 100;
    cout << "list[5] = 100: " << list[5] << endl << endl;

    cout << "再插入5个元素." << endl;
    for (int i = 10; i < 15; ++i) {
        list.insert(0, i);
    }
    cout << "遍历: ";
    list.traverse(visit_sql);
    listInfo_sql(list);
    cout << endl;

    cout << "设置capacity为50." << endl;
    list.capacity(50);
    cout << endl;

    cout << "再插入10个元素." << endl;
    for (int i = 0; i < 10; ++i) {
        list.insert(0, i);
    }
    cout << "遍历: ";
    list.traverse(visit_sql);
    listInfo_sql(list);
    cout << endl;

    elem = 5;
    cout << "定位元素5的位置: " << list.locate(elem, compare_sql) << endl;
    elem = 15;
    cout << "定位元素15的位置: " << list.locate(elem, compare_sql) << endl << endl;

    cout << "获取第5个位置的元素: ";
    cout << list.get(5) << endl;
    cout << "获取第15个位置的元素: ";
    cout << list.get(15) << endl << endl;

    cout << "获取元素5之前的元素: ";
    elem = 5;
    cout << list.prior(elem, compare_sql) << endl;
    cout << "获取元素5之后的元素: ";
    elem = 5;
    cout << list.next(elem, compare_sql) << endl << endl;

    for (int i = 0; i < 5; ++i) {
        cout << "删除下标为20个元素元素: ";
        cout << list.remove(20) << endl;
    }
    listInfo_sql(list);
    cout << endl;

    cout << "清除顺序表." << endl;
    list.clearList();
    listInfo_sql(list);

}