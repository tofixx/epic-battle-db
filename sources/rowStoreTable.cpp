#include "rowStoreTable.h"


RowStoreTable::RowStoreTable(int32_t maxRows, int32_t columns)
    :Table(maxRows, columns)
{

}

int32_t & RowStoreTable::getLocation(const int32_t &row, const int32_t &column)
{
    return m_data[row * m_columns + column];
}

/// return value on heap!
Table* Table::position_list_materialize(const &PositionList positions, const int32_t columns, const int32_t *column_ids)
{
    Table table = new RowStoreTable(positions.size(), columns);

    for(auto column = columns_ids[0]; column < columns; ++column)
        {
        std::vector<int32_t> copy_column(positions.size());
        for (auto row = list->m_positions.begin(); row != list->m_positions.end(); ++row) 
        {
            copy_column.insert(this->getLocation(*row, column));
        }
        table.override(column, copy_column);
    }

    return table;
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
