#pragma once

#include "table.h"

class ColumnStoreTable: public Table {

public:
    ColumnStoreTable(int32_t maxRows, int32_t maxColumns);
    virtual ~ColumnStoreTable() = default;

    void generateData(int32_t rows, uint32_t* distinctValues) override;

    void print_row(int32_t row) override;
};
