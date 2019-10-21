#include <iostream>
#include <cstdlib>
#include <fstream>
#include "BinTree.h"


int main(int argc, char* argv[]) {

    std::string str;
    std::string check_str = " ";
    int counter = 0, test_counter = 0;

    std::queue<BinTree<std::string>::elem*> queue;

    if (argc > 1) {
        std::ifstream in(argv[1]);
        if (!in.is_open()) {
            std::cout << "This file can't be open" << std::endl;
            return 1;
        }
        while (std::getline(in, str)) {
            std::cout << std::endl << "Test #" << ++test_counter << " " << str << std::endl;
            size_t find_cnt = str.find_first_not_of(check_str, 0);
            str.erase(0, find_cnt);
            BinTree<std::string> tree(20);
            if(tree.make_bin_tree(counter, str)) {
                tree.queue_output(tree.get_root(), queue);
            }
            counter = 0;
        }
        return 0;
    }
    else {
        BinTree<std::string> tree(20);
        std::cout << "Enter binary tree" << std::endl;
        std::getline(std::cin, str);
        size_t find_cnt = str.find_first_not_of(check_str, 0);
        str.erase(0, find_cnt);
        if(!tree.make_bin_tree(counter, str))
            return 1;
        tree.queue_output(tree.get_root(), queue);
    }
	
	   while(!queue.empty()) {
        delete(queue.front());
        queue.pop();
    }
    return 0;
}