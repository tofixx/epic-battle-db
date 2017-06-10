#include "../sources/table.h"
#include "../sources/columnStoreTable.h"
#include "../sources/rowStoreTable.h"

void test_create_column_table(){
	ColumnStoreTable t = ColumnStoreTable(10, 20);
}

void test_create_row_table(){
	RowStoreTable t = RowStoreTable(10, 20);
}

int main(int argc, char const * argv[])
{
	test_create_column_table();
	test_create_row_table();
}
