#include "Dinamic_Hafman/tree.h"
#include "Static_Hafman/Static_Hafman.h"
#include <ctime>

void check() {
    std::string static_hafman_string;
    std::string dinamic_hafman_string;
    std::ifstream static_hafman("decode_message_Static_Hafman.txt");
    std::ifstream dinamic_hafman("decode_message_Dinamic_Hafman.txt");
    std::getline(static_hafman, static_hafman_string);
    std::getline(dinamic_hafman, dinamic_hafman_string);
    if (static_hafman_string == dinamic_hafman_string) {
        std::cout << "OK" << std::endl;
    } else {
        std::cout << "PROBLEM((" << std::endl;
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Необходимо ввести строку для кодирования, она может состоять только из букв английского алфавита в нижнем регистре!" << std::endl;
        return 1;
    }
    std::fstream input_file(argv[1]);
    if (!input_file) {
        std::cout << "Wrong open file!" << std::endl;
        return -2;
    } else {
        std::string input_file_string = {};
        std::getline(input_file, input_file_string);
        std::cout << input_file_string << std::endl;

        time_t start_dinamic = clock();
        use_dinamic(input_file_string);
        time_t end_dinamic = clock();

        use_static(input_file_string);
        time_t end_static = clock();

        std::ofstream static_time("static_file.txt");
        std::ofstream dinamic_time("dinamic_file.txt");
        dinamic_time << end_dinamic - start_dinamic;
        static_time << end_static - end_dinamic;

        //check();
        input_file.close();
        return 0;
    }
}
