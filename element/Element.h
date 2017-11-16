//
// Created by ACat on 16/11/2017.
//

#ifndef DATASTRUCTURE_ELEMENT_H
#define DATASTRUCTURE_ELEMENT_H

class Element {
public:
    virtual bool compare(const Element *e) const = 0;
    virtual void visit() const = 0;
};


#endif //DATASTRUCTURE_ELEMENT_H
