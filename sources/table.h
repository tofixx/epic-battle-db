#pragma once

#include <stdint.h>
#include <random>

class Table
{
public:
    Table(int32_t maxRows, int32_t columns);

    virtual ~Table();

    int32_t *m_data;
    int32_t m_maxRows;
    int32_t m_columns;
    int32_t m_numRows; // number of used rows

    virtual int32_t insert(int32_t *values);
    virtual int32_t update(int32_t rowIndex, int32_t *values);
    virtual void overrideColumn(int32_t columnId, int32_t *values);

    int32_t count();
    int32_t size();
    void reset();

    virtual int32_t &getLocation(const int32_t &row, const int32_t &column) = 0;
    virtual std::vector<int32_t> *table_eq_scan(const int32_t &columnId, const int32_t &value) = 0;
    virtual Table *position_list_materialize(std::vector<int32_t> &positions, const int32_t columns, const int32_t *columnIds) = 0;

    void print_row(int32_t row);
    void print(int32_t firstRow, int32_t lastRow);

    // helper
    static uint32_t *getRandomValuesInRange(int32_t numValues, int32_t maxValue);
    static int *generateDistinctValues(int32_t numberOfDistinctValues);
    virtual void generateData(int32_t rows, uint32_t *distinctValues);
    virtual void addDataWithSelectivity(float selectivity, int32_t column, int32_t value);
};
