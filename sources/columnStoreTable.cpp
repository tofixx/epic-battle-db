#include <iostream>
#include "columnStoreTable.h"

#include <stdlib.h>

ColumnStoreTable::ColumnStoreTable(int32_t maxRows, int32_t columns)
    :Table(maxRows, columns)
{

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

void ColumnStoreTable::print_row(int32_t row)
{
    std::cout << "col_"<< row <<"[";
    for(auto i = 0; i < m_columns; ++i)
    {
        std::cout << m_data[m_columns * i + row];
        if(i<(m_columns-1)) std::cout << ", ";
    }
    std::cout << "]" << std::endl;
}
