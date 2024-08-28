#include "distances.hpp"

double std::euclidean_dist(const std::vector<CellValue> &a,
                           const std::vector<CellValue> &b) {
  if (a.size() != b.size()) {
    return -1.0;
  }
  double accumulator = 0.0;
  for (std::size_t i{0}; i < a.size(); ++i) {
    accumulator += (a.at(i) - b.at(i)) * (a.at(i) - b.at(i));
  }
  return std::sqrt(accumulator);
}

double std::manhattan_dist(const std::vector<CellValue> &a,
                           const std::vector<CellValue> &b) {

  if (a.size() != b.size()) {
    return -1.0;
  }
  double accumulator = 0.0;
  for (std::size_t i{0}; i < a.size(); ++i) {
    accumulator += std::abs(a.at(i) - b.at(i));
  }
  return accumulator;
}

double std::chebyshev_dist(const std::vector<CellValue> &a,
                           const std::vector<CellValue> &b) {
  if (a.size() != b.size()) {
    return -1.0;
  }
  double max_dist = 0.0;
  for (std::size_t i{0}; i < a.size(); ++i) {
    double temp = std::abs(a.at(i) - b.at(i));
    if (temp > max_dist) {
      max_dist = temp;
    }
  }
  return max_dist;
}
