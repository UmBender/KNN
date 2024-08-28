#pragma once
#include "../CellValue/CellValue.hpp"
#include "../distances/distances.hpp"
#include <algorithm>
#include <cctype>
#include <functional>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

class KNN {
private:
  std::vector<std::vector<CellValue>> atributes;
  std::vector<std::string> sample_class;
  std::set<std::string> type_classes;
  std::function<double(std::vector<CellValue> &, std::vector<CellValue> &)>
      metric;
  unsigned int k;

public:
  KNN(std::vector<std::vector<CellValue>> &atributes,
      std::vector<std::string> &sample_class, unsigned int k);
  KNN(std::vector<std::vector<CellValue>> &atributes,
      std::vector<std::string> &sample_class);
  KNN(std::vector<std::vector<CellValue>> &atributes,
      std::vector<std::string> &sample_class, unsigned int k,
      std::function<double(std::vector<CellValue> &, std::vector<CellValue> &)>
          metric);

  std::vector<std::string> clasify(std::vector<CellValue> a);
};
