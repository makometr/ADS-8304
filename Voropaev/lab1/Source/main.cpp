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



int main(int argc, char* argv[])
{

    std::string s;
    if (argc > 1) {
        std::string path = "Test/";
        path += argv[1];
        int flag = 0; //Flag to check the entered string(1 - true, 2 - false)
        std::ifstream str(path);
        while (std::getline(str, s)) {
			flag = 1;
            //удаление символа конца строки
			/*size_t ptr = s.find("\n", s.length() - 2);
			if(ptr != std::string::npos){
				s.erase(s.end() - 1);
			}*/
			
            s.erase(s.end() - 1);
			
            //Checking for invalid symbols
            for (int i = 0; i < s.size(); i++) {
                if (s[i] != 'A' && s[i] != 'B' && s[i] != '(' && s[i] != ')' && s[i] != '[' && s[i] != ']' && s[i] != '\n'){
                    flag = 0;
					break;
				}
            }
			


            if (!flag) {
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

        for (int i = 0; i < s.size(); i++) {
            if (s[i] != 'A' && s[i] != 'B' && s[i] != '(' && s[i] != ')' && s[i] != ' ' && s[i] != '[' && s[i] != ']') {
                std::cout << "Entered string: " + s + " contains invalid symbols\n" << std::endl;
                return 0;
            }
        }
		
		check(s);
    }

    

    return 0;

}