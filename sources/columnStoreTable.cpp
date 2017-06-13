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

/// return value on heap!
Table* Table::position_list_materialize(const &PositionList positions, const int32_t columns, const int32_t *column_ids)
{
    Table table = new RowStoreTable(positions.size(), columns);

    for (auto row = list->m_positions.begin(); row != list->m_positions.end(); ++row) 
    {
        std::vector<int32_t> copy_row(columns);
        for(auto column = columns_ids[0]; column < columns; ++column)
        {
            copy_row.insert(this->getLocation(*row, column));
        }
        table.insert(copy_row);
    }

    return table;
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
