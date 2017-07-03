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


/**
* Returns a predefined selectivity. Selectivity is 0 to 100, representing a procentual value of distinct values. 0 means ther will be just one value
**/
uint32_t *getValuesWithSelectivity(int32_t numValues, int32_t maxValue, int32_t selectivity)
{
    uint32_t *returnValues = new uint32_t[numValues];
    for (auto i = 0; i < numValues; ++i)
    {
        if (selectivity == 0) {
            returnValues[i] = 1;
        } else {
            returnValues[i] = selectivity * maxValue / 100;
        }
    }
    return returnValues;
}

int main(int argc, char const *argv[])
{
    std::cout << "Starting scan benchmark... " << std::endl;

    std::ofstream out("times_scan.csv");
    out << "rows,columns,selectivity,ns rowstore, ns columnstore" << std::endl;
    int32_t rows = 10000000;
    int32_t rounds = 20;

    for (int columns = 1; columns <= 128; columns *= 2)
    {
        for (float selectivity = 0; selectivity <= 1; selectivity += 0.2) {

            std::cout << "Creating table with " << columns << " columns and a selectivity of " << selectivity * 100 << "%" << std::endl;

            // create tables
            auto row_table = RowStoreTable(rows, columns);
            auto column_table = ColumnStoreTable(rows, columns);

            auto randomValues = getRandomValuesInRange(columns, (rows / 500));

            row_table.generateData(rows, randomValues);
            column_table.generateData(rows, randomValues);

            auto comparison_value = 10000001;

            row_table.addDataWithSelectivity(selectivity,comparison_value);
            column_table.addDataWithSelectivity(selectivity,comparison_value);

            delete[] randomValues;

            auto column = columns/2;

            // scan tables
            // -> row
            // auto comparison_value = row_table.getLocation(0, column); // TODO: replace with know value
            // std::cout << "comparsion value is " << comparison_value << std::endl;
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
            out << rows << "," << columns << "," << selectivity << "," << scanTime_row << "," << scanTime_col << std::endl;
            std::cout << rows << "," << columns << "," << selectivity << "," << scanTime_row << "," << scanTime_col << std::endl;
        }
    }

}
