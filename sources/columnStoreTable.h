#pragma once

#include "table.h"

class ColumnStoreTable : public Table
{
public:
    ColumnStoreTable(int32_t maxRows, int32_t maxColumns);
    virtual ~ColumnStoreTable() = default;

    int32_t &getLocation(const int32_t &row, const int32_t &column) override;
    std::vector<int32_t> *table_eq_scan(const int32_t &columnId, const int32_t &value) override;
    Table *position_list_materialize(std::vector<int32_t> &positions, const int32_t columns, const int32_t *columnIds) override;
};
