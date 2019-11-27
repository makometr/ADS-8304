#include <iostream>
#include <string>
#include <fstream>

std::ofstream fOut;
template <class Item>
class Stack {
    private:
    	Item *s;
		int N, N1;
    public:
    	Stack(int maxN) {
			s = new Item[maxN];
			N = 0;
			N1 = maxN;
		}
    	bool empty() const {
			return N == 0;
		}
    	void push(Item elem) {
			s[N++] = elem; 		
			if (N > N1) {
				std::cerr << "Error!";
			}
		}
    	Item pop() {
    		if(N != 0){
				return s[--N];
			}
			else{
				std::cerr << "Error!";
				return 0;
			}
		}
		~Stack(){
			delete [] s;
			N1 = 0;
			N = 0;
		}
};

void OpenBrackets(std::string textExpression){
	bool flag = true;
	int counter = 0;
	int counterAfterBracket = 0;
	int counterCloseBrackets = 0;
	Stack<int> stackPositions(2);
	fOut << "      b)";
	while(textExpression[counter] != '\0'){
		if(textExpression[counter] == '('){
			counterCloseBrackets = counter + 1;
			while(flag){
				if(counterAfterBracket == 0 && textExpression[counterCloseBrackets] == ')'){
					stackPositions.push(counterCloseBrackets);
					stackPositions.push(counter);
					flag = false;
				}
				else if(textExpression[counterCloseBrackets] == '('){
					counterCloseBrackets++;
					counterAfterBracket++;
				}
				else if(textExpression[counterCloseBrackets] == ')'){
					counterCloseBrackets++;
					counterAfterBracket--;
				}
				else{
					counterCloseBrackets++;
				}
			}
			flag = true;
			counterCloseBrackets = 0;
			fOut << " " << stackPositions.pop() + 1 << " " << stackPositions.pop() + 1 << ";";
		}
		
		counter++;
	}
	fOut << std::endl;
}

void CloseBrackets(std::string textExpression){
	bool flag = true;
	int counter = 0;
	int counterAfterBracket = 0;
	int counterOpenBrackets = 0;
	Stack<int> stackPositions(2);
	fOut << textExpression << std::endl << "a)";
	while(textExpression[counter] != '\0'){
		if(textExpression[counter] == ')'){
			stackPositions.push(counter);
			counterOpenBrackets = counter - 1;
			while(flag){
				if(counterAfterBracket == 0 && textExpression[counterOpenBrackets] == '('){
					stackPositions.push(counterOpenBrackets);
					flag = false;
				}
				else if(textExpression[counterOpenBrackets] == ')'){
					counterOpenBrackets--;
					counterAfterBracket++;
				}
				else if(textExpression[counterOpenBrackets] == '('){
					counterOpenBrackets--;
					counterAfterBracket--;
				}
				else{
					counterOpenBrackets--;
				}
			}
			flag = true;
			counterOpenBrackets = 0;
			fOut << " " << stackPositions.pop() + 1 << " " << stackPositions.pop() + 1 << ";";
		}
		
		counter++;
	}	
}

int main(){
	std::ifstream fEnter("Tests/TestData.txt");
	fOut.open("Result.txt");
	std::string textExpression;
	fEnter >> textExpression;
	while(textExpression != "END")
	{
		CloseBrackets(textExpression);
		OpenBrackets(textExpression);
		fEnter >> textExpression;
	}
	fEnter.close();
	fOut.close();
	return 0;
}