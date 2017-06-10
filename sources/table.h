#pragma once

#include <stdint.h>
#include <random>

class Table
{
public:
    Table(int32_t maxRows, int32_t maxColumns);
    virtual ~Table();

    /**
     * Fills the first rows with data
     */
    void virtual generateData(int32_t rows, int32_t* distinctValues) = 0;
    void insert();

protected:
    static int* generateDistinctValues(int32_t numberOfDistinctValues);
    int32_t * m_data;
    int32_t m_maxRows;
    int32_t m_maxColumns;
private:
    static std::random_device randomDevice;
    static std::mt19937 randomGenerator;
    static std::uniform_int_distribution<> randomDistribution;
};
