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
Table *ColumnStoreTable::position_list_materialize(PositionList<int32_t> &positions, const int32_t columns, const int32_t *column_ids)
{
    ColumnStoreTable table = ColumnStoreTable(positions.size(), columns);

    // row wise
    for (auto row = positions.m_positions.begin(); row != positions.m_positions.end(); ++row)
    {
        int32_t* copy_row = new int32_t[columns];
        for (auto column = 0; column < columns; ++column)
        {
            copy_row[column] = this->getLocation(*row, column_ids[column]);
        }
        table.insert(copy_row);
        delete[] copy_row;
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

