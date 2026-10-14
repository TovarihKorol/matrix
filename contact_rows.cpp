#include <iostream>
#include <algorithm>
#include <new>
void free_arr(int ** arr, size_t n) {
  if (arr != nullptr) {
    for (size_t i = 0; i < n; ++i) {
      delete[] arr[i];
    }
    delete[] arr;
  }
}
int ** concat_rows(const int* const * lhs, size_t n1, size_t m1, const int * const * rhs, size_t n2, size_t m2) {
  size_t n = std::max(n1, n2);
  int ** res = new int*[n];
  for (size_t i = 0; i < n; ++i){
    res[i] = nullptr;
  }
  try{
    for (size_t i = 0; i < n; ++i){
      size_t len = 0;
      if (i < n1){
        len += m1;
      }
      if (i < n2) {
        len += m2;
      }
      res[i] = new int[len];
    }
  }
  catch(...) {
    free_arr(res, n);
    throw;
  }
  for (size_t i = 0; i < n; ++i){
    size_t pos = 0;
      if (i < n1) {
        for(size_t j = 0; j < m1;++j) {
          res[i][pos + j] = lhs[i][j];
        }
      pos += m1;
      }
    if (i < n2) {
      for(size_t j = 0; j < m2; ++j){
        res[i][pos + j] = rhs[i][j];
      }
    }
  }
  return res;
}
int main() {
  size_t n1 = 0, m1 = 0, n2 = 0, m2 = 0;
  std::cin >> n1 >> m1 >> n2 >> m2;
  if (std::cin.fail() || n1 == 0 || m1 == 0 || n2 == 0 || m2 == 0) {
    std::cerr << "Invalid_input\n";
    return 1;
  }
  size_t n = std::max(n1, n2);
  int ** arr1 = nullptr;
  int ** arr2 = nullptr;
  int ** res = nullptr;
  try {
    arr1 = new int*[n1];
    for(size_t i = 0; i < n1; ++ i){
      arr1[i] = nullptr;
    }
    for(size_t i = 0; i < n1; ++i) {
      arr1[i] = new int[m1];
    }
    arr2 = new int*[n2];
    for (size_t i = 0; i < n2; ++i){
      arr2[i] = nullptr;
    }
    for(size_t i = 0; i < n2; ++i){
      arr2[i] = new int[m2];
    }
    for (size_t i = 0; i < n1; ++i) {
      for (size_t j = 0; j < m1; ++j) {
        std::cin >> arr1[i][j];
        if(std::cin.fail()) {
          std::cerr << "Invalid_input\n";
          free_arr(arr1, n1);
          free_arr(arr2, n2);
          return 1;
        }
      }
    }
    for (size_t i = 0; i < n2; ++i) {
      for (size_t j = 0; j < m2; ++j) {
        std::cin >> arr2[i][j];
        if(std::cin.fail()) {
          std::cerr << "Invalid_input\n";
          free_arr(arr1, n1);
          free_arr(arr2, n2);
          return 1;
        }
      }
    }
  res = concat_rows(arr1, n1, m1, arr2, n2, m2);
  for(size_t i = 0; i < n; ++i){
    size_t len = 0;
    if(i < n1) {
      len += m1;
    }
    if(i < n2){
      len += m2;
    }
    for (size_t j = 0; j < len; ++j){
      std::cout << res[i][j] << " ";
    }
    std::cout << "\n";
  }
  }
  catch (const std::bad_alloc &) {
    std::cerr << "bad_alloc\n";
    free_arr(arr1, n1);
    free_arr(arr2, n2);
    return 2;
  }
   free_arr(arr1, n1);
   free_arr(arr2, n2);
   free_arr(res, n);
  return 0;
}

