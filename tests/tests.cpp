#include <iostream>
#include "../sources/table.h"
#include "../sources/columnStoreTable.h"
#include "../sources/rowStoreTable.h"

/* time tracking */

template<typename TimeT = std::chrono::high_resolution_clock>
struct measure
{
    template<typename F, typename ...Args>
    static typename TimeT::rep execution(F func, Args&&... args, int executionTimes)
    {
        auto start = TimeT::now();

		for(auto i = 0; i < executionTimes; ++i)
		{
        	func(std::forward<Args>(args)...);
		}

        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(TimeT::now() - start).count();
        return duration / executionTimes;
    }
};

/* test methods */

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

int main(int argc, char const * argv[])
{
	/* week 1 tests */
	// data creation sample
	test_create_column_table();
	test_create_row_table();
	// time measuring sample
	std::cout << "create column table: " << std::endl << measure<>::execution(test_create_column_table, 10) << " ns" << std::endl;
	std::cout << "create row table: " << std::endl << measure<>::execution(test_create_row_table, 10) << " ns" << std::endl;

}
