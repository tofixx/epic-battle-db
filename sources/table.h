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
    int32_t m_numRows;

    int32_t count();
    int32_t size();
    void reset();

    // helper
    static uint32_t *getRandomUnsignedValuesInRange(int32_t numValues, int32_t maxValue);
    static int32_t *getRandomValuesInRange(int32_t numValues, int32_t maxValue);
    static int *generateDistinctValues(int32_t numberOfDistinctValues);

};
