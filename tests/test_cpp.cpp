
#include <iostream>
#include <string>
#include <cassert>

int cmp_int(const int *a, const int *b) 
{
    return (*a > *b) - (*a < *b);
}

#define REGISTER_ZTREE_TYPES(X) \
    X(int, int, Int, cmp_int)

#include "ztree.h"

#define TEST(name) printf("[TEST] %-40s", name);
#define PASS() std::cout << "\033[0;32mPASS\033[0m\n";

void test_cpp_wrappers() 
{
    TEST("C++ Wrapper (Insert, [], Find)");

    z_tree::map<int, int> m;
    
    // Insert.
    m.insert(10, 100);
    m.insert(5, 50);

    // Operator [].
    assert(m[10] == 100);
    m[20] = 200; // Auto-insert.
    assert(m.size() == 3);

    // Find (returns pointer or nullptr).
    assert(m.find(5) != nullptr);
    assert(*m.find(5) == 50);
    assert(m.find(99) == nullptr);

    PASS();
}

void test_iterators() 
{
    TEST("STL Iterators (Begin, End, ++, --)");

    z_tree::map<int, int> m;
    m[10] = 1;
    m[20] = 2;
    m[30] = 3;

    // Forward.
    auto it = m.begin();
    assert(it.key() == 10);
    ++it;
    assert(it.key() == 20);
    ++it;
    assert(it.key() == 30);
    ++it;
    assert(it == m.end());

    // Bidirectional.
    --it;
    assert(it.key() == 30);

    // Range-based for loop.
    int sum = 0;
    for (auto entry : m) {
        sum += entry.value();
    }
    assert(sum == 6);

    PASS();
}

void test_lower_bound() 
{
    TEST("Lower Bound & Erase");

    z_tree::map<int, int> m;
    m[10] = 10;
    m[20] = 20;
    m[30] = 30;

    // Lower bound.
    auto it = m.lower_bound(15);
    assert(it.key() == 20);

    it = m.lower_bound(10);
    assert(it.key() == 10);

    // Erase by key.
    m.erase(20);
    assert(m.find(20) == nullptr);
    assert(m.size() == 2);

    PASS();
}

int main() 
{
    std::cout << "=> Running tests (ztree.h, C++)\n";
    test_cpp_wrappers();
    test_iterators();
    test_lower_bound();
    std::cout << "=> All tests passed successfully.\n";
    return 0;
}

