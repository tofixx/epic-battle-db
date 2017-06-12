#include "columnStoreTable.h"

#include <stdlib.h>

ColumnStoreTable::ColumnStoreTable(int32_t maxRows, int32_t maxColumns)
    :Table(maxRows, maxColumns)
{

}

void ColumnStoreTable::generateData(int32_t rows, uint32_t* distinctValues)
{
    for (auto columnIndex = 0; columnIndex < m_maxColumns; columnIndex++) {
        auto columnValues = Table::generateDistinctValues(distinctValues[columnIndex]);

        for (auto rowIndex = 0; rowIndex < rows; rowIndex++) {
            auto valueIndex = rand() % distinctValues[columnIndex];
            m_data[columnIndex * m_maxRows + rowIndex] = columnValues[valueIndex];
        }
        // clear
    }
}
