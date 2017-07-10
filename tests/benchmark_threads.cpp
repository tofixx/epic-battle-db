#include <iostream>
#include <chrono>
#include <assert.h>
#include <stdlib.h>
#include <pthread.h>

#include "../sources/table.h"
#include "../sources/columnStoreTable.h"
#include "../sources/rowStoreTable.h"

typedef struct thread_data {
    int rows;
    int rounds;
    int columnsLimit;
} tdata_t;

void *test_materialize_row_table_threaded(void *threadarg)
{
    tdata_t *my_data = (tdata_t *) threadarg;

    for (int columns = 1; columns <= my_data->columnsLimit; columns *= 2) {
        // create
        RowStoreTable *t = new RowStoreTable(my_data->rows, columns);
        auto randomValues = RowStoreTable::getRandomUnsignedValuesInRange(columns, 20);
        t->generateData(my_data->rows, randomValues);

        // scan
        int32_t search_key = t->getLocation(0, 0);
        int32_t column = 0;
        auto start = std::chrono::high_resolution_clock::now();
        for (int32_t round = 0; round != my_data->rounds; ++round) {
            t->table_eq_scan(column, search_key);
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() / my_data->rounds;
        std::cout << my_data->rows << ",row," << columns << "," << time << std::endl;

        // cleanup
        delete t;
    }

    return 0;
}

void *test_materialize_col_table_threaded(void *threadarg)
{
    tdata_t *my_data = (tdata_t *) threadarg;

    for (int columns = 1; columns <= my_data->columnsLimit; columns *= 2) {
        // create
        ColumnStoreTable *t = new ColumnStoreTable(my_data->rows, columns);
        auto randomValues = ColumnStoreTable::getRandomUnsignedValuesInRange(columns, 20);
        t->generateData(my_data->rows, randomValues);

        // scan
        int32_t search_key = t->getLocation(0, 0);
        int32_t column = 0;
        auto start = std::chrono::high_resolution_clock::now();
        for (int32_t round = 0; round != my_data->rounds; ++round) {
            t->table_eq_scan(column, search_key);
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() / my_data->rounds;
        std::cout << my_data->rows << ",col, " << columns << "," << time << std::endl;

        // cleanup
        delete t;
    }

    return 0;
}


int main(int argc, char const *argv[])
{
    auto rows = 1000;
    auto rounds = 2;
    auto columnsLimit = 128;
    auto threads = 2;

    if (argc > 3) {
        rows = atoi(argv[1]);
        rounds = atoi(argv[2]);
        threads = atoi(argv[3]);
    }


    tdata_t *tdata = (tdata_t *) malloc(sizeof(tdata_t));
    tdata->rows = rows;
    tdata->rounds = rounds;
    tdata->columnsLimit = columnsLimit;

    pthread_t threadInstances[threads];

    std::cout << "RowStore with " << threads << " Threads:" << std::endl;
    for (int i = 0; i < threads; i++) {
        pthread_create(&threadInstances[i], NULL, test_materialize_row_table_threaded, tdata);
    }
    for (int i = 0; i < threads; i++) {
        pthread_join(threadInstances[i], NULL);
    }

    std::cout << "ColStore with " << threads << " Threads:" << std::endl;
    for (int i = 0; i < threads; i++) {
        pthread_create(&threadInstances[i], NULL, test_materialize_col_table_threaded, tdata);
    }
    for (int i = 0; i < threads; i++) {
        pthread_join(threadInstances[i], NULL);
    }

    std::cout << "Singlethreaded:" << std::endl;
    pthread_create(&threadInstances[0], NULL, test_materialize_row_table_threaded, tdata);
    pthread_join(threadInstances[0], NULL);
    pthread_create(&threadInstances[0], NULL, test_materialize_col_table_threaded, tdata);
    pthread_join(threadInstances[0], NULL);

    return 0;
}

