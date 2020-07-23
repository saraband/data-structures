#include <iostream>
#include "Vector.hpp"

int main ()
{
  using namespace std;

  Vector<int> vector;
  vector.push_back(17);
  vector.push_back(42);
  cout << vector << endl;

  vector.pop_back();
  cout << vector << endl;

  vector.push_front(88);
  cout << vector << endl;

  vector.pop_front();
  cout << vector << endl;
  
  return 0;
}