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

    std::ofstream out("times_insert.csv");
    out << "rows,columns,time ns row store, time ns col store" << std::endl;
    for (int32_t rows = 10000; rows <= 10000000; rows *= 10)
    {
        for (int columns = 1; columns <= 128; columns *= 2)
        {
            RowStoreTable *t = new RowStoreTable(rows, columns);
            ColumnStoreTable *tc = new ColumnStoreTable(rows, columns);
            
            auto rowData = getRandomValuesInRange(columns, 300);

            auto start = std::chrono::high_resolution_clock::now();
            for (int32_t i = 0; i < rows; ++i)
            {
                auto result = t->insert(rowData);
            }
            auto end = std::chrono::high_resolution_clock::now();
            auto row_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

            auto startc = std::chrono::high_resolution_clock::now();
            for (int32_t i = 0; i < rows; ++i)
            {
                auto result = tc->insert(rowData);
            }
            auto endc = std::chrono::high_resolution_clock::now();
            auto col_time = std::chrono::duration_cast<std::chrono::nanoseconds>(endc - startc).count();

            out << rows << "," << columns << "," << row_time << "," << col_time << std::endl;
            std::cout << rows << "," << columns << "," << row_time << "," << col_time << std::endl;

            delete rowData;

            delete t;
            delete tc;

        }
    }
}
