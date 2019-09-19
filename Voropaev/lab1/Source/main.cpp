#include <iostream>
#include <string>
#include <fstream>
#define Square "[[B](A)]"
#define Round  "((A)[B])"

// Функция, проверяющая входную строку на соответсвие изначальному условию:
// ск::= кв|кр
// кв::= [[кв](кр)]|B
// кр::= ((кр)[кв])|A

void collapse(std::string& source, size_t n){// source - cсылка на исходную строку, n - счетчик глубины рекурсии
    size_t s_ptr = source.find(Square);
    if (s_ptr != std::string::npos) {
        source.erase(s_ptr, 8);
        source.insert(s_ptr, "B");
    }

    size_t r_ptr = source.find(Round);
    if (r_ptr != std::string::npos) {
        source.erase(r_ptr, 8);
        source.insert(r_ptr, "A");
    }
    std::cout << "Current collapsed string: " + source << std::endl;
    std::cout << "Depth of recursion: " << n << std::endl;
    std::cout << "_______________________________" << std::endl;

    if (s_ptr == std::string::npos && r_ptr == std::string::npos)
        return;

    collapse(source, ++n);

}


void check(std::string& input)// input - строка,вводимая ползватаелем; n - счетчик для подсчёта глубины рекурсии
{

    collapse(input, 0);

    if (input == "A" || input == "B") {
        std::cout << "Result : True\n###############################" << std::endl;
    }
    else{
        std::cout << "Result : False\n##############################" << std::endl;
    }
}

bool check_string(std::string str){
	for (int i = 0; i < str.size(); i++) {
                if (str[i] != 'A' && str[i] != 'B' && str[i] != '(' && str[i] != ')' && str[i] != '[' && str[i] != ']' && str[i] != '\n')
					return false;	
	}
	return true;
}

int main(int argc, char* argv[])
{

    std::string s;
    if (argc > 1) {
        std::string path;
		std::cout << "Enter the path to the folder with tests" << std::endl; 
		std::cin >> path;
        path += argv[1];
		std::cout << "Path: " + path << std::endl;
        std::ifstream str(path);
        while (std::getline(str, s)){
			
            s.erase(s.end() - 1);
			
            //Checking for invalid symbols	
            if (!check_string(s)){
                std::cout << "Entered string: " + s + " contains invalid symbols\n#########################" << std::endl;

                continue;
            }
			std::cout << "Entered string: " + s + "\n"<< std::endl;
            check(s);
        }
    }
    else if(argc == 1){
        std::cout << "Enter string: " << std::endl;;
        std::cin >> s;

        if(!check_string(s)){
                std::cout << "Entered string: " + s + " contains invalid symbols\n" << std::endl;
                return 0;
        }
		
		check(s);
    }

    

    return 0;

}