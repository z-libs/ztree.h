
#include <stdio.h>

int int_cmp(const int *a, const int *b) 
{ 
    return (*a > *b) - (*a < *b); 
}

#define REGISTER_ZTREE_TYPES(X) \
    X(int, int, IntMap, int_cmp)

#define ZTREE_SHORT_NAMES
#include "ztree.h"

int main(void)
{
    tree(IntMap) tree = tree_init(IntMap);

    tree_insert(&tree, 10, 100);
    tree_insert(&tree, 5, 50);

    tree_foreach(&tree, node) 
    {
        printf("%d -> %d\n", node->key, node->value);
    }
    
    tree_clear(&tree);
    return 0;
}
