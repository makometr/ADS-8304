#include <iostream>

#include "redblackdemotree.h"

int main()
{
    RedBlackDemoTree tree;
    auto demonstrator = tree.getHtmlDemonstrator();

    std::cout
        << "This program waits to enter following possible actions:" << std::endl
        << "'i' - insert value to the red-black tree (requires number)," << std::endl
        << "'r' - remove value from the red-black tree (requires number)." << std::endl
        << "The program will close if you enter incorrectly." << std::endl
        << "Example: i7 i 8 r7 exit" << std::endl
        << "The result will be written to the file red-black-tree-demo.html" << std::endl
        << "Enter actions: " << std::endl;

    char action;
    int number;
    while (true) {
        if (!(std::cin >> action && (action == 'i' || action == 'r')))
            break;
        if (!(std::cin >> number))
            break;
        std::cout << std::endl;

        if (action == 'i') {
            if (!tree.contains(number)) {
                std::string message = "Inserting value " + std::to_string(number);
                std::cout << message << std::endl;
                demonstrator->printHeading(message);
                tree.insert(number);
            }
            else {
                std::string message = "Rejecting value " + std::to_string(number) + " because it already exists.";
                std::cout << message;
                demonstrator->printHeading(message);
            }
        } else { // action = 'r'
            std::string message = "Removing value " + std::to_string(number);
            std::cout << message << std::endl;
            demonstrator->printHeading(message);
            tree.remove(number);
        }

        std::cout << std::endl;
        demonstrator->printDivisor();
        demonstrator->writeToFile("red-black-tree-demo.html");
    }
    return 0;
}

