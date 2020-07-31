#ifndef BINARY_SEARCH_HPP
#define BINARY_SEARCH_HPP

#include <vector>
#include <cmath>

#include "../Test.hpp"
#include "../Utils.hpp"

template<typename T>
int binarySearchFindIndex (const std::vector<T>& array, T value, int* steps = nullptr) {
  if (!array.size())
    return -1;

  int lowerBound = 0;
  int upperBound = array.size() - 1;

  do {
    // For testing complexity
    if (steps)
      *steps += 1;
    
    if (array[lowerBound] == value)
      return lowerBound;
    if (array[upperBound] == value)
      return upperBound;
    
    if (lowerBound + 1 == upperBound)
      return -1;

    int middleIndex = lowerBound + floor((static_cast<float>(upperBound) - lowerBound) / 2);
    
    if (value > array[middleIndex])
      lowerBound = middleIndex;
    else
      upperBound = middleIndex;
  } while (lowerBound != upperBound);

  return -1;
}

#endif