#include "CSV.hpp"

CSV::CSV(std::string new_file_name) : file_name(new_file_name) {

  std::ifstream file(file_name);
  std::string row;

  while (std::getline(file, row)) {
    std::stringstream ss(row);
    std::string token;
    std::vector<std::string> tokens;
    while (std::getline(ss, token, ',')) {
      tokens.push_back(token);
    }
    sample_class.push_back(*(tokens.end() - 1));
    tokens.pop_back();
    std::vector<double> elements;
    for (std::string &i : tokens) {
      double new_val = std::stod(i);
      elements.push_back(new_val);
    }
    atributes.push_back(elements);
  }

  set_max();
  set_min();
  normalize();
}

void CSV::show() {
  for (std::size_t i{0}; i < sample_class.size(); ++i) {
    std::for_each(atributes[i].begin(), atributes[i].end(),
                  [](double val) { std::cout << val << ","; });
    std::cout << sample_class[i] << std::endl;
  }
}

void CSV::normalize() {
  for (std::size_t i{0}; i < atributes.size(); ++i) {
    std::vector<double> normalized;
    for (std::size_t j{0}; j < atributes[i].size(); ++j) {
      double norm =
          (atributes[i][j] - value_min[j]) / (value_max[j] - value_min[j]);
      normalized.push_back(norm);
    }
    norm_atributes.push_back(normalized);
  }
}

void CSV::set_max() {
  for (std::size_t i{0}; i < atributes[0].size(); ++i) {
    double max = DBL_MIN;
    for (std::size_t j{0}; j < atributes.size(); ++j) {
      if (atributes[j][i] > max) {
        max = atributes[j][i];
      }
    }
    value_max.push_back(max);
  }
}
void CSV::set_min() {
  for (std::size_t i{0}; i < atributes[0].size(); ++i) {
    double min = DBL_MAX;
    for (std::size_t j{0}; j < atributes.size(); ++j) {
      if (atributes[j][i] < min) {
        min = atributes[j][i];
      }
    }
    value_min.push_back(min);
  }
}
void CSV::show_normalized() {
  for (std::size_t i{0}; i < sample_class.size(); ++i) {
    std::for_each(norm_atributes[i].begin(), norm_atributes[i].end(),
                  [](double val) { std::cout << val << ","; });
    std::cout << sample_class[i] << std::endl;
  }
}

std::pair<std::vector<std::vector<double>>, std::vector<std::string>>
CSV::get_set() {
  return std::make_pair(norm_atributes, sample_class);
}

std::vector<double> CSV::normalize_test(std::vector<double> &arr) {
  if (arr.size() != value_max.size()) {
    return std::vector<double>(value_max.size(), 0.0);
  }
  std::vector<double> rarr;
  for (size_t i{0}; i < arr.size(); ++i) {
    if (arr[i] > value_max[i]) {
      rarr.push_back(1.0);
      continue;
    }
    if (arr[i] < value_min[i]) {
      rarr.push_back(0.0);
      continue;
    }

    double temp = (arr[i] - value_min[i]) / (value_max[i] - value_min[i]);
    rarr.push_back(temp);
  }
  return rarr;
}

std::vector<std::pair<std::string, std::vector<double>>> CSV::matrix_form() {
  std::vector<std::pair<std::string, std::vector<double>>> rarr;
  for (std::size_t i{0}; i < sample_class.size(); ++i) {
    std::pair<std::string, std::vector<double>> temp =
        std::make_pair(sample_class[i], atributes[i]);
    rarr.push_back(temp);
  }
  return rarr;
}
