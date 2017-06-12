#pragma once

#include "table.h"

class RowStoreTable: public Table {

public:
    RowStoreTable(int32_t maxRows, int32_t maxColumns);
    virtual ~RowStoreTable() = default;

    void generateData(int32_t rows, uint32_t* distinctValues) override;

    int32_t & getLocation(const int32_t &row, const int32_t &column) override;
    
};
