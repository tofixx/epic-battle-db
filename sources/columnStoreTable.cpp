#include "columnStoreTable.h"

#include <stdlib.h>
#include <assert.h> 

ColumnStoreTable::ColumnStoreTable(int32_t maxRows, int32_t columns)
    : Table(maxRows, columns)
{
}

int32_t &ColumnStoreTable::getLocation(const int32_t &row, const int32_t &column)
{
    return m_data[column * m_maxRows + row];
}

/// return value on heap!
Table *ColumnStoreTable::position_list_materialize(PositionList<int32_t> &positions, const int32_t columns, const int32_t *column_ids)
{
    ColumnStoreTable table = ColumnStoreTable(positions.size(), columns);

    // row wise
    for (auto row = positions.m_positions.begin(); row != positions.m_positions.end(); ++row)
    {
        std::vector<int32_t> copy_row(columns);
        for (auto column = 0; column < columns; ++column)
        {
            copy_row.push_back(this->getLocation(*row, column_ids[column]));
        }
        // TODO:
        // table.insert(copy_row);
    }

    // column wise
    //    for (auto column = 0; column < columns; ++column) {
    //        std::vector<int32_t> copy_column(positions.size());
    //        for (auto row = positions.m_positions.begin(); row != positions.m_positions.end(); ++row) {
    //            copy_column.push_back(this->getLocation(*row, column_ids[column]));
    //        }
    //        // TODO:
    //        // table.override(column, copy_column);
    //    }

    return &table;
}

void ColumnStoreTable::generateData(int32_t rows, uint32_t *distinctValues)
{
    for (auto columnIndex = 0; columnIndex < m_columns; columnIndex++)
    {

        auto columnValues = Table::generateDistinctValues(distinctValues[columnIndex]);

        for (auto rowIndex = 0; rowIndex < rows; rowIndex++)
        {
            auto valueIndex = rand() % distinctValues[columnIndex];
            m_data[columnIndex * m_maxRows + rowIndex] = columnValues[valueIndex];
        }
        delete[] columnValues;
    }
    m_numRows += rows;
}

void ColumnStoreTable::insert(int32_t *values)
{
    // check if enough tuples are in input
    assert(values[m_columns]);

    if (m_numRows + 1 <= m_maxRows)
    {
        m_numRows += 1;

        for (auto columnIndex = 0; columnIndex < m_columns; columnIndex++)
        {
            m_data[columnIndex * m_maxRows + m_numRows] = values[columnIndex];
        }
    }
}