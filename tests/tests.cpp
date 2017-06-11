#include "../sources/table.h"
#include "../sources/columnStoreTable.h"
#include "../sources/rowStoreTable.h"

void test_create_column_table(){
	uint32_t distinct20 [20] = { 14, 16, 15, 8, 14, 13, 12, 11, 1, 13, 17, 17, 12, 3, 16, 6, 17, 20, 3, 13  };

	ColumnStoreTable t = ColumnStoreTable(100, 20);
	t.generateData(20, distinct20);
}

void test_create_row_table(){
	uint32_t distinct20 [20] = { 14, 16, 15, 8, 14, 13, 12, 11, 1, 13, 17, 17, 12, 3, 16, 6, 17, 20, 3, 13  };

	RowStoreTable t = RowStoreTable(100, 20);
	t.generateData(20, distinct20);
}

int main(int argc, char const * argv[])
{
	test_create_column_table();
	test_create_row_table();
}
