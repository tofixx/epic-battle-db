#include <assert.h>
#include <cstring>
#include <iostream>
#include <algorithm>

#include "rowStoreTable.h"

RowStoreTable::RowStoreTable(const int32_t maxRows, const int32_t columns)
    : Table(maxRows, columns)
{
}

inline int32_t &RowStoreTable::getLocation(const int32_t &row, const int32_t &column)
{
    return m_data[row * m_columns + column];
}

/// return value on heap!
Table *RowStoreTable::position_list_materialize(const std::vector<int32_t> &positions, const int32_t columns, const int32_t *columnIds)
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

int32_t RowStoreTable::insert_row(const int32_t *values)
{
    std::memcpy(&this->getLocation(m_numRows, 0), values, sizeof(int32_t) * m_columns);
    return m_numRows++;
}

int32_t RowStoreTable::update_row(const int32_t rowIndex, const int32_t *values)
{
    memcpy(&this->getLocation(rowIndex, 0), values, sizeof(int32_t) * m_columns);
    return rowIndex;
}


// SAME IN ALL STORES BUT HERE TO INLINE getLocation()

/// <returns>return value on heap!</returns>
std::vector<int32_t> *RowStoreTable::table_eq_scan(const int32_t &columnId, const int32_t &value)
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

void RowStoreTable::generateData(const int32_t rows, const uint32_t *distinctValues)
{
    for (auto columnIndex = 0; columnIndex < m_columns; columnIndex++)
    {

        auto columnValues = Table::generateDistinctValues(distinctValues[columnIndex]);

        for (auto rowIndex = 0; rowIndex < rows; ++rowIndex)
        {
            auto valueIndex = rand() % distinctValues[columnIndex];
            this->getLocation(rowIndex, columnIndex) = columnValues[valueIndex];
        }
        delete[] columnValues;
    }
    m_numRows += rows;
}

void RowStoreTable::addDataWithSelectivity(const float selectivity, const int32_t column, const int32_t value) {

    // when there is a selectivity of 0 nothing should be added
    if (selectivity == 0 ) return;

    std::vector<int32_t> positions;
    for (int i = 0; i < m_numRows; i++)
    {
        positions.push_back(i);
    }

    // shuffle vector
    auto engine = std::default_random_engine{};
    std::shuffle(std::begin(positions), std::end(positions), engine);

    // fill column with value
    for (int i = 0; i < (selectivity * m_numRows); i++)
    {
        this->getLocation(positions[i], column) = value;
    }

    positions.clear();

}


inline int32_t RowStoreTable::insert(const int32_t *values)
{
    for (auto columnIndex = 0; columnIndex != m_columns; ++columnIndex)
    {
        this->getLocation(m_numRows, columnIndex) = values[columnIndex];
    }
    return m_numRows++;
}

int32_t RowStoreTable::update(const int32_t rowIndex, const int32_t *values)
{
    for (auto columnIndex = 0; columnIndex != m_columns; ++columnIndex)
    {
        this->getLocation(rowIndex, columnIndex) = values[columnIndex];
    }
    return rowIndex;
}

int32_t RowStoreTable::update(const int32_t rowIndex, const int32_t *columnsIndex, const int32_t columns, const int32_t *values)
{
    for (auto index = 0; index != columns; ++index)
    {
        auto columnIndex = columnsIndex[index];
        this->getLocation(rowIndex, columnIndex) = values[columnIndex];
    }
    return rowIndex;
}


inline void RowStoreTable::overrideColumn(const int32_t columnIndex, const int32_t *values)
{
    this->m_numRows = this->size();
    for (auto rowIndex = 0; rowIndex < m_numRows; rowIndex++)
    {
        this->getLocation(rowIndex, columnIndex) = int32_t(values[columnIndex]);
    }
}

void RowStoreTable::print_row(const int32_t row)
{
    std::cout << "col_" << row << "[";
    for (auto column = 0; column < m_columns; ++column)
    {
        std::cout << this->getLocation(row, column);
        if (column != (m_columns - 1))
            std::cout << ", ";
    }
    std::cout << "]" << std::endl;
}

void RowStoreTable::print(const int32_t firstRow, const int32_t lastRow)
{
    for (int32_t start = firstRow; start < lastRow; ++start)
    {
        print_row(start);
    }
}