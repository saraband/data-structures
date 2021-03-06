#include "BinarySearch.hpp"

int main ()
{
  test::registerTest("Binary search an item that does not exist", []() {
    std::vector<int> array{ 1, 2, 4, 5, 8, 16, 188, 255, 397 };
    int steps = 0;

    test::expect(binarySearchFindIndex(array, 42, &steps) == -1);
    test::expect(steps == 4);
  });

  test::registerTest("Binary search", []() {
    std::vector<int> array{ 1, 2, 4, 5, 8, 16, 188, 255, 397 };
    int steps = 0;

    test::expect(binarySearchFindIndex(array, 2, &steps) == 1);
    test::expect(steps == 4);
  });

  test::registerTest("Binary search an item that is at the end", []() {
    std::vector<int> array{ 1, 2, 4, 5, 8, 16, 188, 255, 397 };
    int steps = 0;

    test::expect(binarySearchFindIndex(array, 397, &steps) == 8);
    test::expect(steps == 1);
  });

  test::registerTest("Binary search an item that is at the beginning", []() {
    std::vector<int> array{ 1, 2, 4, 5, 8, 16, 188, 255, 397 };
    int steps = 0;

    test::expect(binarySearchFindIndex(array, 1, &steps) == 0);
    test::expect(steps == 1);
  });

  return 0;
}