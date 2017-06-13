#include <iostream>
#include <limits>

#include "table.h"
#include "positionList.h"


Table::Table(int maxRows, int columns)
  : m_maxRows(maxRows)
  , m_columns(columns)
{
    m_data = new int32_t[m_columns * maxRows];
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

/// <returns>return value on heap!</returns>
PositionList<int32_t>* Table::table_eq_scan(const int32_t &column_id, const int32_t &value)
{
    auto* list = new PositionList<int32_t>();
    for(auto row = 0; row < m_maxRows; ++row)
    {
        if (getLocation(row, column_id) == value)
        {
            list->add(row);
        }
    }
    return list;
}


std::random_device Table::randomDevice;
std::mt19937 Table::randomGenerator = std::mt19937(Table::randomDevice()); // seed the generator
std::uniform_int_distribution<> Table::randomDistribution = std::uniform_int_distribution<>(std::numeric_limits<int32_t>::lowest(), std::numeric_limits<int32_t>::max()); // define the range

int* Table::generateDistinctValues(int32_t numberOfDistinctValues) {
    int32_t* distinctValues = new int32_t[numberOfDistinctValues];

    for (int i = 0; i < numberOfDistinctValues; i++) {
        //Table::randomDistribution(Table::randomGenerator);
        //distinctValues[i] = Table::randomDistribution(Table::randomGenerator);
        // TODO: should check if really distinct

        // alternative:
        distinctValues[i] = i;
    }
    return distinctValues;
}
