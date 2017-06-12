#include "columnStoreTable.h"

#include <stdlib.h>

ColumnStoreTable::ColumnStoreTable(int32_t maxRows, int32_t columns)
    :Table(maxRows, columns)
{

}


int32_t & ColumnStoreTable::getLocation(const int32_t &row, const int32_t &column)
{
    return m_data[column*m_maxRows+row];   
}

void ColumnStoreTable::generateData(int32_t rows, uint32_t* distinctValues)
{
    for (auto columnIndex = 0; columnIndex < m_columns; columnIndex++) {

        auto columnValues = Table::generateDistinctValues(distinctValues[columnIndex]);

        for (auto rowIndex = 0; rowIndex < rows; rowIndex++) {
            auto valueIndex = rand() % distinctValues[columnIndex];
            m_data[columnIndex * m_maxRows + rowIndex] = columnValues[valueIndex];
        }
        delete[] columnValues;
    }
}
