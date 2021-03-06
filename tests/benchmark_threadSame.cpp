#include <iostream>
#include <chrono>
#include <assert.h>
#include <stdlib.h>
#include <pthread.h>

#include "../sources/table.h"
#include "../sources/columnStoreTable.h"
#include "../sources/rowStoreTable.h"
#include <sys/time.h>

typedef struct thread_data {
    int threads;
    int rows;
    int rounds;
    int columns;
    RowStoreTable* tr;
    ColumnStoreTable* tc;
} tdata_t;

auto comparison_value = 10000001;
auto scan_column = 0;
float selectivity = 0.0001; // 0,01%

void *test_scan_count_row_table_threaded(void *threadarg)
{
    tdata_t *my_data = (tdata_t *) threadarg;

    // work so all threads are working while timing
    for (int32_t round = 0; round < my_data->rounds / 5; ++round) {
        auto result = my_data->tr->table_eq_scan(scan_column, comparison_value);
        delete result;
    }

    // scan
    auto start = std::chrono::high_resolution_clock::now();
    for (int32_t round = 0; round < my_data->rounds; ++round) {
        auto result = my_data->tr->table_eq_scan(scan_column, comparison_value);
        delete result;
    }
    auto end = std::chrono::high_resolution_clock::now();

    // work so all threads are working while timing
    for (int32_t round = 0; round < my_data->rounds / 5; ++round) {
        auto result = my_data->tr->table_eq_scan(scan_column, comparison_value);
        delete result;
    }

    // result
    auto time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() / my_data->rounds;
    std::cout << my_data->rows << "," << my_data->columns << "," << my_data->threads << ",rows," << time << std::endl;

    // cleanup
    return 0;
}

void *test_scan_count_col_table_threaded(void *threadarg)
{
    tdata_t *my_data = (tdata_t *) threadarg;

    // work so all threads are working while timing
    for (int32_t round = 0; round < my_data->rounds / 5; ++round) {
        auto result = my_data->tc->table_eq_scan(scan_column, comparison_value);
        delete result;
    }

    // scan
    auto start = std::chrono::high_resolution_clock::now();
    for (int32_t round = 0; round < my_data->rounds; ++round) {
        auto result = my_data->tc->table_eq_scan(scan_column, comparison_value);
        delete result;
    }
    auto end = std::chrono::high_resolution_clock::now();

    // work so all threads are working while timing
    for (int32_t round = 0; round < my_data->rounds / 5; ++round) {
        auto result = my_data->tc->table_eq_scan(scan_column, comparison_value);
        delete result;
    }

    // result
    auto time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() / my_data->rounds;
    std::cout << my_data->rows << "," << my_data->columns << "," << my_data->threads << ",cols," << time << std::endl;

    // cleanup
    return 0;
}


int main(int argc, char const *argv[])
{
    auto rows = 100000;
    auto rounds = 100;
    auto columns = 8;
    auto maxThreads = 4;

    if (argc > 3) {
        rows = atoi(argv[1]);
        rounds = atoi(argv[2]);
        maxThreads = atoi(argv[3]);
    }

    tdata_t *tdata = (tdata_t *) malloc(sizeof(tdata_t));
    tdata->rows = rows;
    tdata->rounds = rounds;
    tdata->columns = columns;

    auto randomValues = RowStoreTable::getRandomUnsignedValuesInRange(tdata->columns, 20);
    // create
    RowStoreTable *tr = new RowStoreTable(tdata->rows, tdata->columns);
    tr->generateData(tdata->rows, randomValues);
    tr->addDataWithSelectivity(selectivity, scan_column, comparison_value);
    tdata->tr = tr;

    ColumnStoreTable *tc = new ColumnStoreTable(tdata->rows, tdata->columns);
    tc->generateData(tdata->rows, randomValues);
    tc->addDataWithSelectivity(selectivity, scan_column, comparison_value);
    tdata->tc = tc;


    pthread_t threadInstances[maxThreads];

    std::cout << "rows,cols,threads,store,time" << std::endl;

    for (int threads = 1; threads <= maxThreads; threads++) {
        tdata->threads = threads;
        for (int i = 0; i < threads; i++) {
            pthread_create(&threadInstances[i], NULL, test_scan_count_row_table_threaded, tdata);
        }
        for (int i = 0; i < threads; i++) {
            pthread_join(threadInstances[i], NULL);
        }
    }

    for (int threads = 1; threads <= maxThreads; threads++) {
        tdata->threads = threads;
        for (int i = 0; i < threads; i++) {
            pthread_create(&threadInstances[i], NULL, test_scan_count_col_table_threaded, tdata);
        }
        for (int i = 0; i < threads; i++) {
            pthread_join(threadInstances[i], NULL);
        }
    }

    delete tr;
    delete tc;
    return 0;
}

