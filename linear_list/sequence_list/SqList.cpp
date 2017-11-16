//
// Created by ACat on 16/11/2017.
//

#include <iostream>
#include "SqList.h"
#include "../../element/int/Integer.h"

using namespace std;

SqList::SqList() {

//    try {
//        this->data = new T[this->_capacity_init];
//    } catch (bad_alloc &e) {
//        return false;
//    }

    this->data = (Element **) calloc(static_cast<size_t>(this->_capacity_init), sizeof(Element *));
    if (!this->data) return;

    this->_capacity = this->_capacity_init;
    this->_size = 0;
}

SqList::SqList(int size) {

//    try {
//        this->data = new T[size];
//    } catch (bad_alloc &e) {
//        return false;
//    }

    this->data = (Element **) calloc(static_cast<size_t>(size), sizeof(Element *));
    if (!this->data) {
        cerr << "顺序表申请内存失败!" << endl;
        return;
    }

    this->_capacity = size;
    this->_size = 0;
}

SqList::SqList(const SqList &list) {

    this->data = (Element **) calloc(static_cast<size_t>(list._capacity), sizeof(Element *));
    if (!this->data) {
        cerr << "顺序表申请内存失败!" << endl;
        return;
    }
    memcpy(this->data, list.data, sizeof(Element *) * list._size);

    this->_capacity_init = list._capacity_init;
    this->_capacity = list._capacity;
    this->_next_capacity = list._next_capacity;
    this->_capacity_increase = list._capacity_increase;
    this->_size = list._size;
}

SqList::~SqList() {
    free(this->data);
}

bool SqList::clearList() {

    // 若表不存在, 则不能清空表
    if (!this->data) return false;

    this->_size = 0;
    return true;
}

bool SqList::isEmpty() const {
    return !length();
}

int SqList::length() const {
    return this->_size;
}

/**
 * 获取表中指定位置的元素
 * @param index 指定位置
 * @return 返回表中指定位置存在的元素, 若表不存在或指定位置不存在元素则返回 nullptr
 */
Element * SqList::get(int index) const {

    // 若表不存在或指定位置超出表的范围, 则不能获取元素
    if (!this->data || index >= this->_size || index < 0) return nullptr;

    return this->data[index];
}

/**
 * 顺序遍历, 定位元素在表中第一次出现的位置
 * @param e 元素
 * @param fp_compare 比较函数
 * @return 若在表中成功定位元素, 则返回元素的位置; 若未成功定位元素, 则返回 -1
 */
int SqList::locate(const Element *e) const {

    // 若表不存在, 则不能定位元素
    if (!this->data) return -1;

    for (int i = 0; i < length(); ++i) {
        if (this->data[i]->compare(e)) return i;
    }
    return -1;
}

Element * SqList::prior(const Element *curr) const {
    return this->get(this->locate(curr) - 1);
}

Element * SqList::next(const Element *curr) const {
    return this->get(this->locate(curr) + 1);
}

/**
 * 在表的指定位置插入元素
 * @param index 指定位置
 * @param e 带插入元素
 * @return 是否插入成功
 */
bool SqList::insert(int index, const Element *e) {

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
        this->data[index] = const_cast<Element *>(e);
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
        this->data[index] = const_cast<Element *>(e);
        this->_size = index + 1;
    }

    return true;
}

Element * SqList::remove(int index) {

    // 如果表不存在, 则不能删除元素
    if (!this->data) return nullptr;

    // 若位置超出表的范围, 则不能产出元素
    if (index < 0 || index >= this->length()) return nullptr;

    Element * e = this->data[index];
    for (int i = index; i < this->length() - 1; ++i) {
        this->data[i] = this->data[i + 1];
    }
    --this->_size;

    return e;
}

bool SqList::traverse() const {

    // 如果表不存在, 则不能遍历元素
    if (!this->data) return false;

    cout << "[";
    for (int i = 0; i < this->length(); ++i) {
        this->data[i]->visit();
        cout << ", ";
    }
    cout << "]" << endl;

    return true;
}

int SqList::capacity() const {
    return this->_capacity;
}

/**
 * 设置下一次扩容容量
 * @param size 下一次扩容容量
 * @return 操作是否成功
 */
bool SqList::capacity(int size) {

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
bool SqList::increaseCapacity() {

    // 如果表不存在, 则不能扩容
    if (!this->data) return false;

    // 计算扩容后储存空间的大小
    int nextCapacity = this->_next_capacity;
    if (nextCapacity <= this->capacity()) {
        nextCapacity = this->capacity() + this->_capacity_increase;
    }

    Element ** temp = this->data;
    this->data = (Element **) realloc(this->data, nextCapacity * sizeof(Element *));
    // 若重新申请空间失败, 则不能插入元素
    if (!this->data) {
        this->data = temp;
        return false;
    }

    this->_capacity = nextCapacity;
    this->_next_capacity = 0;
    return true;
}









//////////////////////////////////////
// 测试
//////////////////////////////////////
void listInfo(SqList list) {
    cout << "empty: " << boolalpha << list.isEmpty() << endl
         << "length: " << list.length() << endl
         << "capacity: " << list.capacity() << endl;
}


void testSqList() {

    SqList list;

    cout << "顺序表初始化." << endl;
    listInfo(list);
    cout << endl;

    cout << "插入10个元素." << endl;
    for (int i = 0; i < 10; ++i) {
        list.insert(0, new Integer(i));
    }
    cout << "遍历: ";
    list.traverse();
    listInfo(list);
    cout << endl;

    cout << "再插入5个元素." << endl;
    for (int i = 10; i < 15; ++i) {
        list.insert(0, new Integer(i));
    }
    cout << "遍历: ";
    list.traverse();
    listInfo(list);
    cout << endl;

    cout << "设置capacity为50." << endl;
    list.capacity(50);
    cout << endl;

    cout << "再插入10个元素." << endl;
    for (int i = 0; i < 10; ++i) {
        list.insert(0, new Integer(i));
    }
    cout << "遍历: ";
    list.traverse();
    listInfo(list);
    cout << endl;

    Integer elem(5);
    cout << "定位元素5的位置: " << list.locate(&elem) << endl;
    elem = 15;
    cout << "定位元素15的位置: " << list.locate(&elem) << endl << endl;

    cout << "获取第5个位置的元素: ";
    list.get(5)->visit();
    cout << endl;
    cout << "获取第15个位置的元素: ";
    list.get(15)->visit();
    cout << endl << endl;

    cout << "获取元素5之前的元素: ";
    elem = 5;
    list.prior(&elem)->visit();
    cout << endl;
    cout << "获取元素5之后的元素: ";
    elem = 5;
    list.next(&elem)->visit();
    cout << endl << endl;

    for (int i = 0; i < 5; ++i) {
        cout << "删除下标为20个元素元素: ";
        list.remove(20)->visit();
        cout << endl;
    }
    listInfo(list);
    cout << endl;

    cout << "清除顺序表." << endl;
    list.clearList();
    listInfo(list);

}