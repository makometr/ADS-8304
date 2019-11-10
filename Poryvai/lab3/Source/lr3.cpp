// Непрерывная реализация на базе вектора 
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include<assert.h>
// интерфейс АТД "Стек" (см. Седжвик - Sedgewick) 
// шаблонный класс. Без некоторых проверок...
// и интерфейс, и реализация в этом заголовочном файле 
void inp(std::string str);


template <class Item>
class STACK
{
private:
	Item* s; int N; int N1; // my N1
public:
	STACK(int maxN)
	{
		s = new Item[maxN];
		N = 0;
 		N1 = maxN;
	}  // my N1
	bool empty() const
	{
		return N == 0;
	}
	void push(Item elem)
	{
		s[N++] = elem;
		if(N>N1)
			assert(1);
			
	}
	~STACK(){
		delete [] s;
		N1 = 0;
		N = 0;
	}
	Item pop()
	{	
		if(N!=0)
			return s[--N];
		else
			assert(1);
	}
	
};



int analizator(std::string& str){

	STACK<char> save(str.length());

	int flag = 1;
	int i = 0;

	while(i < str.length()) {

		if (str[i] == 'C') {
			i++;
			while (save.empty() == false) {

				char a = save.pop();
				if (str[i] != a) {
					flag = 0;

					break;//выход из внутр while
				}

				i++;

			}
			//break далее выход из внешнего while
			if(i == str.length())
				break;

			if(str[i] !='D')
				flag = 0;

			if (flag == 0)
				break;

		}
		else if(str[i] == 'A' || str[i] == 'B' ) {
			save.push(str[i]);
		}
		else {
			flag = 0;
			break;
		}

		i++;
	}

	return flag;


}

int main(int argc,char *argv[])
{
	setlocale(LC_ALL, "Russian");
	std::string str;
//	int flag;
	std::cout<<"Ввод из консоли или из файла?(c,f)"<<"\n";
	std::string arg;
	getline(std::cin,arg);
//	std::ofstream fout("out_wrong.txt");
	if(arg == "f"){

		std::ifstream fin(argv[1]);
		std::cout<<"Введите строку или комбинацию для выхода\n";

		while (getline(fin, str)) {
				std::cout<<"Введите строку или комбинацию для выхода\n";
				inp(str);

		}
	}
	else if( arg == "c"){
		std::cout<<"Введите строку или комбинацию для выхода\n";
		while(getline(std::cin, str)){
				std::cout<<"Введите строку или комбинацию для выхода\n";
      				inp(str);                      
		}


        }


}

void inp( std::string str ){
	
	std::ofstream fout("out_wrong.txt");
	int flag;
	 if (str != " " && str != "") {

                                flag = analizator(str);

                                if (flag == 1){
                                        std::cout<<str<<"\n";
                                        std::cout << "Cтрока задана верно" << "\n";
                                        std::cout<<"\n";
                                        fout<<str<<"\n";
                                        fout << "Cтрока задана верно" << "\n";
                                        fout<<"\n";
                                }
                                else{
                                        std::cout<<str<<"\n";
                                        std::cout << "Строка задана неверно" << "\n";
                                        std::cout<<"\n";
                                        fout<<str<<"\n";
                                        fout << "Строка задана неверно" << "\n";
                                        fout<<"\n";

                                }


        }
      	else{
        	std::cout << "Пустая строка" << "\n";
                std::cout<<"\n";
                fout<<"Пустая строка"<<"\n";
                fout<<"\n";
        }


}
