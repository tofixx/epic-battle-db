#include <stdlib.h>
#include <assert.h>
#include "columnStoreTable.h"

ColumnStoreTable::ColumnStoreTable(int32_t maxRows, int32_t columns)
    : Table(maxRows, columns)
{
}

int32_t &ColumnStoreTable::getLocation(const int32_t &row, const int32_t &column)
{
    assert (column < this->m_columns);
    assert (row < this->m_maxRows);
    return m_data[column * m_maxRows + row];
}

/// return value on heap!
Table *ColumnStoreTable::position_list_materialize(PositionList<int32_t> &positions, const int32_t columns, const int32_t *columnIds)
{
    ColumnStoreTable *table = new ColumnStoreTable(positions.size(), columns);

    // column wise
    int32_t *copy_column = new int32_t[positions.size()];
    int32_t row_count;

    for (auto column = 0; column < columns; ++column)
    {
        row_count = 0;
        for (auto row = positions.m_positions.begin(); row != positions.m_positions.end(); ++row)
        {
            copy_column[row_count++] = this->getLocation(*row, columnIds[column]);
        }
        table->overrideColumn(column, copy_column);
    }

    delete[] copy_column;

    return table;
}
