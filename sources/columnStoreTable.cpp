#include "columnStoreTable.h"

#include <stdlib.h>

ColumnStoreTable::ColumnStoreTable(int32_t maxRows, int32_t columns)
    :Table(maxRows, columns)
{

}


int32_t & ColumnStoreTable::getLocation(const int32_t &row, const int32_t &column)
{
    return m_data[column*m_maxRows+row];   
}

/// return value on heap!
Table* ColumnStoreTable::position_list_materialize(PositionList<int32_t> &positions, const int32_t columns, const int32_t *column_ids)
{
    ColumnStoreTable table = ColumnStoreTable(positions.size(), columns);

    // row wise
    for (auto row = positions.m_positions.begin(); row != positions.m_positions.end(); ++row)
    {
        std::vector<int32_t> copy_row(columns);
        for(auto column = 0; column < columns; ++column)
        {
            copy_row.push_back(this->getLocation(*row, column_ids[column]));
        }
        // TODO:
        // table.insert(copy_row);
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

void ColumnStoreTable::generateData(int32_t rows, uint32_t* distinctValues)
{
    for (auto columnIndex = 0; columnIndex < m_columns; columnIndex++) {

        auto columnValues = Table::generateDistinctValues(distinctValues[columnIndex]);

        for (auto rowIndex = 0; rowIndex < rows; rowIndex++) {
            auto valueIndex = rand() % distinctValues[columnIndex];
            m_data[columnIndex * m_maxRows + rowIndex] = columnValues[valueIndex];
            num_tuples++;
        }
        delete[] columnValues;
    }
}

void ColumnStoreTable::insert(int * values)
{
    // TODO test if the size calculation is correct
    size_t size;
    size = sizeof(values)/sizeof(values[0]);

    // calculates how many tuples are going to be inserted
    int num_insert_tuples = size/m_columns;

    // should calculate the number of existing tuples + number of new tuples
    // if that is bigger than the maxRows the transaction is stopped
    if(num_tuples + num_insert_tuples < m_maxRows ) {
        for (auto index = 0; index < size; index++) {
            int * column_insert = new int[num_insert_tuples];
            for (auto tuple_index = 0; tuple_index < num_insert_tuples; (tuple_index+=num_insert_tuples)) {
                column_insert[tuple_index] = values[index+tuple_index];
            }
            // Save the data and insert
            int tempStorageSize = (num_tuples*m_columns) - (index+1)*num_tuples;
            int * tempStore = new int[tempStorageSize];
            // makes a copy of the store except for the index first columns
            for(auto tempIndex = 0; tempIndex < tempStorageSize; tempIndex++) {
                tempStore[tempIndex] = m_data[num_tuples + (m_columns*index) + tempIndex];
            }
            // inserts one column
            for (auto insertIndex = 0; insertIndex < num_insert_tuples; insertIndex++) {
                m_data[num_tuples + (m_columns*index) + insertIndex] = column_insert[insertIndex];
            }
            // reinserts the remaining data
            for (auto backInsert = 0; backInsert < tempStorageSize; backInsert++) {
                m_data[num_tuples + (m_columns*index) + num_insert_tuples + backInsert] = tempStore[backInsert];
            }
            delete(column_insert);
            delete(tempStore);
        }
    }
}