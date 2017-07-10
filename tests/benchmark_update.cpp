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

    std::ofstream out("times_update.csv");
    out << "rows,columns,row store (row update),col store (by field)" << std::endl;

    auto shuffleOrder = getShuffeledRowIndices(rows);
    
    for (int columns = 1; columns <= 128; columns *= 2)
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
        auto row_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() / rounds;

        // ColumnStoreTable update
        auto startc = std::chrono::high_resolution_clock::now();
        for (int32_t round = 0; round != rounds; ++round)
        {
            for (int32_t i = 0; i < rows; ++i)
            {
                auto result = tc.update(shuffleOrder.at(i), rowData);
            }
        }
        auto endc = std::chrono::high_resolution_clock::now();
        auto col_time = std::chrono::duration_cast<std::chrono::nanoseconds>(endc - startc).count() / rounds;

        out << rows << "," << columns << "," << row_time << "," << col_time << "," << std::endl;
        std::cout << rows << "," << columns << "," << row_time << "," << col_time << std::endl;

        delete rowData;
    }
}
