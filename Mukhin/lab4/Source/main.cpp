#include <iostream>
#include "Tree.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Set a root value!" << std::endl << std::string(40, '_') << std::string(3, '\n');
        return 1;
    } else {
        Tree tr(atoi(argv[1]));
        for (int i = 2; i < argc; i++) {
            tr.insert(atoi(argv[i]));
        }
        tr.print_tree();
        std::cout << "Dip: " << tr.dip() << std::endl;
        tr.print_leaves();
        std::cout << "Number of elements in the n level: "<< tr.count_nodes_in_level(1) << std::endl;
        std::cout << "Dip of the tree: "<< tr.tree_length() << std::endl << std::string(40, '_') << std::string(3, '\n');
        return 0;
    }
}
