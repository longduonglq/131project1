//
// Created by dop on 2/13/21.
//

#ifndef PROJ1_TABLE_H
#define PROJ1_TABLE_H

#include <iostream>
#include <numeric>
#include <algorithm>
#include <vector>
#include <type_traits>
#include <sstream>
#include "configuration.h"
#include "AbstractColumn.h"

class Table {
public:
    int tableWidth;

    Table(const std::vector<AbstractColumn*>& _columns, std::wstring _title);
    Table(const std::vector<AbstractColumn*>& _columns, std::wstring _title, int _consoleWidth, bool selfCentered=true);

    std::wstring nSpace(int n) const;
    std::wstring doubleLine(int n) const;
    std::wstring singleLine(int n);

    void dumpTableTo(std::wostream& os) const;

    ~Table();

private:
    int consoleWidth;
    std::wstring title;
    // Must use polymorphism because Columns
    // might contains items of different types.
    std::vector<AbstractColumn*> columns;
    int leftPadding, rightPadding;
};

#endif //PROJ1_TABLE_H
