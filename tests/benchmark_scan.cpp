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

int main(int argc, char const *argv[])
{
    std::ofstream out("times_scan.csv");
    out << "rows,columns,ns rowstore, ns columnstore" << std::endl;
    int32_t rows = 10000000;
    int32_t rounds = 20;

    for (int columns = 1; columns <= 128; columns *= 2)
    {
        // create tables
        auto row_table = RowStoreTable(rows, columns);
        auto column_table = ColumnStoreTable(rows, columns);


        // fill tables with same data
        // TODO: replace with data with known selectivity
        auto randomValues = getRandomValuesInRange(columns, (rows / 500));
        row_table.generateData(rows, randomValues);
        column_table.generateData(rows, randomValues);
        delete[] randomValues;
        auto column = columns/2;


        // scan tables
        // -> row
        auto comparison_value = row_table.getLocation(0, column); // TODO: replace with know value
        auto start = std::chrono::high_resolution_clock::now();
        for (int32_t round = 0; round != rounds; ++round) {
            row_table.table_eq_scan(column, comparison_value);
            // (optional) clear caches
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto scanTime_row = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() / rounds;

        // -> col
        comparison_value = column_table.getLocation(0, column); // TODO: replace with know value
        start = std::chrono::high_resolution_clock::now();
        for (int32_t round = 0; round != rounds; ++round) {
            column_table.table_eq_scan(column, comparison_value);
            // (optional) clear caches
        }
        end = std::chrono::high_resolution_clock::now();
        auto scanTime_col = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() / rounds;


        // output results
        out << rows << "," << columns << "," << scanTime_row << "," << scanTime_col << std::endl;
        std::cout << rows << "," << columns << "," << scanTime_row << "," << scanTime_col << std::endl;
    }

}
