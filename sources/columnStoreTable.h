#pragma once

#include "table.h"

class ColumnStoreTable: public Table {

public:
    ColumnStoreTable(int32_t maxRows, int32_t maxColumns);
    virtual ~ColumnStoreTable() = default;

    void generateData(int32_t rows, uint32_t* distinctValues) override;

    int32_t & getLocation(const int32_t &row, const int32_t &column) override;

};
