#pragma once
#include <cfloat>
#include <string>

enum CellType { QUANTITATIVE = 1, QUALITATIVE };
class CellValue {
private:
  std::string csv_data;
  CellType type;
  double continuous;

public:
  CellValue(std::string data);
  CellValue(double numeric_data);
  CellType get_type() const;
  std::string get_quali() const;
  double get_quanti() const;
  double dist(const CellValue &b) const;
};

double operator-(const CellValue &a, const CellValue &b);
