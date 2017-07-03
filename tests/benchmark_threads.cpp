#include <iostream>
#include <chrono>
#include <assert.h>
#include <stdlib.h>
#include <pthread.h>

#include "../sources/table.h"
#include "../sources/columnStoreTable.h"
#include "../sources/rowStoreTable.h"
#include "../sources/timer.h"

auto rows = 1000000;
auto columnsLimit = 128;
auto rounds = 100;
auto threads = 5;
int  thread_ids[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

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


void *test_materialize_row_table_threaded(void *thread)
{
    for (int columns = 1; columns <= columnsLimit; columns *= 2) {
        // create
        RowStoreTable *t = new RowStoreTable(rows, columns);
        auto randomValues = getRandomValuesInRange(columns, 20);
        t->generateData(rows, randomValues);

        // scan
        int32_t search_key = t->getLocation(0, 0);
        int32_t column = 0;
        auto start = std::chrono::high_resolution_clock::now();
        for (int32_t round = 0; round != rounds; ++round) {
            t->table_eq_scan(column, search_key);
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() / rounds;
        std::cout << ",row," << columns << "," << time << std::endl;

        // cleanup
        delete t;
    }

    return 0;
}

void *test_materialize_col_table_threaded(void *thread)
{
    for (int columns = 1; columns <= columnsLimit; columns *= 2) {
        // create
        ColumnStoreTable *t = new ColumnStoreTable(rows, columns);
        auto randomValues = getRandomValuesInRange(columns, 20);
        t->generateData(rows, randomValues);

        // scan
        int32_t search_key = t->getLocation(0, 0);
        int32_t column = 0;
        auto start = std::chrono::high_resolution_clock::now();
        for (int32_t round = 0; round != rounds; ++round) {
            t->table_eq_scan(column, search_key);
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() / rounds;
        std::cout << ",col, " << columns << "," << time << std::endl;

        // cleanup
        delete t;
    }

    return 0;
}


int main(int argc, char const *argv[])
{
    pthread_t threadInstances[threads];

    std::cout << "RowStore with " << threads << " Threads:" << std::endl;
    for (int i = 0; i < threads; i++) {
        pthread_create(&threadInstances[i], NULL, test_materialize_row_table_threaded, &thread_ids[i]);
    }
    for (int i = 0; i < threads; i++) {
        pthread_join(threadInstances[i], NULL);
    }

    std::cout << "ColStore with " << threads << " Threads:" << std::endl;
    for (int i = 0; i < threads; i++) {
        pthread_create(&threadInstances[i], NULL, test_materialize_col_table_threaded, &thread_ids[i]);
    }
    for (int i = 0; i < threads; i++) {
        pthread_join(threadInstances[i], NULL);
    }

    std::cout << "Singlethreaded:" << std::endl;
    pthread_create(&threadInstances[0], NULL, test_materialize_row_table_threaded, &thread_ids[0]);
    pthread_join(threadInstances[0], NULL);
    pthread_create(&threadInstances[0], NULL, test_materialize_col_table_threaded, &thread_ids[0]);
    pthread_join(threadInstances[0], NULL);

    return 0;
}

