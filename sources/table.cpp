#include <iostream>
#include "table.h"

Table::Table(int maxRows, int maxColumns)
  : m_maxRows(maxRows)
  , m_maxColumns(maxColumns)
{
    m_data = new int[maxColumns * maxRows];
}

Table::~Table() {};

void Table::insert()
{
    // insert...
    std::cout << "insert..." << std::endl;
}
