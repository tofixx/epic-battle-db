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


int32_t rows = 10000000;
int32_t rounds = 20;
int32_t max_columns = 128;

int main(int argc, char const *argv[])
{
    std::cout << "Starting scan benchmark... " << std::endl;

    std::ofstream out("times_scan.csv");
    out << "rows,columns,selectivity,rowstore,columnstore" << std::endl;

    auto comparison_value = 10000001;
    auto scan_column = 0;

    for (int columns = 1; columns <= max_columns; columns *= 2)
    {

        for (float selectivity = 0; selectivity <= 1; selectivity += 0.2)
        {

            std::cout << "Scanning table with " << columns << " columns and a selectivity of " << selectivity * 100 << "%" << std::endl;
            // create tables
            auto row_table = RowStoreTable(rows, columns);
            auto column_table = ColumnStoreTable(rows, columns);

            // Populate Table with random data
            auto randomValues = row_table.getRandomValuesInRange(columns, (rows / 500));
            row_table.generateData(rows, randomValues);
            column_table.generateData(rows, randomValues);
            delete[] randomValues;

            // Add known data to column 0 with defined selectivity
            row_table.addDataWithSelectivity(selectivity, scan_column, comparison_value);
            column_table.addDataWithSelectivity(selectivity, scan_column, comparison_value);

            // scan tables
            // -> row
            auto start = std::chrono::high_resolution_clock::now();
            for (int32_t round = 0; round != rounds; ++round) {
                auto result = row_table.table_eq_scan(scan_column, comparison_value);
                delete result;
            }
            auto end = std::chrono::high_resolution_clock::now();
            auto scanTime_row = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() / rounds;

            // -> col
            start = std::chrono::high_resolution_clock::now();
            for (int32_t round = 0; round != rounds; ++round) {
                auto result = column_table.table_eq_scan(scan_column, comparison_value);
                delete result;
            }
            end = std::chrono::high_resolution_clock::now();
            auto scanTime_col = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() / rounds;

            // output results
            out << rows << "," << columns << "," << selectivity << "," << scanTime_row << "," << scanTime_col << std::endl;
            std::cout << rows << "," << columns << "," << selectivity << "," << scanTime_row << "," << scanTime_col << std::endl;

        }
    }

}
