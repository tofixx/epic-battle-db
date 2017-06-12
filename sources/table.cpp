#include "table.h"

#include <iostream>
#include <limits>

Table::Table(int maxRows, int columns)
  : m_maxRows(maxRows)
  , m_columns(columns)
{
    m_data = new int[m_columns * maxRows];
}

Table::~Table() 
{
    delete[] m_data;
};

void Table::insert()
{
    // insert...
    std::cout << "insert..." << std::endl;
}


std::random_device Table::randomDevice;
std::mt19937 Table::randomGenerator = std::mt19937(Table::randomDevice()); // seed the generator
std::uniform_int_distribution<> Table::randomDistribution = std::uniform_int_distribution<>(std::numeric_limits<int32_t>::lowest(), std::numeric_limits<int32_t>::max()); // define the range

int* Table::generateDistinctValues(int32_t numberOfDistinctValues) {
    int32_t* distinctValues = new int32_t[numberOfDistinctValues];

    for (int i = 0; i < numberOfDistinctValues; i++) {
        Table::randomDistribution(Table::randomGenerator);
        distinctValues[i] = Table::randomDistribution(Table::randomGenerator);
        // TODO: should check if really distinct
    }
    return distinctValues;
}
