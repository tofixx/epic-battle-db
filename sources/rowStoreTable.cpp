#include <assert.h>
#include "rowStoreTable.h"

RowStoreTable::RowStoreTable(int32_t maxRows, int32_t columns)
    : Table(maxRows, columns)
{
}

int32_t &RowStoreTable::getLocation(const int32_t &row, const int32_t &column)
{
    assert (column < this->m_columns);
    assert (row < this->m_maxRows);
    return m_data[row * m_columns + column];
}

/// return value on heap!
Table *RowStoreTable::position_list_materialize(PositionList<int32_t> &positions, const int32_t columns, const int32_t *columnIds)
{
    RowStoreTable *table = new RowStoreTable(positions.count(), columns);

    // row wise
    std::vector<int32_t> copy_row;
    for (auto row = positions.m_positions.begin(); row != positions.m_positions.end(); ++row)
    {
        for (auto column = 0; column < columns; ++column)
        {
            copy_row.push_back(this->getLocation(*row, columnIds[column]));
        }
        table->insert(copy_row);
    }
    return table;
}
