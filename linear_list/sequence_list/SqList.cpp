//
// Created by ACat on 16/11/2017.
//

#include <iostream>
#include "SqList.h"

using namespace std;

template <class T>
SqList<T>::SqList() {

    try {
        this->data = new T[this->_capacity_init];
    } catch (bad_alloc &e) {
        cerr << "顺序表申请内存失败!" << endl;
        return;
    }

    this->_capacity = this->_capacity_init;
    this->_size = 0;
}

template <class T>
SqList<T>::SqList(int size) {

    try {
        this->data = new T[size];
    } catch (bad_alloc &e) {
        cerr << "顺序表申请内存失败!" << endl;
        return;
    }

    this->_capacity = size;
    this->_size = 0;
}

template <class T>
SqList<T>::SqList(const SqList &list) {

    try {
        this->data = new T[list._capacity];
    } catch (bad_alloc &e) {
        cerr << "顺序表申请内存失败!" << endl;
        return;
    }

    for (int i = 0; i < list.length(); ++i) {
        this->data[i] = list.data[i];
    }

    this->_capacity_init = list._capacity_init;
    this->_capacity = list._capacity;
    this->_next_capacity = list._next_capacity;
    this->_capacity_increase = list._capacity_increase;
    this->_size = list._size;
}

template <class T>
SqList<T>::~SqList() {
    delete[] this->data;
}

template <class T>
bool SqList<T>::clearList() {

    // 若表不存在, 则不能清空表
    if (!this->data) return false;

    this->_size = 0;
    return true;
}

template <class T>
bool SqList<T>::isEmpty() const {
    return !length();
}

template <class T>
int SqList<T>::length() const {
    return this->_size;
}

template <class T>
bool SqList<T>::get(int index, T &get_e) const {

    // 若表不存在或指定位置超出表的范围, 则不能获取元素
    if (!this->data || index >= this->_size || index < 0) return false;

    get_e = this->data[index];
    return true;
}

/**
 * 顺序遍历, 定位元素在表中第一次出现的位置
 * @param e 元素
 * @param fp_compare 比较函数
 * @return 若在表中成功定位元素, 则返回元素的位置; 若未成功定位元素, 则返回 -1
 */
template <class T>
int SqList<T>::locate(const T &e, bool (*fp_compare)(const T &, const T &)) const {

    // 若表不存在, 则不能定位元素
    if (!this->data) return -1;

    for (int i = 0; i < length(); ++i) {
        if (fp_compare(this->data[i], e)) return i;
    }
    return -1;
}

template <class T>
bool SqList<T>::prior(const T &curr, T &get_e, bool (*fp_compare)(const T &, const T &)) const {
    return this->get(this->locate(curr, fp_compare) - 1, get_e);
}

template <class T>
bool SqList<T>::next(const T &curr, T &get_e, bool (*fp_compare)(const T &, const T &)) const {
    return this->get(this->locate(curr, fp_compare) + 1, get_e);
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
    if (!this->data || index < 0) return false;

    if (index < this->length()) {
        // index小于表长的情况

        // 储存空间已满, 必须扩容, 若扩容失败, 则不能插入元素
        if (this->length() == this->capacity() && !this->increaseCapacity()) return false;

        // 插入元素位置后的所有元素后移一位
        for (int i = this->length(); i > index; --i) {
            this->data[i] = this->data[i - 1];
        }
        // 插入元素到指定位置
        this->data[index] = e;
        ++this->_size;

    } else {
        // index不小于表容量的情况
        if (index >= this->_capacity) {
            // 扩容, 若index不小于下一次扩容的容量, 则重新计算下一次扩容的容量
            if (index >= this->_next_capacity) {
                this->_next_capacity = index + 1;
            }
            // 若扩容失败, 则不能插入元素
            if (!this->increaseCapacity()) return false;
        }

        // 插入元素
        for (int i = index - 1; i >= this->length(); --i) {
            this->data[i] = 0;
        }
        this->data[index] = e;
        this->_size = index + 1;
    }

    return true;
}

