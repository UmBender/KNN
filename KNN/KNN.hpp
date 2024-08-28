#pragma once
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
  std::vector<std::vector<double>> atributes;
  std::vector<std::string> sample_class;
  std::set<std::string> type_classes;
  std::function<double(std::vector<double> &, std::vector<double> &)> metric;
  unsigned int k;

public:
  KNN(std::vector<std::vector<double>> &atributes,
      std::vector<std::string> &sample_class, unsigned int k);
  KNN(std::vector<std::vector<double>> &atributes,
      std::vector<std::string> &sample_class);
  KNN(std::vector<std::vector<double>> &atributes,
      std::vector<std::string> &sample_class, unsigned int k,
      std::function<double(std::vector<double> &, std::vector<double> &)>
          metric);

  std::vector<std::string> clasify(std::vector<double> a);
};
