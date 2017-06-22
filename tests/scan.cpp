#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <assert.h>
#include <stdlib.h>

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

void execute_scan(Table *table, const int32_t &column_id, const int32_t &comparison_value)
{
    table->table_eq_scan(column_id, comparison_value);
}

int main(int argc, char const *argv[])
{
    //test_scan_row_table();
    //test_scan_col_table();
    TimeTimer<> timer(3);
    std::ofstream out("times_scan.csv");
    out << "style,rows,columns,time ns" << std::endl;
    for (int32_t rows = 10000; rows <= 1000000; rows *= 10)
    {
        for (int columns = 1; columns <= 128; columns *= 2)
        {

            std::vector<Table> tables;
            tables.push_back(RowStoreTable(rows, columns));
            tables.push_back(ColumnStoreTable(rows, columns));

            auto randomValues = getRandomValuesInRange(columns, rows / 500);
            for (auto table = tables.begin(); table != tables.end(); ++table)
            {
                table->generateData(rows, randomValues);
                auto comparison_value = table->getLocation(0, 3);
                auto scanTime = timer.measure(execute_scan, *table, 3, comparison_value);
                if (table == tables.begin())
                {
                    out << "row-style," << rows << "," << columns << "," << scanTime << std::endl;
                }
                else
                {
                    out << "col-style," << rows << "," << columns << "," << scanTime << std::endl;
                }
            }
            delete[] randomValues;
        }
    }
}