template <class T>
bool SqList<T>::remove(int index, T &get_e) {

    // 如果表不存在, 则不能删除元素
    if (!this->data) return false;

    // 若位置超出表的范围, 则不能产出元素
    if (index < 0 || index >= this->length()) return false;

    T e = this->data[index];
    for (int i = index; i < this->length() - 1; ++i) {
        this->data[i] = this->data[i + 1];
    }
    --this->_size;

    get_e = e;
    return true;
}

template <class T>
bool SqList<T>::traverse(void (*fp_visit)(const T &)) const {

    // 如果表不存在, 则不能遍历元素
    if (!this->data) return false;

    cout << "[";
    for (int i = 0; i < this->length(); ++i) {
        fp_visit(this->data[i]);
        cout << ", ";
    }
    cout << "]" << endl;

    return true;
}

template <class T>
int SqList<T>::capacity() const {
    return this->_capacity;
}

/**
 * 设置下一次扩容容量
 * @param size 下一次扩容容量
 * @return 操作是否成功
 */
template <class T>
bool SqList<T>::capacity(int size) {

    // 如果表不存在, 则不能设置下一次扩容容量
    if (!this->data) return false;

    // 若指定的容量不大于表的当前容量, 则此次操作不生效
    if (size <= this->capacity()) return false;

    this->_next_capacity = size;
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
bool SqList<T>::increaseCapacity() {

    // 如果表不存在, 则不能扩容
    if (!this->data) return false;

    // 计算扩容后储存空间的大小
    int nextCapacity = this->_next_capacity;
    if (nextCapacity <= this->capacity()) {
        nextCapacity = this->capacity() + this->_capacity_increase;
    }

    T *temp = this->data;
    try {
        this->data = new T[nextCapacity];
    } catch (bad_alloc &e) {
        // 若重新申请空间失败, 则不能插入元素
        this->data = temp;
        return false;
    }

    for (int i = 0; i < this->length(); ++i) {
        this->data[i] = temp[i];
    }

    this->_capacity = nextCapacity;
    this->_next_capacity = 0;
    return true;
}


//////////////////////////////////////
// 测试
//////////////////////////////////////
template <class T>
void listInfo(SqList<T> list) {
    cout << "empty: " << boolalpha << list.isEmpty() << endl
         << "length: " << list.length() << endl
         << "capacity: " << list.capacity() << endl;
}



bool compare(int const &a, int const &b) {
    return a == b;
}

void visit(const int & a) {
    cout << a;
}

void testSqList() {

    int elem, get_elem;
    SqList<int> list;

    cout << "顺序表初始化." << endl;
    listInfo(list);
    cout << endl;

    cout << "插入10个元素." << endl;
    for (int i = 0; i < 10; ++i) {
        list.insert(0, i);
    }
    cout << "遍历: ";
    list.traverse(visit);
    listInfo(list);
    cout << endl;

    cout << "再插入5个元素." << endl;
    for (int i = 10; i < 15; ++i) {
        list.insert(0, i);
    }
    cout << "遍历: ";
    list.traverse(visit);
    listInfo(list);
    cout << endl;

    cout << "设置capacity为50." << endl;
    list.capacity(50);
    cout << endl;

    cout << "再插入10个元素." << endl;
    for (int i = 0; i < 10; ++i) {
        list.insert(0, i);
    }
    cout << "遍历: ";
    list.traverse(visit);
    listInfo(list);
    cout << endl;

    elem = 5;
    cout << "定位元素5的位置: " << list.locate(elem, compare) << endl;
    elem = 15;
    cout << "定位元素15的位置: " << list.locate(elem, compare) << endl << endl;

    cout << "获取第5个位置的元素: ";
    list.get(5, get_elem);
    cout << get_elem << endl;
    cout << "获取第15个位置的元素: ";
    list.get(15, get_elem);
    cout << get_elem << endl << endl;

    cout << "获取元素5之前的元素: ";
    elem = 5;
    list.prior(elem, get_elem, compare);
    cout << get_elem << endl;
    cout << "获取元素5之后的元素: ";
    elem = 5;
    list.next(elem, get_elem, compare);
    cout << get_elem << endl << endl;

    for (int i = 0; i < 5; ++i) {
        cout << "删除下标为20个元素元素: ";
        list.remove(20, get_elem);
        cout << get_elem << endl;
    }
    listInfo(list);
    cout << endl;

    cout << "清除顺序表." << endl;
    list.clearList();
    listInfo(list);

}