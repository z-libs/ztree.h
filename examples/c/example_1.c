
#include <stdio.h>
#include <string.h>

static int str_cmp(const char **a, const char **b) 
{
    return strcmp(*a, *b);
}

#define REGISTER_ZTREE_TYPES(X) \
    X(const char*, int, SymbolTable, str_cmp)

#define ZTREE_SHORT_NAMES
#include "ztree.h"

int main(void) 
{
    tree(SymbolTable) symbols = tree_init(SymbolTable);

    printf("=> Populating symbol table.\n");
    tree_insert(&symbols, "count", 1);      // int
    tree_insert(&symbols, "velocity", 2);   // float
    tree_insert(&symbols, "buffer", 3);     // char*
    tree_insert(&symbols, "alpha", 2);      // float

    printf("Symbols (Sorted):\n");
    tree_foreach(&symbols, it) 
    {
        printf("  %s: TypeID %d\n", it->key, it->value);
    }

    printf("\n=> Lookup and deletion.\n");
    
    if (tree_find(&symbols, "velocity")) 
    {
        printf("Found 'velocity'. Removing it (end of scope)...\n");
        tree_remove(&symbols, "velocity");
    }

    if (!tree_find(&symbols, "velocity")) 
    {
        printf("Verified: 'velocity' is gone.\n");
    }

    printf("\n=> Lower bound (autocomplete).\n");
    const char* search = "b";
    ztree_node_SymbolTable* lb = tree_lower_bound(&symbols, search);

    if (lb) 
    {
        printf("Lower bound for 'b' is '%s'.\n", lb->key);
        for (ztree_node_SymbolTable* n = lb; n != NULL; n = tree_next(n)) 
        {
            if (n->key[0] != 'b') 
            {
                break; 
            }
            printf("  -> Matching candidate: %s\n", n->key);
        }
    }

    tree_clear(&symbols);
    return 0;
}
