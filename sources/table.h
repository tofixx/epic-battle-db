#pragma once

#include <stdint.h>

class Table
{
public:
    Table(int32_t maxRows, int32_t maxColumns);
    virtual ~Table();

    void virtual generateData(int32_t rows, int32_t* distinctValues) = 0;
    void insert();

protected:
    int32_t * m_data;
    int32_t m_maxRows;
    int32_t m_maxColumns;
private:

};
