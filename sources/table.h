#pragma once

#include <stdint.h>
#include <random>

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
    
    void print_row(int32_t row);
    void print(int32_t firstRow, int32_t lastRow);

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
