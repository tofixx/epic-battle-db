#include <iostream>
#include <chrono>

#include "../sources/table.h"
#include "../sources/columnStoreTable.h"
#include "../sources/rowStoreTable.h"
#include "../sources/timer.h"

/* test methods */

void test_create_column_table(){
	//std::cout << "create column table... " << std::endl;
	uint32_t distinct20 [20] = { 14, 16, 15, 8, 14, 13, 12, 11, 1, 13, 17, 17, 12, 3, 16, 6, 17, 20, 3, 13  };

	ColumnStoreTable t = ColumnStoreTable(3000, 20);
	t.generateData(2000, distinct20);
}

void test_create_row_table(){
	//std::cout << "create row table... " << std::endl;
	uint32_t distinct20 [20] = { 14, 16, 15, 8, 14, 13, 12, 11, 1, 13, 17, 17, 12, 3, 16, 6, 17, 20, 3, 13  };

	RowStoreTable t = RowStoreTable(3000, 20);
	t.generateData(2000, distinct20);
}

int main(int argc, char const * argv[])
{
	/* week 1 tests */
	// data creation sample
	test_create_column_table();
	test_create_row_table();
	// time measuring sample
	TimeTimer<> timer = TimeTimer<>(1000);
	std::cout << std::endl << "test_create_column_table()" << std::endl << timer.measure(test_create_column_table) << " ns average time per call" << std::endl;
	std::cout << std::endl << "test_create_row_table()" << std::endl << timer.measure(test_create_row_table) << " ns average time per call" << std::endl;

}
