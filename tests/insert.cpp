#include <iostream>
#include <assert.h>
#include <fstream>

#include "../sources/table.h"
#include "../sources/columnStoreTable.h"
#include "../sources/rowStoreTable.h"

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
        delete rowData;
    }
    delete t;
}

int main(int argc, char const *argv[])
{
    test_insert_row_table(10, 10, 10, true);
    test_insert_row_table(120000, 100, 100000, false);
    test_insert_column_table(120000, 100, 100000);
}
