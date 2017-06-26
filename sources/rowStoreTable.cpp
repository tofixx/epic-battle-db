#include <assert.h>
#include <stdio.h>
#include <cstring>

#include "rowStoreTable.h"

RowStoreTable::RowStoreTable(int32_t maxRows, int32_t columns)
    : Table(maxRows, columns)
{
}

inline int32_t &RowStoreTable::getLocation(const int32_t &row, const int32_t &column)
{
    //assert(column < this->m_columns);
    //assert(row < this->m_maxRows);
    return m_data[row * m_columns + column];
}

/// return value on heap!
Table *RowStoreTable::position_list_materialize(std::vector<int32_t> &positions, const int32_t columns, const int32_t *columnIds)
{
    RowStoreTable *table = new RowStoreTable(positions.size(), columns);

    // row wise
    int32_t *copy_row = new int32_t[columns];
    for (auto row = positions.begin(); row != positions.end(); ++row)
    {
        for (auto column = 0; column < columns; ++column)
        {
            copy_row[column] = this->getLocation(*row, columnIds[column]);
        }
        table->insert(copy_row);
    }
    delete[] copy_row;
    return table;
}

int32_t RowStoreTable::insert_row(int32_t *values)
{
    //assert(&values[m_columns] != nullptr);

    //if (m_numRows < m_maxRows)
    //{
    memcpy(&this->getLocation(m_numRows, 0), values, sizeof(int32_t) * m_columns);
    return m_numRows++;
    //}
    //else
    //{
    //    return -1;
    //}
}
