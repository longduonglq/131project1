//
// Created by dop on 2/17/21.
//

#ifndef PROJ1_ABSTRACTCOLUMN_H
#define PROJ1_ABSTRACTCOLUMN_H
#include <iostream>

class AbstractColumn
{
public:
    AbstractColumn() = default;
    virtual ~AbstractColumn() {};

    virtual const int getColumnWidth() const = 0;
    virtual const std::size_t getSize() = 0;
    virtual void dumpNext(std::wostream& os) = 0;
    virtual void reset() = 0;
};

#endif //PROJ1_ABSTRACTCOLUMN_H
