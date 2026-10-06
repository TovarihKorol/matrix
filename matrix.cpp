#include <iostream>
#include <new>
int** allocateMatrix(size_t n, size_t m) {
  int** matrix = new int*[n];
  for (size_t i = 0; i < n; ++i) {
    matrix[i] = nullptr;
  }
  try {
    for (size_t i = 0; i < n; ++i) {
      matrix[i] = new int[m];
    }
  } catch (...) {
    for (size_t i = 0; i < n; ++i) {
      delete[] matrix[i];
    }
    delete[] matrix;
    throw;
  }
  return matrix;
}
void freeMatrix(int** matrix, size_t n) {
  if (matrix == nullptr) return;
  for (size_t i = 0; i < n; ++i) {
    delete[] matrix[i];
  }
  delete[] matrix;
}
int** transpose(const int* const* matrix, size_t n, size_t m) {
  int** result = new int*[m];
  for (size_t i = 0; i < m; ++i) {
    result[i] = nullptr;
  }
  try {
    for (size_t i = 0; i < m; ++i) {
      result[i] = new int[n];
    }
  } catch (...) {
    freeMatrix(result, m);
    throw;
  }
  for (size_t i = 0; i < n; ++i) {
    for (size_t j = 0; j < m; ++j) {
      result[j][i] = matrix[i][j];
    }
  }
  return result;
}

void printMatrix(const int* const* matrix, size_t rows, size_t cols) {
  for (size_t i = 0; i < rows; ++i) {
    for (size_t j = 0; j < cols; ++j) {
      if (j > 0) std::cout << ' ';
      std::cout << matrix[i][j];
    }
    std::cout << '\n';
  }
}

int main() {
  long long nn = 0, mm = 0;
  std::cin >> nn >> mm;
  if (std::cin.fail() || nn <= 0 || mm <= 0) {
    std::cerr << "Неправильный ввод!\n";
    return 1;
  }
  const size_t n = static_cast<size_t>(nn);
  const size_t m = static_cast<size_t>(mm);

  int** matrix = nullptr;
  try {
    matrix = allocateMatrix(n, m);
  } catch (const std::bad_alloc&) {
    std::cerr << "Не удалось выделить память\n";
    return 2;
  }

  for (size_t i = 0; i < n; ++i) {
    for (size_t j = 0; j < m; ++j) {
      std::cin >> matrix[i][j];
      if (std::cin.fail()) {
        std::cerr << "Неправильный ввод!\n";
        freeMatrix(matrix, n);
        return 1;
      }
    }
  }

  int** transposed = nullptr;
  try {
    transposed = transpose(matrix, n, m);
  } catch (const std::bad_alloc&) {
    std::cerr << "Не удалось выделить память\n";
    freeMatrix(matrix, n);
    return 2;
  }

  printMatrix(transposed, m, n);

  freeMatrix(transposed, m);
  freeMatrix(matrix, n);
  return 0;
}
