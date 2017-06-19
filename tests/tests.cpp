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
std::vector<int32_t> getRandomValuesInRange(int32_t numValues, int32_t maxValue)
{
    std::vector<int32_t> returnValues;
    for (auto i = 0; i < numValues; ++i)
    {
        returnValues.push_back(std::rand() % maxValue + 1);
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
    std::cout << "insert " << insertRows << " rows in row table of size " << maxRows << std::endl;

    RowStoreTable t = RowStoreTable(maxRows, columns);
    for (int32_t i = 0; i < insertRows; ++i)
    {
        auto rowData = getRandomValuesInRange(columns, 300);
        auto result = t.insert(rowData);
        // std::cout << "inserted in line " << result << std::endl;
        if (printRow)
        {
            t.print_row(result);
        }
    }
}

void test_insert_column_table(int maxRows, int columns, int insertRows)
{
    assert(insertRows <= maxRows);
    std::cout << "insert " << insertRows << " rows in column table of size " << maxRows << std::endl;

    ColumnStoreTable t = ColumnStoreTable(maxRows, columns);
    for (int32_t i = 0; i < insertRows; ++i)
    {
        auto rowData = getRandomValuesInRange(columns, 300);
        auto result = t.insert(rowData);
        // std::cout << "inserted in line " << result << std::endl;
    }
}

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
    t.print(0, 9);
    t.print_row(799);

    int32_t search_key = t.getLocation(0,3);
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

    RowStoreTable *t = new RowStoreTable(800, 20);
    t->generateData(800, distinct20);
    std::cout << "row table has " << t->count() << " rows..." << std::endl;

    int32_t search_key = t->getLocation(1,3);
    int32_t column = 3;
    auto list = t->table_eq_scan(column, search_key);

    int32_t columns[3] = {0, 3, 4};
    auto result = t->position_list_materialize(*list, 3, columns);
    delete list;
    delete t;
    std::cout << "result has " << result->count() << " rows..." << std::endl;
    if (result->count())
    {
        result->print(0, result->count());
    }
    delete result;
    std::cout << "col store materialize executed" << std::endl;
}

void test_materialize_col_table()
{
    uint32_t distinct20[20] = {14, 16, 15, 8, 14, 13, 12, 11, 1, 13, 17, 17, 12, 3, 16, 6, 17, 20, 3, 13};

    ColumnStoreTable *t = new ColumnStoreTable(1000, 20);
    t->generateData(800, distinct20);
    std::cout << "column table has " << t->count() << " rows..." << std::endl;

    int32_t search_key = t->getLocation(0,3);
    int32_t column = 3;
    auto list = t->table_eq_scan(column, search_key);
    int32_t columns[3] = {0, 3, 4};
    auto result = t->position_list_materialize(*list, 3, columns);
    delete list;
    delete t;
    std::cout << "result has " << result->count() << " rows..." << std::endl;
    if (result->count())
    {
        result->print(0, result->count());
    }
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
    
    timer.measure(test_create_column_table);
    timer.measure(test_create_row_table);

    /* week 2 tests */    
    timer.measure(test_insert_row_table, 10, 10, 10, true);
    timer.measure(test_insert_row_table, 120000, 100, 100000, false);
    timer.measure(test_insert_column_table, 120000, 100, 100000);

    test_scan_row_table();
    test_scan_col_table();
    test_materialize_col_table();
    test_materialize_row_table();
}
