#include <iostream>
#include "redblacktree.h"

int main()
{
    RedBlackTree<int> t;
    t.setEventInfoOutput(&std::cout);

    std::cout << "Enter a number(s) to insert it to the tree (or non-number to exit):" << std::endl;

    for (int n = 0; std::cin >> n; ) {
        std::cout << std::endl;
        if (!t.contains(n)) {
            std::cout << "Inserting value " << n << std::endl;
            t.insert(n);
            std::cout << "Bracket view: " << t.toBracketView(std::to_string) << std::endl;
            std::cout << "Tree height = " << t.height() << std::endl;
        }
        else
            std::cout << "Rejecting value " << n << " because it already exists." << std::endl;
        std::cout << std::endl;
    }
    return 0;
}

