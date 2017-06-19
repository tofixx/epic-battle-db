#include <iostream>
#include <limits>
#include <assert.h>

#include "table.h"
#include "positionList.h"

Table::Table(int maxRows, int columns)
    : m_maxRows(maxRows), m_columns(columns), m_numRows(0)
{
    m_data = new int32_t[m_columns * maxRows];
}

Table::~Table()
{
    delete[] m_data;
};

/// <returns>return value on heap!</returns>
PositionList<int32_t> *Table::table_eq_scan(const int32_t &columnId, const int32_t &value)
{
    auto *list = new PositionList<int32_t>();
    for (auto row = 0; row < m_maxRows; ++row)
    {
        if (getLocation(row, columnId) == value)
        {
            list->add(row);
        }
    }
    return list;
}

std::random_device Table::randomDevice;
std::mt19937 Table::randomGenerator = std::mt19937(Table::randomDevice());                                                                                                // seed the generator
std::uniform_int_distribution<> Table::randomDistribution = std::uniform_int_distribution<>(std::numeric_limits<int32_t>::lowest(), std::numeric_limits<int32_t>::max()); // define the range

int *Table::generateRandomDistinctValues(int32_t numberOfDistinctValues)
{
    int32_t *distinctValues = new int32_t[numberOfDistinctValues];

    for (int i = 0; i < numberOfDistinctValues; i++)
    {
        int32_t new_value = Table::randomDistribution(Table::randomGenerator);
        // TODO: should check if really distinct
        distinctValues[i] = new_value;
    }
    return distinctValues;
}

int *Table::generateDistinctValues(int32_t numberOfDistinctValues)
{
    int32_t *distinctValues = new int32_t[numberOfDistinctValues];

    for (int i = 0; i < numberOfDistinctValues; i++)
    {
        distinctValues[i] = i;
    }
    return distinctValues;
}

void Table::generateData(int32_t rows, uint32_t *distinctValues)
{
    for (auto columnIndex = 0; columnIndex < m_columns; columnIndex++)
    {

        auto columnValues = Table::generateDistinctValues(distinctValues[columnIndex]);

        for (auto rowIndex = 0; rowIndex < rows; rowIndex++)
        {
            auto valueIndex = rand() % distinctValues[columnIndex];
            this->getLocation(rowIndex, columnIndex) = columnValues[valueIndex];
        }
        delete[] columnValues;
    }
    m_numRows += rows;
}

int32_t Table::insert(const std::vector<int32_t> &row_values)
{
    //check if there are enough values in input
    assert(row_values.size() <= this->m_columns);
    int32_t columnIndex = 0;
    if (m_numRows + 1 <= m_maxRows)
    {
        for (auto col = row_values.begin(); col != row_values.end(); col++)
        {        
            columnIndex = std::distance(row_values.begin(), col);
            this->getLocation(m_numRows, columnIndex) = *col;
        }
        return ++m_numRows;
    }
    else
    {
        return -1;
    }
}

void Table::overrideColumn(const int32_t columnIndex, const std::vector<int32_t> &values)
{
    assert(columnIndex >= 0 && columnIndex < m_columns);

    assert(values.size() <= this->m_maxRows);

    for (auto rowIndex = 0; rowIndex < m_numRows; rowIndex++)
    {
        this->getLocation(rowIndex, columnIndex) = *new int32_t(values[columnIndex]);
    }
}

int32_t Table::count()
{
    return m_numRows;
}

int32_t Table::size()
{
    return m_maxRows;
}

void Table::print_row(int32_t row)
{
    std::cout << "col_" << row << "[";
    for (auto column = 0; column < m_columns; ++column)
    {
        std::cout << this->getLocation(row, column);
        if (column < (m_columns - 1))
            std::cout << ", ";
    }
    std::cout << "]" << std::endl;
}

void Table::print(int32_t firstRow, int32_t lastRow)
{
    for (; firstRow < lastRow; ++firstRow)
    {
        print_row(firstRow);
    }
}
