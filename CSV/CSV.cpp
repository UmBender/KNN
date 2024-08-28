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
    std::vector<CellValue> elements;
    for (std::string &i : tokens) {
      double new_val = std::stod(i);
      elements.push_back(new_val);
    }
    atributes.push_back(elements);
  }

  get_column_type();
  set_max();
  set_min();
  normalize();
}

void CSV::get_column_type() {
  for (std::size_t i{0}; i < atributes.size(); ++i) {
    bool is_numeric = true;
    for (std::size_t j{0}; j < atributes[j].size(); ++j) {
      if (atributes[i][j].get_type() == QUALITATIVE) {
        is_numeric = false;
      }
    }
    column_type.push_back(is_numeric ? QUANTITATIVE : QUALITATIVE);
  }
}

void CSV::show() {
  for (std::size_t i{0}; i < sample_class.size(); ++i) {
    std::for_each(atributes[i].begin(), atributes[i].end(),
                  [](CellValue val) { std::cout << val.get_quali() << ","; });
    std::cout << sample_class[i] << std::endl;
  }
}

void CSV::normalize() {
  for (std::size_t i{0}; i < atributes.size(); ++i) {
    if (column_type[i] == QUANTITATIVE) {
      std::vector<CellValue> normalized;
      for (std::size_t j{0}; j < atributes[i].size(); ++j) {
        CellValue norm = CellValue((atributes[i][j] - value_min[j]) /
                                   (value_max[j] - value_min[j]));
        normalized.push_back(norm);
      }
      norm_atributes.push_back(normalized);
    } else {
      std::vector<CellValue> normalized;
      for (std::size_t j{0}; j < atributes[i].size(); ++j) {
        normalized.push_back(atributes[i][j]);
      }
      norm_atributes.push_back(normalized);
    }
  }
}

void CSV::set_max() {
  for (std::size_t i{0}; i < atributes[0].size(); ++i) {
    if (column_type[i] == QUANTITATIVE) {
      double max = DBL_MIN;
      for (std::size_t j{0}; j < atributes.size(); ++j) {
        if (atributes[j][i].get_quanti() > max) {
          max = atributes[j][i].get_quanti();
        }
      }
      value_max.push_back(max);
    } else {
      value_max.push_back(0);
    }
  }
}
void CSV::set_min() {
  for (std::size_t i{0}; i < atributes[0].size(); ++i) {
    if (column_type[i] == QUANTITATIVE) {
      double min = DBL_MAX;
      for (std::size_t j{0}; j < atributes.size(); ++j) {
        if (atributes[j][i].get_quanti() < min) {
          min = atributes[j][i].get_quanti();
        }
      }
      value_min.push_back(min);
    } else {
      value_min.push_back(1);
    }
  }
}
void CSV::show_normalized() {
  for (std::size_t i{0}; i < sample_class.size(); ++i) {
    std::for_each(norm_atributes[i].begin(), norm_atributes[i].end(),
                  [](CellValue val) { std::cout << val.get_quali() << ","; });
    std::cout << sample_class[i] << std::endl;
  }
}

std::pair<std::vector<std::vector<CellValue>>, std::vector<std::string>>
CSV::get_set() {
  return std::make_pair(norm_atributes, sample_class);
}

std::vector<CellValue> CSV::normalize_test(std::vector<CellValue> &arr) {
  if (arr.size() != value_max.size()) {
    return std::vector<CellValue>(value_max.size(), 0.0);
  }
  std::vector<CellValue> rarr;
  for (size_t i{0}; i < arr.size(); ++i) {
    if (column_type[i] == QUANTITATIVE && arr[i].get_type() == QUANTITATIVE) {
      if (arr[i].get_quanti() > value_max[i].get_quanti()) {
        rarr.push_back(1.0);
        continue;
      }
      if (arr[i].get_quanti() < value_min[i].get_quanti()) {
        rarr.push_back(0.0);
        continue;
      }

      double temp = (arr[i] - value_min[i]) / (value_max[i] - value_min[i]);
      rarr.push_back(CellValue(temp));
    } else {
      rarr.push_back(arr[i]);
    }
  }
  return rarr;
}

std::vector<std::pair<std::string, std::vector<CellValue>>> CSV::matrix_form() {
  std::vector<std::pair<std::string, std::vector<CellValue>>> rarr;
  for (std::size_t i{0}; i < sample_class.size(); ++i) {
    std::pair<std::string, std::vector<CellValue>> temp =
        std::make_pair(sample_class[i], atributes[i]);
    rarr.push_back(temp);
  }
  return rarr;
}
