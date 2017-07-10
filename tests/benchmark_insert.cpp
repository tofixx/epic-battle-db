#include <iostream>
#include <assert.h>
#include <fstream>
#include <cstring>
#include <chrono>
#include <cstdlib>

#include "../sources/table.h"
#include "../sources/columnStoreTable.h"
#include "../sources/rowStoreTable.h"

int main(int argc, char const *argv[])
{
    int32_t rows = 1000;
    int32_t rounds = 10;

    if (argc > 2) {
        rows = atoi(argv[1]);
        rounds = atoi(argv[2]);
    }

    std::ofstream out("times_insert.csv");
    out << "rows,columns,col store (by field),col store (inlined),row store (by field),row store (inlined),row store (row insert),row store (inlined row insert)" << std::endl;

    for (int columns = 1; columns <= 128; columns *= 2)
    {
        auto rowData = RowStoreTable::getRandomValuesInRange(columns, 300);

        RowStoreTable tr = RowStoreTable(rows, columns);
        ColumnStoreTable tc = ColumnStoreTable(rows, columns);


        // ColumnStoreTable normal insert
        auto startc = std::chrono::high_resolution_clock::now();
        for (int32_t round = 0; round != rounds; ++round)
        {
            for (int32_t i = 0; i < rows; ++i)
            {
                auto result = tc.insert(rowData);
            }
            tc.reset();
        }
        auto endc = std::chrono::high_resolution_clock::now();
        auto col_time = std::chrono::duration_cast<std::chrono::nanoseconds>(endc - startc).count() / rounds;

        // ColumnStoreTable inlined insert
        auto startc_i = std::chrono::high_resolution_clock::now();
        for (int32_t round = 0; round != rounds; ++round)
        {
            for (int32_t i = 0; i < rows; ++i)
            {
                for (auto columnIndex = 0; columnIndex != tc.m_columns; ++columnIndex)
                {
                    tc.m_data[columnIndex * tc.m_maxRows + tc.m_numRows] = rowData[columnIndex];
                }
                tc.m_numRows++;
            }
            tc.reset();
        }
        auto endc_i = std::chrono::high_resolution_clock::now();
        auto col_i_time = std::chrono::duration_cast<std::chrono::nanoseconds>(endc_i - startc_i).count() / rounds;

        // RowStoreTable normal insert
        auto start_r = std::chrono::high_resolution_clock::now();
        for (int32_t round = 0; round != rounds; ++round)
        {
            for (int32_t i = 0; i != rows; ++i)
            {
                auto result = tr.insert(rowData);
            }
            tr.reset();
        }
        auto end_r = std::chrono::high_resolution_clock::now();
        auto row_r_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end_r - start_r).count() / rounds;

        // RowStoreTable inlined insert
        auto start_i = std::chrono::high_resolution_clock::now();
        for (int32_t round = 0; round != rounds; ++round)
        {
            for (int32_t i = 0; i != rows; ++i)
            {
                for (auto columnIndex = 0; columnIndex != tr.m_columns; ++columnIndex)
                {
                    tr.m_data[tr.m_numRows * tr.m_columns + columnIndex] = rowData[columnIndex];
                }
                tr.m_numRows++;
            }
            tr.reset();
        }
        auto end_i = std::chrono::high_resolution_clock::now();
        auto row_i_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end_i - start_i).count() / rounds;

        // RowStoreTable row insert
        auto start = std::chrono::high_resolution_clock::now();
        for (int32_t round = 0; round != rounds; ++round)
        {
            for (int32_t i = 0; i != rows; ++i)
            {
                auto result = tr.insert_row(rowData);
            }
            tr.reset();
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto row_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() / rounds;

        // RowStoreTable inlined row insert
        auto start_ir = std::chrono::high_resolution_clock::now();
        for (int32_t round = 0; round != rounds; ++round)
        {
            for (int32_t i = 0; i != rows; ++i)
            {
                std::memcpy(&tr.getLocation(tr.m_numRows, 0), rowData, sizeof(int32_t) * tr.m_columns);
                tr.m_numRows++;
            }
            tr.reset();
        }
        auto end_ir = std::chrono::high_resolution_clock::now();
        auto row_ir_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end_ir - start_ir).count() / rounds;


        out << rows << "," << columns << "," << col_time << "," << col_i_time << "," << row_r_time << "," << row_i_time << "," << row_time << "," << row_ir_time << std::endl;
        std::cout << rows << "," << columns << "," << col_time << "," << col_i_time << "," << "," << row_r_time << "," << row_i_time << "," << row_time << "," << row_ir_time << std::endl;

        delete rowData;
    }
}
