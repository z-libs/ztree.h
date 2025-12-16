
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

int cmp_int(const int *a, const int *b) 
{
    return (*a > *b) - (*a < *b);
}

#define REGISTER_ZTREE_TYPES(X) \
    X(int, int, Int, cmp_int)

#include "ztree.h"

#define TEST(name) printf("[TEST] %-35s", name);
#define PASS() printf(" \033[0;32mPASS\033[0m\n")

void test_basic_ops(void) 
{
    TEST("Init, Insert, Find, Size");

    ztree_Int t = ztree_init(Int);
    assert(ztree_find(&t, 10) == NULL);

    // Insert.
    ztree_insert(&t, 10, 100);
    ztree_insert(&t, 5, 50);
    ztree_insert(&t, 20, 200);

    assert(t.size == 3);

    // Find.
    ztree_node_Int *n = ztree_find(&t, 10);
    assert(n != NULL);
    assert(n->value == 100);

    n = ztree_find(&t, 5);
    assert(n->value == 50);

    n = ztree_find(&t, 999);
    assert(n == NULL);

    ztree_clear(&t);
    assert(t.size == 0);
    PASS();
}

void test_ordering_and_bounds(void) 
{
    TEST("Ordering, Min/Max, Lower Bound");

    ztree_Int t = ztree_init(Int);
    // Insert in mixed order: 20, 10, 30, 5, 15, 25, 35.
    int keys[] = {20, 10, 30, 5, 15, 25, 35};
    for(int i=0; i<7; ++i) ztree_insert(&t, keys[i], keys[i]*10);

    // Min/max.
    assert(ztree_min(&t)->key == 5);
    assert(ztree_max(&t)->key == 35);

    // Lower bound
    // Search for 12 -> LB should be 15.
    ztree_node_Int *lb = ztree_lower_bound(&t, 12);
    assert(lb != NULL && lb->key == 15);

    // Search for 20 -> LB should be 20 (exact match).
    lb = ztree_lower_bound(&t, 20);
    assert(lb != NULL && lb->key == 20);

    // Search for 40 -> LB should be NULL (end).
    lb = ztree_lower_bound(&t, 40);
    assert(lb == NULL);

    ztree_clear(&t);
    PASS();
}

void test_removal(void) 
{
    TEST("Removal (Leaf, Single, Double)");

    ztree_Int t = ztree_init(Int);
    int keys[] = {20, 10, 30, 5, 15, 40};
    for(int i=0; i<6; ++i) ztree_insert(&t, keys[i], 0);

    ztree_remove(&t, 5);
    assert(ztree_find(&t, 5) == NULL);
    assert(t.size == 5);

    ztree_remove(&t, 30);
    assert(ztree_find(&t, 30) == NULL);
    assert(ztree_find(&t, 40) != NULL);

    ztree_remove(&t, 20);
    assert(ztree_find(&t, 20) == NULL);
    
    assert(ztree_find(&t, 15) != NULL);
    assert(ztree_find(&t, 40) != NULL);

    ztree_clear(&t);
    PASS();
}

void test_iteration(void) 
{
    TEST("Iteration (Foreach In-Order)");

    ztree_Int t = ztree_init(Int);
    for(int i=5; i>=1; --i) ztree_insert(&t, i, i);

    int count = 0;
    int prev_key = 0;
    ztree_node_Int *it;

    ztree_foreach(&t, it) 
    {
        count++;
        assert(it->key > prev_key); // Ensure strict ascending order.
        prev_key = it->key;
    }
    (void)it;
    assert(count == 5);
    assert(prev_key == 5);

    ztree_clear(&t);
    PASS();
}

int main(void) 
{
    printf("=> Running tests (ztree.h, C)\n");
    test_basic_ops();
    test_ordering_and_bounds();
    test_removal();
    test_iteration();
    printf("=> All tests passed successfully.\n");
    return 0;
}

