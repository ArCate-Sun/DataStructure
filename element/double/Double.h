//
// Created by ACat on 17/11/2017.
//

#ifndef DATASTRUCTURE_DOUBLE_H
#define DATASTRUCTURE_DOUBLE_H


#include "../Element.h"

class Double : public Element {
private:
    double data;

public:
    Double();

    Double(double data);

    bool compare(const Element *e) const override;

    void visit() const override;

    Double &operator=(double data);
};


#endif //DATASTRUCTURE_DOUBLE_H
