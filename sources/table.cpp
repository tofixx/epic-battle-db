#include <iostream>
#include <limits>
#include <assert.h>
#include <algorithm>
#include <random>
#include <stdexcept>

#include "table.h"

Table::Table(int maxRows, int columns)
    : m_maxRows(maxRows), m_columns(columns), m_numRows(0)
{
    m_data = new int32_t[m_columns * maxRows];
}

Table::~Table()
{
    delete[] m_data;
};

/**
* Returns numValues random Values from 1 - maxValues
*/
uint32_t* Table::getRandomUnsignedValuesInRange(int32_t numValues, int32_t maxValue) {
    uint32_t *returnValues = new uint32_t[numValues];
    for (auto i = 0; i < numValues; ++i)
    {
        returnValues[i] = (uint32_t)(std::rand() % maxValue + 1);
    }
    return returnValues;
}

int32_t* Table::getRandomValuesInRange(int32_t numValues, int32_t maxValue)
{
    int32_t *returnValues = new int32_t[numValues];
    for (auto i = 0; i < numValues; ++i)
    {
        returnValues[i] = std::rand() % maxValue + 1;
    }
    return returnValues;
}

int *Table::generateDistinctValues(int32_t numberOfDistinctValues)
{
    int32_t *distinctValues = new int32_t[numberOfDistinctValues];

    for (int i = 0; i < numberOfDistinctValues; i++)
    {
        distinctValues[i] = i;
    }
    return distinctValues;
}


int32_t Table::count()
{
    return m_numRows;
}

int32_t Table::size()
{
    return m_maxRows;
}

void Table::reset()
{
    this->m_numRows = 0;
}
