#pragma once
#include <algorithm>
#include <cfloat>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class CSV {
private:
  std::vector<std::vector<double>> atributes;
  std::vector<std::string> sample_class;
  std::vector<double> value_max;
  std::vector<double> value_min;
  std::vector<std::vector<double>> norm_atributes;
  std::string file_name;
  void normalize();
  void set_max();
  void set_min();

public:
  CSV(std::string file_name);
  void show();
  void show_normalized();
  std::pair<std::vector<std::vector<double>>, std::vector<std::string>>
  get_set();
  std::vector<double> normalize_test(std::vector<double> &arr);
  std::vector<std::pair<std::string, std::vector<double>>> matrix_form();
};
