#include <iostream>
#include "Tree.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "You must set value" << std::endl;
        return 1;
    } else {
        Tree tr(atoi(argv[1]));
        for (int i = 2; i < argc; i++) {
            tr.insert_elem(atoi(argv[i]));
        }
        tr.cout_tree();
        tr.cout_leaves();
        std::cout << tr.dip_tree() << std::endl;
        std::cout << tr.nodes_at_level(1) << std::endl;
        std::cout << tr.dip_of_tree() << std::endl; 
        return 0;
    }
}
