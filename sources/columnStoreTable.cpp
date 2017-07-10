#include <stdlib.h>
#include <assert.h>
#include "columnStoreTable.h"

ColumnStoreTable::ColumnStoreTable(int32_t maxRows, int32_t columns)
    : Table(maxRows, columns)
{
}

inline int32_t &ColumnStoreTable::getLocation(const int32_t &row, const int32_t &column)
{
    return m_data[column * m_maxRows + row];
}

/// <returns>return value on heap!</returns>
std::vector<int32_t> *ColumnStoreTable::table_eq_scan(const int32_t &columnId, const int32_t &value)
{
    auto *result = new std::vector<int32_t>();
    result->reserve(m_maxRows);

    for (auto row = 0; row < m_maxRows; ++row)
    {
        if (getLocation(row, columnId) == value)
        {
            result->push_back(row);
        }
    }
    return result;
}

/// return value on heap!
Table *ColumnStoreTable::position_list_materialize(std::vector<int32_t> &positions, const int32_t columns, const int32_t *columnIds)
{
    ColumnStoreTable *table = new ColumnStoreTable(positions.size(), columns);

    // column wise
    int32_t *copy_column = new int32_t[positions.size()];
    int32_t row_count;

    for (auto column = 0; column < columns; ++column)
    {
        row_count = 0;
        for (auto row = positions.begin(); row != positions.end(); ++row)
        {
            copy_column[row_count++] = this->getLocation(*row, columnIds[column]);
        }
        table->overrideColumn(column, copy_column);
    }

    delete[] copy_column;

    return table;
}
