#include "queue.h"
#include <iostream>
#include <cstdlib>
#include <fstream>


int main(int argc, char* argv[]){

    int a,b;

    std::string processed_string;

    queue less_than_a;
    queue between_a_and_b;
    queue greater_than_b;

    std::string val_str;

    std::ifstream input_file_stream(argv[1]);

    if(!input_file_stream){
        std::cout << "File can't be open" << std::endl;
        return 1;
    }

    std::getline(input_file_stream, val_str);

    try {
        a = std::stoi(val_str);
    }
    catch(std::invalid_argument& exception){
        std::cout << "Invalid argument of the a-value:" << val_str << std::endl;
        return 1;
    }
    catch(std::out_of_range& exception){
        std::cout << "a-value is too large for INT to contain it!!!\na-value: " << val_str << std::endl;
        return 1;
    }


    std::cout << "a-value: " << std::endl;
    std::cout << a << ' ' << std::endl;



    std::getline(input_file_stream, val_str);

    try {
        b = std::stoi(val_str);
    }
    catch(std::invalid_argument& exception){
        std::cout << "Invalid argument of the b-value: " << val_str << std::endl;
        return 1;
    }
    catch(std::out_of_range& exception){
        std::cout << "b-value is too large for INT to contain it!!!\nb-value: " << val_str << std::endl;
        return 1;
    }

    std::cout << "b-value: " << std::endl;
    std::cout << b << ' ' << std::endl;



    if(a >= b){
        std::cout << "a-value must be lesser than b-value" << std::endl;
        return 1;
    }


    std::getline(input_file_stream, processed_string);

    std::cout << "Processed string:\n" << processed_string << "\n______________________________" << std::endl;

    std::string currently_processed_value_str;
    int counter = 0;


    for(auto proc_symbol:processed_string){

        counter++;

        if(isdigit(proc_symbol)){
            currently_processed_value_str += proc_symbol;
            if(counter != processed_string.size())
                continue;
        }

        if(!currently_processed_value_str.empty()) {

            int value;


            try {
                value = std::stoi(currently_processed_value_str);
            }
            catch(std::invalid_argument& exception){
                std::cout << "Invalid argument of the found digit:" << currently_processed_value_str << std::endl;
                return 1;
            }
            catch(std::out_of_range& exception){
                std::cout << "Found digit is too large for INT to contain it!!!\nFound digit: " << currently_processed_value_str << std::endl;
                return 1;
            }


            std::cout << "Current found digit: " << value << std::endl;

            if (value < a)
                less_than_a.push(value);
            else if (value >= a && value <= b)
                between_a_and_b.push(value);
            else if (value > b)
                greater_than_b.push(value);

            currently_processed_value_str = "";
        }

    }
    std::cout << "\n______________________________\n";


    queue::el popped_value;


    if (!less_than_a.getSize())
        std::cout << "No numbers in the first queue(lesser than A)" << std::endl;

    else if(less_than_a.getSize()){
        std::cout << "Digits from the first queue(lesser than A)" << std::endl;

        while (less_than_a.getSize()) {
            popped_value = less_than_a.pop();
            std::cout << popped_value.value << ' ';
        }
    }
    std::cout << "\n______________________________\n";


    if (!between_a_and_b.getSize())
        std::cout << "No numbers in the second queue(Greater than a and lesser than b)" << std::endl;

    else {
        std::cout << std::endl << "Digits from the second queue(greater than A and lesser than B)" << std::endl;

        while (between_a_and_b.getSize()) {
            popped_value = between_a_and_b.pop();
            std::cout << popped_value.value << ' ';
        }
    }
    std::cout << "\n______________________________\n";


    if (!greater_than_b.getSize())
        std::cout << "No numbers in the third queue(greater than B)" << std::endl;

    else {
        std::cout << std::endl << "Digits from the third queue(greater than B)" << std::endl;

        while (greater_than_b.getSize()) {
            popped_value = greater_than_b.pop();
            std::cout << popped_value.value << ' ';

        }
    }
    std::cout << "\n______________________________\n";


    return 0;
}