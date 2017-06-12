#pragma once

#include <stdint.h>
#include <random>

#include "positionList.h"

class Table
{
public:
    Table(int32_t maxRows, int32_t columns);
    virtual ~Table();

    /**
     * Fills the first rows with data
     */
    virtual void generateData(int32_t rows, uint32_t* distinctValues) = 0;
    void insert();

    virtual int32_t & getLocation(const int32_t &row, const int32_t &column) = 0;
    PositionList<int32_t> *table_eq_scan(const int32_t &column_id, const int32_t &value);
    //struct Table *position_list_materialize(struct PositionList *ps, int num_columns, int *column_ids);

protected:
    static int* generateDistinctValues(int32_t numberOfDistinctValues);
    int32_t * m_data;
    int32_t m_maxRows;
    int32_t m_columns;
private:
    static std::random_device randomDevice;
    static std::mt19937 randomGenerator;
    static std::uniform_int_distribution<> randomDistribution;
};
