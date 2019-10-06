#include <iostream>
#include <cstdlib>
#include <fstream>
#include "krm.h"


int main(int argc, char* argv[]) {
    krm k(0);
    krm p(0);

    if(argc > 1){

        std::ifstream in(argv[1]);

        if(!in) {
            std::cout << "File can't be open" << std::endl;
            return 1;
        }

        ;
        if(!k.read_k(in))
            return 1;

        std::cout << "First entered koromyslo: ";
        k.print_k();
        std::cout << std::endl << "_________________________" << std::endl;


        if(!p.read_k(in))
            return 1;

        std::cout << "Second entered koromyslo: ";
        p.print_k();
        std::cout << std::endl << "_________________________" << std::endl;
    }

    else {

        std::cout << "Enter koromyslo" << std::endl;

        if(!k.read_k(std::cin))
            return 1;

        std::cout << "Enter podkoromyslo" << std::endl;
        if(!p.read_k(std::cin))
            return 1;
    }

    std::cout << "Entered koromyslo: " << std::endl;
    k.print_k(); std::cout << std::endl << "_________________________" << std::endl;
    std::cout << "Entered podkoromyslo: " << std::endl;
    p.print_k(); std::cout << std::endl << "_________________________" << std::endl;

    std::cout << "Results of search:" << std::endl;

    int n = 0;
    std::string s;
    k.find_k(p, s, n);

    if(!n)
        std::cout << "No matches were found" << std::endl;

    return 0;
}
//((1 6)(2 5))
//((1 6)(2 5))
//C:\Users\Anton\CLionProjects\ADS_lab2\test\t1.txt