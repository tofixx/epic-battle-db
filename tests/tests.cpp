#include <iostream>
#include <chrono>

#include "../sources/table.h"
#include "../sources/columnStoreTable.h"
#include "../sources/rowStoreTable.h"
#include "../sources/timer.h"

/* test methods */

// week 1
void test_create_column_table(){
	std::cout << "create column table... " << std::endl;
	uint32_t distinct20 [20] = { 14, 16, 15, 8, 14, 13, 12, 11, 1, 13, 17, 17, 12, 3, 16, 6, 17, 20, 3, 13  };

	ColumnStoreTable t = ColumnStoreTable(100, 20);
	t.generateData(20, distinct20);
}

void test_create_row_table(){
	std::cout << "create row table... " << std::endl;
	uint32_t distinct20 [20] = { 14, 16, 15, 8, 14, 13, 12, 11, 1, 13, 17, 17, 12, 3, 16, 6, 17, 20, 3, 13  };

	RowStoreTable t = RowStoreTable(100, 20);
	t.generateData(20, distinct20);
}

// week 2
void test_scan_row_table() {
    uint32_t distinct20[20] = {14, 16, 15, 8, 14, 13, 12, 11, 1, 13, 17, 17, 12, 3, 16, 6, 17, 20, 3, 13};

    RowStoreTable t = RowStoreTable(1000, 20);
    t.generateData(800, distinct20);

    int32_t search_key = 2;
    int32_t column = 3;
    auto list = t.table_eq_scan(column, search_key);

    for (auto it = list->m_positions.begin(); it != list->m_positions.end(); ++it) {
        if (t.getLocation(*it, column) != search_key) {
            std::cout << "ERROR: wrong result: pos  " << *it << " value " << t.getLocation(*it, column) << " expected " << search_key << std::endl;
        }
    }
    std::cout << "check row store scan DONE" << std::endl;
}

void test_scan_col_table() {
    uint32_t distinct20[20] = {14, 16, 15, 8, 14, 13, 12, 11, 1, 13, 17, 17, 12, 3, 16, 6, 17, 20, 3, 13};

    ColumnStoreTable t = ColumnStoreTable(1000, 20);
    t.generateData(800, distinct20);

    int32_t search_key = 2;
    int32_t column = 3;
    auto list = t.table_eq_scan(column, search_key);

    for (auto it = list->m_positions.begin(); it != list->m_positions.end(); ++it) {
        if (t.getLocation(*it, column) != search_key) {
            std::cout << "ERROR: wrong result: " << *it << " value " << t.getLocation(*it, column) << " expected " << search_key << std::endl;
        }
    }

    std::cout << "check col store scan DONE" << std::endl;
}

void test_materialize_col_table() {
    uint32_t distinct20[20] = {14, 16, 15, 8, 14, 13, 12, 11, 1, 13, 17, 17, 12, 3, 16, 6, 17, 20, 3, 13};

    RowStoreTable t = RowStoreTable(1000, 20);
    t.generateData(800, distinct20);

    int32_t search_key = 2;
    int32_t column = 3;
    auto list = t.table_eq_scan(column, search_key);

    int32_t columns[3] = {0, 1, 4};
    t.position_list_materialize(*list, 3, columns);
    std::cout << "col store materialize executed but not checked" << std::endl;
}

void test_materialize_row_table() {
    uint32_t distinct20[20] = {14, 16, 15, 8, 14, 13, 12, 11, 1, 13, 17, 17, 12, 3, 16, 6, 17, 20, 3, 13};

    ColumnStoreTable t = ColumnStoreTable(1000, 20);
    t.generateData(800, distinct20);

    int32_t search_key = 2;
    int32_t column = 3;
    auto list = t.table_eq_scan(column, search_key);

    int32_t columns[3] = {0, 1, 4};
    t.position_list_materialize(*list, 3, columns);
    std::cout << "row store materialize executed but not checked" << std::endl;
}

int main(int argc, char const * argv[])
{
	/* week 1 tests */
	// data creation sample
	test_create_column_table();
	test_create_row_table();

	// time measuring sample
	TimeTimer<> timer = TimeTimer<>(10);
	std::cout << std::endl << timer.measure(test_create_column_table) << " ns average time per call" << std::endl;
	std::cout << std::endl << timer.measure(test_create_row_table) << " ns average time per call" << std::endl;

    /* week 2 tests */
    test_scan_row_table();
    test_scan_col_table();
    test_materialize_col_table();
    test_materialize_row_table();

}
