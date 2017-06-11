#include "rowStoreTable.h"


RowStoreTable::RowStoreTable(int32_t maxRows, int32_t maxColumns)
    :Table(maxRows, maxColumns)
{

}

void RowStoreTable::generateData(int32_t rows, uint32_t* distinctValues)
{
    // maybe fill row wise instead of column wise for optimal performance
    for (auto columnIndex = 0; columnIndex < m_maxColumns; columnIndex++) {
        
        auto columnValues = Table::generateDistinctValues(distinctValues[columnIndex]);

        for (auto rowIndex = 0; rowIndex < rows; rowIndex++) {
            auto valueIndex = rand() % distinctValues[columnIndex];
            m_data[rowIndex * m_maxColumns + columnIndex] = columnValues[valueIndex];
        }

    }
}
