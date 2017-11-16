//
// Created by ACat on 17/11/2017.
//

#ifndef DATASTRUCTURE_INTEGER_H
#define DATASTRUCTURE_INTEGER_H


#include "../Element.h"

class Integer : public Element {
private:
    int data;
public:
    Integer();

    Integer(int data);

    bool compare(const Element *e) const override;

    void visit() const override;

    Integer &operator=(int data);
};


#endif //DATASTRUCTURE_INTEGER_H
