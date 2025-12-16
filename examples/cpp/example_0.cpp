
#include <iostream>
#include <string>

static int score_cmp(const int* a, const int* b) 
{
    return (*b - *a);
}

#define REGISTER_ZTREE_TYPES(X) \
    X(int, std::string, Leaderboard, score_cmp)

#include "ztree.h"

int main() 
{
    z_tree::map<int, std::string> board;

    printf("=> Updating scores (operator []).\n");
    
    board[1500] = "Alice";
    board[2000] = "Bob";
    board[1200] = "Charlie";
    board[3000] = "Dave";

    std::cout << "Leaderboard:\n";
    
    for (auto entry : board) 
    {
        std::cout << "  " << entry.value() << ": " << entry.key() << " pts\n";
    }

    printf("\n=> Range query (lower bound).\n");
    
    int cutoff = 1800;
    auto it = board.lower_bound(cutoff);

    if (it != board.end()) 
    {
        std::cout << "Players with <= " << cutoff << " points (starting from top):\n";
        for (; it != board.end(); ++it) 
        {
             std::cout << "  " << it->length() << " chars (" << it.key() << ")\n";
        }
    }

    printf("\n=> Erase .\n");
    std::cout << "Removing Bob (Score 2000)...\n";
    board.erase(2000);

    if (board.find(2000) == nullptr) 
    {
        std::cout << "Bob is gone.\n";
    }

    return 0;
}
