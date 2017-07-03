#include <iostream>
#include <limits>
#include <assert.h>
#include <algorithm>
#include <random>
#include <stdexcept>

#include "table.h"

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
std::vector<int32_t> *Table::table_eq_scan(const int32_t &columnId, const int32_t &value)
{
    auto *result = new std::vector<int32_t>(); // todo m_maxRows Länge verwenden
    for (auto row = 0; row < m_maxRows; ++row)
    {
        if (getLocation(row, columnId) == value)
        {
            result->push_back(row);
            // todo immer überschreiben, zähler aber nicht immer hochzählen
        }
    }
    return result;
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

        for (auto rowIndex = 0; rowIndex < rows; ++rowIndex)
        {
            auto valueIndex = rand() % distinctValues[columnIndex];
            this->getLocation(rowIndex, columnIndex) = columnValues[valueIndex];
        }
        delete[] columnValues;
    }
    m_numRows += rows;
}

void Table::addDataWithSelectivity(float selectivity, int32_t value) {

    if (selectivity > 1 || selectivity < 0) throw std::invalid_argument( "selectivity has to be between 0 and 1" );

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
        this->getLocation(positions[i], 0) = value;
    }

    positions.clear();

}



int32_t Table::insert(int32_t *values)
{
    //check if there are enough values in input
    //assert(&values[m_columns] != nullptr);

    //if (m_numRows < m_maxRows)
    //{
    for (auto columnIndex = 0; columnIndex != m_columns; ++columnIndex)
    {
        this->getLocation(m_numRows, columnIndex) = values[columnIndex];
    }
    return m_numRows++;
    //}
    //else
    //{
    //    return -1;
    //}
}

void Table::overrideColumn(int32_t columnIndex, int32_t *values)
{
    assert(columnIndex >= 0 && columnIndex < m_columns);

    assert(&values[m_numRows] != nullptr);

    this->m_numRows = this->size();
    for (auto rowIndex = 0; rowIndex < m_numRows; rowIndex++)
    {
        this->getLocation(rowIndex, columnIndex) = int32_t(values[columnIndex]);
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

void Table::reset()
{
    this->m_numRows = 0;
}

void Table::print_row(int32_t row)
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

void Table::print(int32_t firstRow, int32_t lastRow)
{
    for (; firstRow < lastRow; ++firstRow)
    {
        print_row(firstRow);
    }
}
