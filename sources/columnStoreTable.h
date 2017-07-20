#pragma once

#include "table.h"

class ColumnStoreTable : public Table
{
public:
    ColumnStoreTable(const int32_t maxRows, const int32_t maxColumns);
    virtual ~ColumnStoreTable() = default;

    int32_t &getLocation(const int32_t &row, const int32_t &column);
    Table *position_list_materialize(const std::vector<int32_t> &positions, const int32_t columns, const int32_t *columnIds);

    // SAME IN ALL STORES BUT HERE TO INLINE getLocation()
    std::vector<int32_t> *table_eq_scan(const int32_t &columnId, const int32_t &value);
    int32_t table_eq_count(const int32_t &columnId, const int32_t &value);
    int32_t insert(const int32_t *values);
    int32_t update(const int32_t rowIndex, const int32_t *values);
    int32_t update(const int32_t rowIndex, const int32_t *columnsIndex, const int32_t columns, const int32_t *values);
    void overrideColumn(const int32_t columnId,const int32_t *values);

    void generateData(const int32_t rows, const uint32_t *distinctValues);
    void addDataWithSelectivity(const float selectivity, const int32_t column, const int32_t value);

    void print_row(const int32_t row);
    void print(const int32_t firstRow, const int32_t lastRow);
};
