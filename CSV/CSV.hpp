#pragma once
#include "../CellValue/CellValue.hpp"
#include <algorithm>
#include <cfloat>
#include <complex>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

class CSV {
private:
  std::vector<std::vector<CellValue>> atributes;
  std::vector<std::string> sample_class;
  std::vector<CellValue> value_max;
  std::vector<CellValue> value_min;
  std::vector<std::vector<CellValue>> norm_atributes;
  std::vector<CellType> column_type;
  std::string file_name;
  void get_column_type();
  void normalize();
  void set_max();
  void set_min();

public:
  CSV(std::string file_name);
  void show();
  void show_normalized();
  std::pair<std::vector<std::vector<CellValue>>, std::vector<std::string>>
  get_set();
  std::vector<CellValue> normalize_test(std::vector<CellValue> &arr);
  std::vector<std::pair<std::string, std::vector<CellValue>>> matrix_form();
};
