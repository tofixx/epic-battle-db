#pragma once

#include "table.h"

class RowStoreTable : public Table
{
public:
    RowStoreTable(int32_t maxRows, int32_t maxColumns);
    virtual ~RowStoreTable() = default;

    int32_t &getLocation(const int32_t &row, const int32_t &column);
    Table *position_list_materialize(std::vector<int32_t> &positions, const int32_t columns, const int32_t *columnIds);
    int32_t insert_row(int32_t *values);
    int32_t update_row(int32_t rowIndex, int32_t *values);

    // SAME IN ALL STORES BUT HERE TO INLINE getLocation()
    std::vector<int32_t> *table_eq_scan(const int32_t &columnId, const int32_t &value);
    void generateData(int32_t rows, uint32_t *distinctValues);
    void addDataWithSelectivity(float selectivity, int32_t column, int32_t value);
    int32_t insert(int32_t *values);
    int32_t update(int32_t rowIndex, int32_t *values);
    void overrideColumn(int32_t columnId, int32_t *values);

    void print_row(int32_t row);
    void print(int32_t firstRow, int32_t lastRow);
};
