#include <iostream>
#include <chrono>
#include <assert.h>
#include <stdlib.h>
#include <pthread.h>

#include "../sources/table.h"
#include "../sources/columnStoreTable.h"
#include "../sources/rowStoreTable.h"
#include "../sources/timer.h"

void *test_materialize_row_table_threaded(void *thread)
{
    uint32_t distinct20[20] = {14, 16, 15, 8, 14, 13, 12, 11, 1, 13, 17, 17, 12, 3, 16, 6, 17, 20, 3, 13};

    RowStoreTable *t = new RowStoreTable(800, 20);
    t->generateData(800, distinct20);
    std::cout << "row table has " << t->count() << " rows..." << std::endl;

    int32_t search_key = t->getLocation(1,3);
    int32_t column = 3;
    auto list = t->table_eq_scan(column, search_key);

    int32_t columns[3] = {0, 3, 4};
    auto result = t->position_list_materialize(*list, 3, columns);
    delete list;
    delete t;
    std::cout << "result has " << result->count() << " rows..." << std::endl;
    if(result->count()) result->print(0, result->count());
    delete result;
    std::cout << "col store materialize executed" << std::endl;
    return 0;
}

void *test_materialize_col_table_threaded(void *thread)
{
    uint32_t distinct20[20] = {14, 16, 15, 8, 14, 13, 12, 11, 1, 13, 17, 17, 12, 3, 16, 6, 17, 20, 3, 13};

    ColumnStoreTable *t = new ColumnStoreTable(1000, 20);
    t->generateData(800, distinct20);
    std::cout << "column table has " << t->count() << " rows..." << std::endl;

    int32_t search_key = t->getLocation(0,3);
    int32_t column = 3;
    auto list = t->table_eq_scan(column, search_key);
    int32_t columns[3] = {0, 3, 4};
    auto result = t->position_list_materialize(*list, 3, columns);
    delete list;
    delete t;
    std::cout << "result has " << result->count() << " rows..." << std::endl;
    if(result->count()) result->print(0, result->count());
    delete result;
    std::cout << "row store materialize executed" << std::endl;
    return 0;
}


int main(int argc, char const *argv[])
{
    /* week  tests */
    // make the tests threaded
    std::cout << "Tests started" << std::endl;
    pthread_t threads[2];


    auto thread = pthread_create(&threads[0], NULL, test_materialize_row_table_threaded, (void *) 0);
    auto column = pthread_create(&threads[1], NULL, test_materialize_col_table_threaded, (void *) 1);

    if (thread || column){
        std::cout << "Error:unable to create thread" << std::endl;
        exit(-1);
    }

    pthread_exit(NULL);
}

