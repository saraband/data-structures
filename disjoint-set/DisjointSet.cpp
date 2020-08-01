#include "DisjointSet.hpp"

int main ()
{
  test::registerTest("Disjoint set initialization", []() {
    DisjointSet<int> set{ std::vector<int>{ 1, 2, 3, 4, 5 } };

    test::expect(set.m_parents.size() == 5);

    // Each element must be its own parent
    for (const auto& element : set.m_parents) {
      int key = element.first;
      int parent = element.second;

      test::expect(key == parent);
    }
  });

  test::registerTest("find & unite", []() {
    DisjointSet<int> set{ std::vector<int>{ 1, 2, 3, 4, 5 } };
    set.unite(1, 2);
    set.unite(2, 3);
    set.unite(4, 5);

    test::expect(set.find(1) == set.find(2));
    test::expect(set.find(2) == set.find(3));
    test::expect(set.find(4) == set.find(5));
    test::expect(set.find(1) != set.find(5));
  });

  test::registerTest("Union by rank should work", []() {
    DisjointSet<int> set{ std::vector<int>{ 1, 2, 3, 4, 5 } };
    set.unite(1, 2);

    // 1 appended arbitrarily to 2 but rank of group 2 should have increased
    test::expect(set.m_parents.find(1)->second == 2);
    test::expect(set.m_ranks.find(2)->second == 1);

    // 3 should have been appended to 2 since 2 has a higher rank
    set.unite(2, 3);
    test::expect(set.m_parents.find(3)->second == 2);
    test::expect(set.m_ranks.find(2)->second == 1);
  });

  test::registerTest("Path compression should work", []() {
    DisjointSet<int> set{ std::vector<int>{ 1, 2, 3, 4, 5 } };
    set.unite(3, 4);
    set.unite(2, 3);
    set.unite(1, 2);

    test::expect(set.m_parents.find(3)->second == 4);
    test::expect(set.m_parents.find(2)->second == 4);
    test::expect(set.m_parents.find(1)->second == 4);
  });

  return 0;
}
