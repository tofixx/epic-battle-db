#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <assert.h>
#include <stdlib.h>
#include <chrono>
#include <typeinfo>
#include <vector>

#include "../sources/table.h"
#include "../sources/columnStoreTable.h"
#include "../sources/rowStoreTable.h"
#include "../sources/timer.h"

/**
* Returns numValues random Values from 1 - maxValues
*/
uint32_t *getRandomValuesInRange(int32_t numValues, int32_t maxValue)
{
    uint32_t *returnValues = new uint32_t[numValues];
    for (auto i = 0; i < numValues; ++i)
    {
        returnValues[i] = (uint32_t)(std::rand() % maxValue + 1);
    }
    return returnValues;
}

/* test methods */

void test_scan_row_table()
{
    uint32_t distinct20[20] = {14, 16, 15, 8, 14, 13, 12, 11, 1, 13, 17, 17, 12, 3, 16, 6, 17, 20, 3, 13};

    RowStoreTable t = RowStoreTable(1000, 20);
    t.generateData(800, distinct20);
    t.print(0, 9);
    t.print_row(799);

    int32_t search_key = t.getLocation(0, 3);
    int32_t column = 3;
    auto list = t.table_eq_scan(column, search_key);

    for (auto it = list->begin(); it != list->end(); ++it)
    {
        if (t.getLocation(*it, column) != search_key)
        {
            std::cout << "ERROR: wrong result: pos  " << *it << " value " << t.getLocation(*it, column) << " expected " << search_key << std::endl;
        }
    }
    delete list;
    std::cout << "check row store scan DONE" << std::endl;
}

void test_scan_col_table()
{
    uint32_t distinct20[20] = {14, 16, 15, 8, 14, 13, 12, 11, 1, 13, 17, 17, 12, 3, 16, 6, 17, 20, 3, 13};

    ColumnStoreTable t = ColumnStoreTable(1000, 20);
    t.generateData(800, distinct20);
    t.print(0, 9);
    t.print_row(799);

    int32_t search_key = t.getLocation(0, 3);
    int32_t column = 3;
    auto list = t.table_eq_scan(column, search_key);

    for (auto it = list->begin(); it != list->end(); ++it)
    {
        if (t.getLocation(*it, column) != search_key)
        {
            std::cout << "ERROR: wrong result: " << *it << " value " << t.getLocation(*it, column) << " expected " << search_key << std::endl;
        }
    }
    delete list;
    std::cout << "check col store scan DONE" << std::endl;
}

void execute_scan_row(RowStoreTable &table, const int32_t &column_id, const int32_t &comparison_value)
{
    table.table_eq_scan(column_id, comparison_value);
}

int main(int argc, char const *argv[])
{
    //test_scan_row_table();
    //test_scan_col_table();
    std::ofstream out("times_scan.csv");
    out << "rows,columns,ms rowstore, ms columnstore" << std::endl;
    for (int32_t rows = 10000; rows <= 10000000; rows *= 10)
    {
        for (int columns = 1; columns <= 128; columns *= 2)
        {

            auto row_table = new RowStoreTable(rows, columns);
            auto column_table = new ColumnStoreTable(rows, columns);

            auto randomValues = getRandomValuesInRange(columns, (rows / 500));

            row_table->generateData(rows, randomValues);
            column_table->generateData(rows, randomValues);
            auto column = columns/2;

            auto comparison_value = row_table->getLocation(0, column);
            auto start = std::chrono::high_resolution_clock::now();
            row_table->table_eq_scan(column, comparison_value);
            auto end = std::chrono::high_resolution_clock::now();

            auto scanTime_row = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

            comparison_value = column_table->getLocation(0, column);
            auto start_col = std::chrono::high_resolution_clock::now();
            column_table->table_eq_scan(column, comparison_value);
            auto end_col = std::chrono::high_resolution_clock::now();

            auto scanTime_column = std::chrono::duration_cast<std::chrono::nanoseconds>(end_col - start_col).count();

            out << rows << "," << columns << "," << scanTime_row << "," << scanTime_column << std::endl;

            delete[] randomValues;
            delete row_table;
            delete column_table;

            std::cout << "completed " << columns << " columns, and " << rows << " rows" << std::endl;
        }
    }
}
