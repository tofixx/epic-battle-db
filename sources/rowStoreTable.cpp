#include "rowStoreTable.h"

RowStoreTable::RowStoreTable(int32_t maxRows, int32_t columns)
    : Table(maxRows, columns)
{
}

int32_t &RowStoreTable::getLocation(const int32_t &row, const int32_t &column)
{
    return m_data[row * m_columns + column];
}

/// return value on heap!
Table *RowStoreTable::position_list_materialize(PositionList<int32_t> &positions, const int32_t columns, const int32_t *column_ids)
{
    RowStoreTable table = RowStoreTable(positions.size(), columns);

    // row wise
    for (auto row = positions.m_positions.begin(); row != positions.m_positions.end(); ++row)
    {
        int32_t* copy_row = new int32_t[columns];
        for (auto column = 0; column < columns; ++column)
        {
            // TODO: make sure it really copies
            copy_row[column] = this->getLocation(*row, column_ids[column]);
        }
        table.insert(copy_row);
        delete[] copy_row;
    }

    return &table;
}


