#include "CSV/CSV.hpp"
#include "CellValue/CellValue.hpp"
#include "KNN/KNN.hpp"
#include "distances/distances.hpp"

int main(void) {
  /*
   * Set csv files for training and testing.
   */
  CSV csv_train("iris/iris_train.csv");
  CSV csv_test("iris/iris_test.csv");
  auto [attr, obj_class] = csv_train.get_set();
  std::vector<std::pair<std::string, std::vector<CellValue>>> data =
      csv_test.matrix_form();

  /*
   * Train the KNN model.
   */
  KNN knn(attr, obj_class, 1, std::euclidean_dist);

  /*
   * Setting the confusion matrix.
   */
  std::map<std::pair<std::string, std::string>, std::size_t> c;

  /*
   * Teste the KNN model.
   */
  for (auto [i, j] : data) {
    std::vector<std::string> classes = knn.clasify(csv_train.normalize_test(j));
    c[std::make_pair(i, classes[0])]++;
  }

  /*
   * Show the result of the test.
   */
  for (auto [info, k] : c) {
    std::cout << "------------------------------------------------------------"
              << std::endl;
    std::cout << "Real: " << info.first << ", Guessed: " << info.second
              << ", Number: " << k << std::endl;
  }

  std::cout << "------------------------------------------------------------"
            << std::endl;

  return 0;
}
