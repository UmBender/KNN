#pragma once
#include <cmath>
#include <cstdlib>
#include <vector>

namespace std {
double euclidean_dist(const std::vector<double> &a,
                      const std::vector<double> &b);

double manhattan_dist(const std::vector<double> &a,
                      const std::vector<double> &b);
double chebyshev_dist(const std::vector<double> &a,
                      const std::vector<double> &b);
} // namespace std
