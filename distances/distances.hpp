#pragma once
#include "../CellValue/CellValue.hpp"
#include <cmath>
#include <cstdlib>
#include <vector>

namespace std {
double euclidean_dist(const std::vector<CellValue> &a,
                      const std::vector<CellValue> &b);

double manhattan_dist(const std::vector<CellValue> &a,
                      const std::vector<CellValue> &b);
double chebyshev_dist(const std::vector<CellValue> &a,
                      const std::vector<CellValue> &b);
} // namespace std
