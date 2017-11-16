//
// Created by ACat on 17/11/2017.
//

#include <iostream>
#include "Double.h"

using namespace std;

Double::Double() {

}

Double::Double(double data) {
    this->data = data;
}

bool Double::compare(const Element *e) const {
    Double *elem = (Double *) e;
    return this == elem || this->data == elem->data;
}

void Double::visit() const {
    cout << this->data;
}

Double &Double::operator=(double data) {
    this->data = data;
    return *this;
}

