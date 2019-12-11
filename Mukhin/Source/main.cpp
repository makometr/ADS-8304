#include "Dinamic_Hafman/tree.h"
#include "Static_Hafman/Static_Hafman.h"
#include <ctime>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Необходимо ввести строку для кодирования, она может состоять только из букв английского алфавита в нижнем регистре!" << std::endl;
        return 1;
    } else {
        time_t start_dinamic = clock();
        use_dinamic(argc, argv);
        time_t end_dinamic = clock();

        use_static(argc, argv);
        time_t end_static = clock();

        std::cout << "Dinamic: " << end_dinamic - start_dinamic << std::endl;
        std::cout << "Static: " << end_static - end_dinamic;
        return 0;
    }
}
