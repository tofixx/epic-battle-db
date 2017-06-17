#include <iostream>

#include "rowStoreTable.h"

RowStoreTable::RowStoreTable(int32_t maxRows, int32_t columns)
    :Table(maxRows, columns)
{

}

void RowStoreTable::generateData(int32_t rows, uint32_t* distinctValues)
{
    // maybe fill row wise instead of column wise for optimal performance
    for (auto columnIndex = 0; columnIndex < m_columns; columnIndex++) {
        
        auto columnValues = Table::generateDistinctValues(distinctValues[columnIndex]);

        for (auto rowIndex = 0; rowIndex < rows; rowIndex++) {
            auto valueIndex = rand() % distinctValues[columnIndex];
            m_data[rowIndex * m_columns + columnIndex] = columnValues[valueIndex];
        }

        delete[] columnValues;
    }
}
