#include <iostream>
#include <chrono>
#include <assert.h>
#include <algorithm> // std::random_shuffle
#include <stdlib.h>
#include <fstream>
#include <string>
#include <vector>

#include "../sources/table.h"
#include "../sources/columnStoreTable.h"
#include "../sources/rowStoreTable.h"

std::vector<uint32_t> getShuffeledRowIndices(int32_t maxRows)
{
    std::vector<uint32_t> indices;
    for (int i = 0; i < maxRows; ++i)
    {
        indices.push_back(i);
    }

    std::random_shuffle(indices.begin(), indices.end());

    return indices;
}

int main(int argc, char const *argv[])
{
    int32_t rows = 1000;
    int32_t rounds = 10;

    if (argc > 2) {
        rows = atoi(argv[1]);
        rounds = atoi(argv[2]);
    }

    std::ofstream out("times_updateRandom.csv");
    out << "rows,columns,update,row copy,row store,col store" << std::endl;

    auto shuffleOrder = getShuffeledRowIndices(rows);
    int randomColumnOrder[128] = {
            44, 116, 76, 72, 1, 87, 118, 3, 74, 106, 54, 127, 95, 11, 97, 53, 62, 63, 10, 36, 115, 7, 6, 119, 69, 64,
            30, 43, 126, 75, 33, 40, 88, 66, 100, 14, 38, 18, 85, 56, 4, 32, 20, 80, 57, 92, 121, 91, 9, 55, 47, 5, 61,
            67, 13, 24, 96, 23, 41, 42, 71, 29, 51, 117, 34, 49, 28, 103, 65, 99, 35, 21, 81, 79, 2, 128, 8, 108, 52,
            16, 109, 77, 125, 107, 111, 59, 31, 50, 84, 110, 89, 22, 60, 48, 98, 114, 113, 27, 122, 15, 70, 102, 19, 94,
            124, 26, 25, 123, 37, 86, 105, 73, 101, 68, 90, 112, 46, 12, 83, 78, 104, 120, 93, 17, 45, 82, 39, 58
    };

    int columns = 128;
    for (int update = 1; update <= 16; update *= 2)
    {
        auto rowData = RowStoreTable::getRandomValuesInRange(columns, 300);
        auto distinctValues = RowStoreTable::getRandomUnsignedValuesInRange(columns, 100);

        RowStoreTable tr = RowStoreTable(rows, columns);
        tr.generateData(rows, distinctValues);

        ColumnStoreTable tc = ColumnStoreTable(rows, columns);
        tc.generateData(rows, distinctValues);

        // RowStoreTable update
        auto start = std::chrono::high_resolution_clock::now();
        for (int32_t round = 0; round != rounds; ++round)
        {
            for (int32_t i = 0; i != rows; ++i)
            {
                auto result = tr.update_row(shuffleOrder.at(i), rowData);
            }
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto copy_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() / rounds;

        // RowStoreTable update
        auto startr = std::chrono::high_resolution_clock::now();
        for (int32_t round = 0; round != rounds; ++round)
        {
            for (int32_t i = 0; i != rows; ++i)
            {
                auto result = tr.update(shuffleOrder.at(i), randomColumnOrder + ((i * update) % 64), update, rowData);
            }
        }
        auto endr = std::chrono::high_resolution_clock::now();
        auto row_time = std::chrono::duration_cast<std::chrono::nanoseconds>(endr - startr).count() / rounds;

        // ColumnStoreTable update
        auto startc = std::chrono::high_resolution_clock::now();
        for (int32_t round = 0; round != rounds; ++round)
        {
            for (int32_t i = 0; i < rows; ++i)
            {
                auto result = tc.update(shuffleOrder.at(i), randomColumnOrder + ((i * update) % 64), update, rowData);
            }
        }
        auto endc = std::chrono::high_resolution_clock::now();
        auto col_time = std::chrono::duration_cast<std::chrono::nanoseconds>(endc - startc).count() / rounds;

        out << rows << "," << columns << "," << update << "," << copy_time << "," << row_time << "," << col_time << "," << std::endl;
        std::cout << rows << "," << columns << "," << update << "," << copy_time << "," << row_time << "," << col_time << std::endl;

        delete rowData;
    }

}
