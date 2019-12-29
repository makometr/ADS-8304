#include "queue.h"
#include <iostream>
#include <cstdlib>
#include <fstream>


int main(int argc, char* argv[]) {

    int lesser_value = 0;
    int greater_value = 0;

    std::string processed_string;
    std::string value_str;

    queue less_than_a;
    queue between_a_and_b;
    queue greater_than_b;

    std::ifstream input_file_stream(argv[1]);

    if(!input_file_stream) {
        std::cout << "File can't be open" << std::endl;
        return 1;
    }


    std::getline(input_file_stream, value_str);

    try {
        lesser_value = std::stoi(value_str);
    }
    catch(std::invalid_argument& exception) {
        std::cout << "Invalid argument of the lesser_value:" << value_str << std::endl;
        return 1;
    }
    catch(std::out_of_range& exception) {
        std::cout << "lesser_value is too large for INT to contain it!!!\nlesser_value: " << value_str << std::endl;
        return 1;
    }
    std::cout << "lesser_value: " << std::endl;
    std::cout << lesser_value << ' ' << std::endl;


    std::getline(input_file_stream, value_str);

    try {
        greater_value = std::stoi(value_str);
    }
    catch(std::invalid_argument& exception) {
        std::cout << "Invalid argument of the greater_value: " << value_str << std::endl;
        return 1;
    }
    catch(std::out_of_range& exception) {
        std::cout << "greater_value is too large for INT to contain it!!!\ngreater_value: " << value_str << std::endl;
        return 1;
    }
    std::cout << "greater_value: " << std::endl;
    std::cout << greater_value << ' ' << std::endl;


    if(lesser_value >= greater_value) {
        std::cout << "lesser_value must be lesser than greater_value" << std::endl;
        return 1;
    }


    std::getline(input_file_stream, processed_string);
    std::cout << "Processed string:\n" << processed_string << "\n______________________________" << std::endl;
	
	
    std::string current_digit_str;
    int counter = 0;

    for(auto proc_symbol: processed_string) {
        counter++;
		
        if(isdigit(proc_symbol)) {
            current_digit_str += proc_symbol;
            if(counter != processed_string.size()) {
                continue;
            }
        }
		else if(current_digit_str.empty()){
			continue;
		}
		
		int value = 0;
		try {
			value = std::stoi(current_digit_str);
		}
		catch(std::invalid_argument& exception) {
			std::cout << "Invalid argument of the found digit: " << current_digit_str << std::endl;
			return 1;
		}
		catch(std::out_of_range& exception) {
			std::cout << "Found digit is too large for INT to contain it!!!\nFound digit: " << current_digit_str << std::endl;
			return 1;
		}
		std::cout << "Current found digit: " << value << std::endl;

		if (value < lesser_value) {
			less_than_a.push(value);
		}
		else if (value >= lesser_value && value <= greater_value) {
			between_a_and_b.push(value);
		}
		else if (value > greater_value) {
			greater_than_b.push(value);
		}

		current_digit_str = "";
    }
    std::cout << "______________________________\n";

	
    queue::el popped_value;

    if (!less_than_a.getSize()) {
        std::cout << "No numbers in the first queue(lesser than A)" << std::endl;
    }
    else {
        std::cout << "Digits from the first queue(lesser than A)" << std::endl;

        while (less_than_a.getSize()) {
            popped_value = less_than_a.pop();
            std::cout << popped_value.value << ' ';
        }
    }
    std::cout << "\n______________________________";

    if (!between_a_and_b.getSize()) {
        std::cout << "No numbers in the second queue(Greater than lesser_value and lesser than greater_value)"
                  << std::endl;
    }
    else {
        std::cout << std::endl << "Digits from the second queue(greater than A and lesser than B)" << std::endl;

        while (between_a_and_b.getSize()) {
            popped_value = between_a_and_b.pop();
            std::cout << popped_value.value << ' ';
        }
    }
    std::cout << "\n______________________________";

    if (!greater_than_b.getSize()) {
        std::cout << "No numbers in the third queue(greater than B)" << std::endl;
    }
    else {
        std::cout << std::endl << "Digits from the third queue(greater than B)" << std::endl;

        while (greater_than_b.getSize()) {
            popped_value = greater_than_b.pop();
            std::cout << popped_value.value << ' ';
        }
    }
    std::cout << "\n______________________________";


    return 0;
}