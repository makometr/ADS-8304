#include <iostream>
#include "DynamicStack.h"
#include <fstream>
#include <string>

void back(std::ifstream* file);
void front(std::ifstream* file);
void print_reverse_stacks(DynamicStack<int>* stack_open, DynamicStack<int>* stack_close);

int main(int argc, char* argv[]) {
    if(argc == 1){
        std::cout<<"No input file"<<std::endl;
        return 1;
    }
    std::ifstream file;
    file.open(argv[1]);
    if(!file.is_open()){
        std::cout<<"Can't open file"<<std::endl;
        return 1;
    }

    int flag;
    std::cout<<"back(1) or front(0)"<<std::endl;
    std::cin>>flag;
    if(flag)
        back(&file);
    else
        front(&file);
    file.close();
    return 0;
}

void back(std::ifstream* file){
    DynamicStack<int> stack;
    std::string inp_str;
    while(getline(*file, inp_str)){
    std::cout<<"{";
    for(unsigned int i = 0; i < inp_str.size(); i++){
        if(inp_str[i] == '('){
            stack.push(i+1);
        }
        else if(inp_str[i] == ')'){
            std::cout<<stack.pop()<<" "<<i+1<<"|";
        }
    }
    std::cout<<"}"<<std::endl;;
   }
}

void print_reverse_stacks(DynamicStack<int>* stack_open, DynamicStack<int>* stack_close){
	DynamicStack<int> tmp_open, tmp_close;
	while(stack_open->size() > 0){
		tmp_open.push(stack_open->pop());
	}
	while(tmp_open.size() > 0){
		std::cout<<tmp_open.pop()<<" "<<stack_close->pop()<<"|";
	}
}

void front(std::ifstream* file){
    DynamicStack<int> stack_open, stack_close;
    std::string inp_str;
    while(getline(*file, inp_str)){
    std::cout<<"{";
    for(unsigned int i = 0; i < inp_str.size(); i++){
        if(inp_str[i] == '('){
            stack_open.push(i + 1);
        }
        else if(inp_str[i] == ')'){
	    stack_close.push(i+1);
	    }
	if(stack_open.size() == stack_close.size() && stack_open.size() > 0 && stack_close.size() > 0){
	    print_reverse_stacks(&stack_open, &stack_close);
	}
    }
    std::cout<<"}"<<std::endl;
    }
}
