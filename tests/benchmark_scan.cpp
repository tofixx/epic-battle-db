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


int main(int argc, char const *argv[])
{
    int32_t rows = 1000;
    int32_t rounds = 10;
    int32_t max_columns = 128;

    if (argc > 2) {
        rows = atoi(argv[1]);
        rounds = atoi(argv[2]);
    }


    std::ofstream out("times_scan.csv");
    out << "rows,columns,selectivity,row store,col store,row store (count),col store (count)" << std::endl;
    std::cout << "rows,columns,selectivity,row store,col store,row store (count),col store (count)" << std::endl;

    auto comparison_value = 10000001;
    auto scan_column = 0;

    for (int columns = 1; columns <= max_columns; columns *= 2)
    {

        for (float selectivity = 0; selectivity <= 1; selectivity += 0.2)
        {

            // create tables
            auto row_table = RowStoreTable(rows, columns);
            auto column_table = ColumnStoreTable(rows, columns);

            // Populate Table with random data
            auto randomValues = RowStoreTable::getRandomUnsignedValuesInRange(columns, (rows / 500));
            row_table.generateData(rows, randomValues);
            column_table.generateData(rows, randomValues);
            delete[] randomValues;

            // Add known data to column 0 with defined selectivity
            row_table.addDataWithSelectivity(selectivity, scan_column, comparison_value);
            column_table.addDataWithSelectivity(selectivity, scan_column, comparison_value);

            // scan tables
            // -> row - list
            auto start = std::chrono::high_resolution_clock::now();
            for (int32_t round = 0; round != rounds; ++round) {
                auto result = row_table.table_eq_scan(scan_column, comparison_value);
                delete result;
            }
            auto end = std::chrono::high_resolution_clock::now();
            auto scanTime_row = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() / rounds;

            // -> row - count
            start = std::chrono::high_resolution_clock::now();
            for (int32_t round = 0; round != rounds; ++round) {
                auto result = row_table.table_eq_count(scan_column, comparison_value);
            }
            end = std::chrono::high_resolution_clock::now();
            auto countTime_row = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() / rounds;

            // -> col
            start = std::chrono::high_resolution_clock::now();
            for (int32_t round = 0; round != rounds; ++round) {
                auto result = column_table.table_eq_scan(scan_column, comparison_value);
                delete result;
            }
            end = std::chrono::high_resolution_clock::now();
            auto scanTime_col = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() / rounds;

            start = std::chrono::high_resolution_clock::now();
            for (int32_t round = 0; round != rounds; ++round) {
                auto result = column_table.table_eq_count(scan_column, comparison_value);
            }
            end = std::chrono::high_resolution_clock::now();
            auto countTime_col = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() / rounds;

            // output results
            out << rows << "," << columns << "," << selectivity << "," << scanTime_row << "," << scanTime_col << "," << countTime_row << "," << countTime_col << std::endl;
            std::cout << rows << "," << columns << "," << selectivity << "," << scanTime_row << "," << scanTime_col << "," << countTime_row << "," << countTime_col << std::endl;

        }

        out << std::endl;
        std::cout << std::endl;
    }

}
