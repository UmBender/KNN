#include "CellValue.hpp"
#include <stdexcept>

CellValue::CellValue(std::string data) : csv_data(data) {

  continuous = DBL_MAX;
  try {
    continuous = std::stold(csv_data);
    type = QUANTITATIVE;
  } catch (const std::invalid_argument &_) {
    type = QUALITATIVE;
  }
}

CellValue::CellValue(double numeric_data) : continuous(numeric_data) {
  type = QUANTITATIVE;
  csv_data = std::to_string(numeric_data);
}

CellType CellValue::get_type() const { return type; }

double CellValue::dist(const CellValue &b) const {
  if (type != b.get_type()) {
    return DBL_MAX;
  }
  switch (type) {
  case QUALITATIVE:
    return csv_data == b.get_quali() ? 0.0 : 1.0;
    break;
  case QUANTITATIVE:
  default:
    break;
  }

  return continuous - b.get_quanti();
}

double operator-(const CellValue &a, const CellValue &b) { return a.dist(b); }

inline std::string CellValue::get_quali() const { return csv_data; }
double CellValue::get_quanti() const { return continuous; }
