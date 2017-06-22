#include <iostream>
#include <chrono>
#include <assert.h>
#include <stdlib.h>
#include <fstream>
#include <string>

#include "../sources/table.h"
#include "../sources/columnStoreTable.h"
#include "../sources/rowStoreTable.h"
#include "../sources/timer.h"

/**
* Returns numValues random Values from 1 - maxValues
*/
int32_t *getRandomValuesInRange(int32_t numValues, int32_t maxValue)
{
    int32_t *returnValues = new int32_t[numValues];
    for (auto i = 0; i < numValues; ++i)
    {
        returnValues[i] = std::rand() % maxValue + 1;
    }
    return returnValues;
}

// week 2
void test_insert_row_table(int maxRows, int columns, int insertRows, bool printRow)
{
    assert(insertRows <= maxRows);
    std::cout << "insert " << insertRows << " rows in row table with " << columns << " columns of size " << maxRows << std::endl;

    RowStoreTable *t = new RowStoreTable(maxRows, columns);
    for (int32_t i = 0; i < insertRows; ++i)
    {
        auto rowData = getRandomValuesInRange(columns, 300);
        auto result = t->insert(rowData);
        // std::cout << "inserted in line " << result << std::endl;
        if (printRow)
        {
            t->print_row(result);
        }
        delete rowData;
    }
    delete t;
}

void test_insert_column_table(int maxRows, int columns, int insertRows)
{
    assert(insertRows <= maxRows);
    std::cout << "insert " << insertRows << " rows in column table with " << columns << " columns of size " << maxRows << std::endl;

    ColumnStoreTable *t = new ColumnStoreTable(maxRows, columns);
    for (int32_t i = 0; i < insertRows; ++i)
    {
        auto rowData = getRandomValuesInRange(columns, 300);
        auto result = t->insert(rowData);
        // std::cout << "inserted in line " << result << std::endl;
        delete rowData;
    }
    delete t;
}

int main(int argc, char const *argv[])
{
    TimeTimer<> timer = TimeTimer<>(3);

    //timer.measure(test_insert_row_table, 10, 10, 10, true);
    //timer.measure(test_insert_row_table, 120000, 100, 100000, false);
    //timer.measure(test_insert_column_table, 120000, 100, 100000);

    std::ofstream out("times_insert.csv");
    out << "rows,columns,time ns row store, time ns col store" << std::endl;
    for (int32_t rows = 1; rows <= 10000000; rows *= 2)
    {
        for (int columns = 1; columns <= 128; columns *= 2)
        {
            auto time_insert_row_style = timer.measure(test_insert_row_table, rows, columns, rows, false);
            auto time_insert_col_style = timer.measure(test_insert_column_table, rows, columns, rows);

            out << rows << "," << columns << "," << time_insert_row_style << "," << time_insert_col_style << std::endl;
        }
    }
}
