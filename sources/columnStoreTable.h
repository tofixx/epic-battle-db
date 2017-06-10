#pragma once

#include "table.h"

class ColumnStoreTable: public Table {

public:
    ColumnStoreTable(int32_t maxRows, int32_t maxColumns);
    virtual ~ColumnStoreTable() = default;

    void generateData(int32_t rows, int32_t* distinctValues) override;
};
