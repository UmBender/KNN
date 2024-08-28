#include "KNN.hpp"
KNN::KNN(std::vector<std::vector<double>> &new_atributes,
         std::vector<std::string> &new_sample_class, unsigned int new_k)
    : atributes(new_atributes), sample_class(new_sample_class),
      metric(std::euclidean_dist), k(new_k) {
  for (std::string i : type_classes) {
    type_classes.insert(i);
  }
}
KNN::KNN(std::vector<std::vector<double>> &new_atributes,
         std::vector<std::string> &new_sample_class)
    : atributes(new_atributes), sample_class(new_sample_class),
      metric(std::euclidean_dist), k(1) {
  for (std::string i : type_classes) {
    type_classes.insert(i);
  }
}
KNN::KNN(std::vector<std::vector<double>> &new_atributes,
         std::vector<std::string> &new_sample_class, unsigned int new_k,
         std::function<double(std::vector<double> &, std::vector<double> &)>
             new_metric)
    : atributes(new_atributes), sample_class(new_sample_class),
      metric(new_metric), k(new_k) {
  for (std::string i : type_classes) {
    type_classes.insert(i);
  }
}
std::vector<std::string> KNN::clasify(std::vector<double> a) {
  std::vector<std::pair<double, std::string>> objects;
  for (size_t i{0}; i < sample_class.size(); ++i) {
    double distance = metric(atributes[i], a);
    if (objects.size() < k) {
      objects.push_back(std::make_pair(distance, sample_class[i]));
    } else {
      std::pair<double, std::string> temp =
          std::make_pair(distance, sample_class[i]);
      if (temp.first < objects[objects.size() - 1].first) {
        objects[objects.size() - 1] = temp;
      }
    }
    std::sort(objects.begin(), objects.end());
  }

  std::map<std::string, std::size_t> counter;
  for (auto [j, i] : objects) {
    counter[i]++;
  }

  std::size_t max_value = 0;
  std::vector<std::string> max_class;
  for (auto [i, j] : counter) {
    if (j == max_value) {
      max_class.push_back(i);
    }
    if (j > max_value) {
      max_value = j;
      max_class.clear();
      max_class.push_back(i);
    }
  }
  return max_class;
}
