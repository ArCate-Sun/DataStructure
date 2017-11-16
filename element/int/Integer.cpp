//
// Created by ACat on 17/11/2017.
//

#include <iostream>
#include "Integer.h"

using namespace std;

Integer::Integer() {

}

Integer::Integer(int data) {
    this->data = data;
}

bool Integer::compare(const Element *e) const {
    Integer * elem = (Integer *) e;
    return this == elem || this->data == elem->data;
}

void Integer::visit() const {
    cout << this->data;
}

Integer &Integer::operator=(int data) {
    this->data = data;
    return *this;
}
