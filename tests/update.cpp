#include <iostream>
#include <chrono>
#include <assert.h>
#include <stdlib.h>
#include <fstream>
#include <string>

#include "../sources/table.h"
#include "../sources/columnStoreTable.h"
#include "../sources/rowStoreTable.h"
#include "../sources/timer.h"

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

uint32_t *getUnsignedRandomValuesInRange(int32_t numValues, int32_t maxValue)
{
    uint32_t *returnValues = new uint32_t[numValues];
    for (auto i = 0; i < numValues; ++i)
    {
        returnValues[i] = std::rand() % maxValue + 1;
    }
    return returnValues;
}



int main(int argc, char const *argv[])
{
    std::ofstream out("times_updates.csv");
    out << "rows,columns,time ns row store (row update), time ns col store (inlined update)" << std::endl;
    int32_t rows = 100000;
    int32_t rounds = 1000;

    for (int columns = 1; columns <= 128; columns *= 2)
    {
        auto rowData = getRandomValuesInRange(columns, 300);
        auto distinctValues = getUnsignedRandomValuesInRange(columns, 100);

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
                auto updateIndex = std::rand() % rows;
                auto result = tr.update(updateIndex, rowData);
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
                auto updateIndex = std::rand() % rows;
                auto result = tc.update(updateIndex, rowData);
            }
        }
        auto endc = std::chrono::high_resolution_clock::now();
        auto col_time = std::chrono::duration_cast<std::chrono::nanoseconds>(endc - startc).count() / rounds;

    
        out << rows << "," << columns << "," << row_time << "," << col_time << "," << std::endl;
        std::cout << rows << "," << columns << "," << row_time << "," << col_time  << std::endl;
 
        delete rowData;
    }
}
