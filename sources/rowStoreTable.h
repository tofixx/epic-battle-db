#pragma once

#include "table.h"

class RowStoreTable : public Table
{

public:
  RowStoreTable(int32_t maxRows, int32_t maxColumns);
  virtual ~RowStoreTable() = default;
  int32_t insert_row(int32_t *values);
  int32_t update(int32_t rowIndex, int32_t *values) override;
  int32_t &getLocation(const int32_t &row, const int32_t &column) override;
  std::vector<int32_t> *table_eq_scan(const int32_t &columnId, const int32_t &value) override;
  Table *position_list_materialize(std::vector<int32_t> &positions, const int32_t columns, const int32_t *columnIds) override;
};
