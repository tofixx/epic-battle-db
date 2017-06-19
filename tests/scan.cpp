#include <iostream>
#include <chrono>
#include <assert.h>
#include <stdlib.h>

#include "../sources/table.h"
#include "../sources/columnStoreTable.h"
#include "../sources/rowStoreTable.h"
#include "../sources/timer.h"

/* test methods */

void test_scan_row_table()
{
    uint32_t distinct20[20] = {14, 16, 15, 8, 14, 13, 12, 11, 1, 13, 17, 17, 12, 3, 16, 6, 17, 20, 3, 13};

    RowStoreTable t = RowStoreTable(1000, 20);
    t.generateData(800, distinct20);
    t.print(0, 9);
    t.print_row(799);

    int32_t search_key = t.getLocation(0,3);
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

    int32_t search_key = t.getLocation(0,3);
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

int main(int argc, char const *argv[])
{
    test_scan_row_table();
    test_scan_col_table();
}
