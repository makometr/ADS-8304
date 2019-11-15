
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <cctype>
#include <string>
#include <iomanip>
#include <algorithm>


template <typename T>
class vStack {

  private:
	  T* mem;
	  int top;
	  int n;
    
  public:
      	  vStack(int length) { //конструктор класса
		  n = length;
		  mem = new T[n];
		  top = 0;
	  } 
      
	  int empty() const {
		  return top == 0;
	  }
      
	  void push(T elem){
		  mem[top++] = elem; 		
		  if (top > n) 
			  std::cout << "incorrect" << std::endl;
	  }
      
	  void pop(){ 
		  top--;
	  }
	  T get_top() {
			 return mem[top-1];


	  }
	  void print_stack(){
    		for (int i = n - 1; n >= 0; n--)
        	std::cout << "|" << std::setw(5) << mem[n] << std::endl;
	  }
	  ~vStack() {//деструктор класса
		  delete [] mem;
	  }

 };

bool readOperand(std::stringstream &ss, char cur){
	bool b;
	if (cur == 't') b = true;
	else if (cur == 'f') b = false;
	else {std::cout<<"incorrect\n"; exit(0);}

	while (cur!='e'){
		ss >> cur;
	}
	return b;
}

bool execOperation(char sign, bool op1, bool op2) {
	if (sign == 'V') 
		return op1 || op2;
	else if(sign == '^')
		return op1 && op2;
	else {std::cout<<"incorrect\n"; exit(0);}

}
void readLogicalExpr(vStack<bool> &stack, std::stringstream &ss) {
	
	
	char cur, sign;
	int flag = 0;
	bool leftop, rightop, invert = false;

	while (ss >> cur) {

		if (cur == '(') {
			readLogicalExpr(stack, ss);
		}
		else if (cur == '!') {
			invert = true;
			continue;
		}

		else if (cur == ')') {
			if (!invert) {
				rightop = stack.get_top();
				stack.pop();
				leftop = stack.get_top();
				stack.pop();
				stack.push(execOperation(sign, leftop, rightop));
			}
			else {
				bool a = stack.get_top();
				stack.pop();
				stack.push(!a);
			}return;
		}
		else if (cur == 'V' || cur == '^')	sign = cur;
	

		else {
			if (!flag) {
				leftop = readOperand(ss, cur);
				stack.push(leftop);
				flag = 1;
				continue;
				
			}
			else {
				rightop = readOperand(ss, cur);
				stack.push(rightop);
			}
		}
	}
	
}

void readFromFile(std::ifstream &file){


	std::stringstream ss;
	if(!file.is_open()){
  	  		std::cout<<"Неверный путь к файлу\n";
	    		return;
    		}

		std::string str;
		while (std::getline(file,str)){
			vStack<bool> stack(10);
			ss << str;
			readLogicalExpr(stack, ss);
			std::cout << str << "= " << stack.get_top() << std::endl;
			ss.clear();
			//stack.print_stack();

		}

}
int main(int argc, char* argv[]) {
	



	if (argc == 2) {

		std::ifstream file(argv[1]);
		readFromFile(file);
		
	}
	else {
		vStack<bool> stack(10);
		std::string s;
		std::stringstream ss;
		std::cout << "Введите логическое выражение:";
		std::getline(std::cin, s);
		s.erase(std::remove_if(s.begin(), s.end(), isspace),s.end());
		ss << s;
		readLogicalExpr(stack, ss);
		std::cout << "= " << stack.get_top() << std::endl;
		//stack.print_stack();


	}
	return 0;
}
		
