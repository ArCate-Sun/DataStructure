//
// Created by ACat on 16/11/2017.
//

#ifndef DATASTRUCTURE_ELEMENT_H
#define DATASTRUCTURE_ELEMENT_H

template <class Data>
class Element<Data> {
    virtual bool compare(Element<Data> e) const = 0;
    virtual void visit() const = 0;
};


#endif //DATASTRUCTURE_ELEMENT_H
