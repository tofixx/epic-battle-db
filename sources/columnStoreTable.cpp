#include "columnStoreTable.h"

#include <stdlib.h>

ColumnStoreTable::ColumnStoreTable(int32_t maxRows, int32_t columns)
    : Table(maxRows, columns)
{
}

int32_t &ColumnStoreTable::getLocation(const int32_t &row, const int32_t &column)
{
    return m_data[column * m_maxRows + row];
}

/// return value on heap!
Table *ColumnStoreTable::position_list_materialize(PositionList<int32_t> &positions, const int32_t columns, const int32_t *columnIds)
{
    ColumnStoreTable *table = new ColumnStoreTable(positions.count(), columns);

    // column wise
    std::vector<int32_t> *copy_column = new std::vector<int32_t>();
    int32_t row_count;

    for (auto column = 0; column < columns; ++column)
    {
        row_count = 0;
        for (auto row = positions.m_positions.begin(); row != positions.m_positions.end(); ++row)
        {
            copy_column->push_back(this->getLocation(*row, columnIds[column]));
        }
        table->overrideColumn(column, *copy_column);
    }
    delete copy_column;
    return table;
}
