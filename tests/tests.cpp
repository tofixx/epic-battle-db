#include <iostream>
#include <chrono>
#include <assert.h>
#include <stdlib.h>

#include "../sources/table.h"
#include "../sources/columnStoreTable.h"
#include "../sources/rowStoreTable.h"
#include "../sources/timer.h"

/* test methods */

/**
* Returns numValues random Values from 1 - maxValues
*/
int32_t *getRandomValuesInRange(int32_t numValues, int32_t maxValue)
{
    int32_t *returnValues = new int32_t[numValues];
    for (auto i = 0; i < numValues; i++)
    {
        returnValues[i] = std::rand() % maxValue + 1;
    }
    return returnValues;
}

// week 1
void test_create_column_table()
{
    std::cout << "create column table... " << std::endl;
    uint32_t distinct20[20] = {14, 16, 15, 8, 14, 13, 12, 11, 1, 13, 17, 17, 12, 3, 16, 6, 17, 20, 3, 13};

    ColumnStoreTable t = ColumnStoreTable(100, 20);
    t.generateData(20, distinct20);
}

void test_create_row_table()
{
    std::cout << "create row table... " << std::endl;
    uint32_t distinct20[20] = {14, 16, 15, 8, 14, 13, 12, 11, 1, 13, 17, 17, 12, 3, 16, 6, 17, 20, 3, 13};

    RowStoreTable t = RowStoreTable(100, 20);
    t.generateData(20, distinct20);
}

// week 2
void test_insert_row_table(int maxRows, int columns, int insertRows, bool printRow)
{
    assert(insertRows <= maxRows);
    std::cout << "insert " << insertRows << " in row table of size " << maxRows << std::endl;

    RowStoreTable t = RowStoreTable(maxRows, columns);
    for (int i = 0; i < insertRows; i++)
    {
        auto rowData = getRandomValuesInRange(columns, 300);
        auto result = t.insert(rowData);
        // std::cout << "inserted in line " << result << std::endl;
        if (printRow)
        {
            t.print_row(result);
        }
        delete rowData;
    }
}

void test_insert_column_table(int maxRows, int columns, int insertRows)
{
    assert(insertRows <= maxRows);
    std::cout << "insert " << insertRows << " in column table of size " << maxRows << std::endl;

    ColumnStoreTable t = ColumnStoreTable(maxRows, columns);
    for (int i = 0; i < insertRows; i++)
    {
        auto rowData = getRandomValuesInRange(columns, 300);
        auto result = t.insert(rowData);
        // std::cout << "inserted in line " << result << std::endl;
        delete rowData;
    }
}

void test_scan_row_table()
{
    uint32_t distinct20[20] = {14, 16, 15, 8, 14, 13, 12, 11, 1, 13, 17, 17, 12, 3, 16, 6, 17, 20, 3, 13};

    RowStoreTable t = RowStoreTable(1000, 20);
    t.generateData(800, distinct20);
    t.print(0, 10);
    t.print_row(799);
    t.print_row(800);

    int32_t search_key = 2;
    int32_t column = 3;
    auto list = t.table_eq_scan(column, search_key);
    list->print();

    for (auto it = list->m_positions.begin(); it != list->m_positions.end(); ++it)
    {
        if (t.getLocation(*it, column) != search_key)
        {
            std::cout << "ERROR: wrong result: pos  " << *it << " value " << t.getLocation(*it, column) << " expected " << search_key << std::endl;
        }
    }
    std::cout << "check row store scan DONE" << std::endl;
}

void test_scan_col_table()
{
    uint32_t distinct20[20] = {14, 16, 15, 8, 14, 13, 12, 11, 1, 13, 17, 17, 12, 3, 16, 6, 17, 20, 3, 13};

    ColumnStoreTable t = ColumnStoreTable(1000, 20);
    t.generateData(800, distinct20);
    t.print(0, 10);
    t.print_row(799);
    t.print_row(800);

    int32_t search_key = 2;
    int32_t column = 3;
    auto list = t.table_eq_scan(column, search_key);
    list->print();

    for (auto it = list->m_positions.begin(); it != list->m_positions.end(); ++it)
    {
        if (t.getLocation(*it, column) != search_key)
        {
            std::cout << "ERROR: wrong result: " << *it << " value " << t.getLocation(*it, column) << " expected " << search_key << std::endl;
        }
    }

    std::cout << "check col store scan DONE" << std::endl;
}

void test_materialize_row_table()
{
    uint32_t distinct20[20] = {14, 16, 15, 8, 14, 13, 12, 11, 1, 13, 17, 17, 12, 3, 16, 6, 17, 20, 3, 13};

    RowStoreTable *t = new RowStoreTable(1000, 20);
    t->generateData(800, distinct20);
    std::cout << "row table has " << t->count() << " elements..." << std::endl;

    int32_t search_key = 2;
    int32_t column = 3;
    auto list = t->table_eq_scan(column, search_key);

    int32_t columns[3] = {0, 1, 4};
    auto result = t->position_list_materialize(*list, 3, columns);
    delete list;
    delete t;
    std::cout << "result has " << result->count() << " elements..." << std::endl;
    result->print(0, 20);
    delete result;
    std::cout << "col store materialize executed" << std::endl;
}

void test_materialize_col_table()
{
    uint32_t distinct20[20] = {14, 16, 15, 8, 14, 13, 12, 11, 1, 13, 17, 17, 12, 3, 16, 6, 17, 20, 3, 13};

    ColumnStoreTable *t = new ColumnStoreTable(1000, 20);
    t->generateData(800, distinct20);
    std::cout << "column table has " << t->count() << " elements..." << std::endl;

    int32_t search_key = 2;
    int32_t column = 3;
    auto list = t->table_eq_scan(column, search_key);
    int32_t columns[3] = {0, 1, 4};
    auto result = t->position_list_materialize(*list, 3, columns);
    delete list;
    delete t;
    std::cout << "result has " << result->count() << " elements..." << std::endl;
    result->print(0, 20);
    delete result;
    std::cout << "row store materialize executed" << std::endl;
}

int main(int argc, char const *argv[])
{
    /* week 1 tests */
    // data creation sample
    test_create_column_table();
    test_create_row_table();

    // time measuring sample
    TimeTimer<> timer = TimeTimer<>(10);
    std::cout << std::endl
              << timer.measure(test_create_column_table) << " ns average time per call" << std::endl;
    std::cout << std::endl
              << timer.measure(test_create_row_table) << " ns average time per call" << std::endl;

    /* week 2 tests */

    std::cout << std::endl
              << timer.measure(test_insert_row_table, 10, 10, 10, true) << " ns average time per call" << std::endl;

    std::cout << std::endl
              << timer.measure(test_insert_row_table, 120000, 100, 100000, false) << " ns average time per call" << std::endl;
    std::cout << std::endl
              << timer.measure(test_insert_column_table, 120000, 100, 100000) << " ns average time per call" << std::endl;
    test_scan_row_table();
    test_scan_col_table();
    test_materialize_col_table();
    test_materialize_row_table();
}
