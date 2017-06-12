#include <iostream>
#include "../sources/table.h"
#include "../sources/columnStoreTable.h"
#include "../sources/rowStoreTable.h"

/* time tracking */

template<typename TimeT = std::chrono::nanoseconds, typename ClockT = std::chrono::high_resolution_clock>
class TimeTimer
{
public:
	TimeTimer(int executionTimes)
	: m_executionTimes(executionTimes)
	{

	}

 template<typename F, typename ...Args>
    typename TimeT::rep measure(F func, Args&&... args)
    {
		std::cout << "run " << func << " for " << m_executionTimes << " times..." << std::endl;
        
		auto start = ClockT::now();
		
		for(auto i = 0; i < m_executionTimes; ++i)
		{
        	func(std::forward<Args>(args)...);
		}

        auto duration = std::chrono::duration_cast<TimeT>(ClockT::now() - start).count();

        return duration / m_executionTimes;
    }

private:
	int m_executionTimes;
   
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
	TimeTimer<> timer = TimeTimer<>(10);
	std::cout << std::endl << timer.measure(test_create_column_table) << " ns average time per call" << std::endl;
	std::cout << std::endl << timer.measure(test_create_row_table) << " ns average time per call" << std::endl;

}
