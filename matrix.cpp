#include <iostream>
#include <new>
int main() {
  size_t n = 0, m = 0;
  std::cin >> n >> m;
  if(std::cin.fail() || n == 0 || m == 0) {
    std::cout << "Неправильный ввод!\n";
    return 1;
  }
  int** matrix = nullptr;
  try{
    matrix = new int*[n];
    for (size_t i = 0; i < n; ++i) {
      matrix[i] = nullptr;
    }
    for (size_t i = 0; i < n; ++i){
      matrix[i] = new int[m];
    }
    for (size_t j = 0; j < n; ++j){
      for (size_t k = 0; k < m; ++k){
        std::cin >> matrix[j][k];
        if (std::cin.fail()){
          std::cout << "Неправильный ввод!\n";
          for (size_t i = 0; i < n; ++i){
            delete [] matrix[i];
          }
          delete [] matrix; 
          return 1;
        }
      }
    }
    for (size_t k = 0; k < m; ++k){
      for (size_t j = 0;j < n; ++j){
        std::cout << matrix[j][k] << " ";
      }
      std::cout << "\n";
    }
  }catch (const std::bad_alloc &e){
    std::cout << "Неудалось выделить память";
    if (matrix != nullptr) {
      for (size_t i = 0; i < n; ++i) {
        delete [] matrix[i];
      }
      delete [] matrix;
    }
    return 2;
  }
  for (size_t i = 0; i < n; ++i) {
    delete [] matrix[i];
  }
  delete [] matrix;
  return 0;
}
