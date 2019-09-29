//
// Created by Anton on 23.09.2019.
//

#include "krm.h"
#include <iostream>

void krm::print_k(){

    std::cout << "((" << e->left->len << ' ';
    if (std::holds_alternative<int>(e->left->value))
        std::cout << std::get<int>(e->left->value);
    else {
        std::get<krm*>(e->left->value)->print_k();
    }
    std::cout << ")(";

    std::cout << e->right->len << ' ';
    if(std::holds_alternative<int>(e->right->value))
        std::cout << std::get<int>(e->right->value) << "))";
    else {
        std::get<krm*>(e->right->value)->print_k();
        std::cout << "))";;
    }
}

void krm::find_k(krm& p, std::string s, int& n) {


    std::string tmp(s);
    bool first,second;
    first = std::holds_alternative<krm*>(e->left->value);
    second = std::holds_alternative<krm*>(e->right->value);


    if(first) {//Проверка левого плеча на содержание подкоромысла
        s.push_back('1');
        std::get<krm*>(e->left->value)->find_k(p, s, n);
    }


    if(second) {//Проверка правого плеча на содержание подкоромысла
        tmp.push_back('2');
        std::get<krm *>(e->right->value)->find_k(p, tmp, n);
    }


    if(!second && !first && std::get<int>(e->left->value) == std::get<int>(p.e->left->value)
        && e->left->len == p.e->left->len
        && std::get<int>(e->right->value) == std::get<int>(p.e->right->value)
        && e->right->len == p.e->right->len){
        std::cout << '1' << s <<  ": Match!!!" << std::endl;
        n++;
    }
}




bool krm::make_atom(std::istream& input, krm* y, int mode) {


    char v;
    std::string str;
    char* ptr;

    while (true) {
        input >> std::noskipws >> v;
        if (v >= '0' && v <= '9') {
            str.push_back(v);
            continue;
        }
        if (v == ' ')
            break;
        else {
            std::cout << "Unexpected symbol in the input stream(make_atom/len)" << std::endl;
            return false;
        }
    }

    if(mode == 1)
        y->e->left->len = std::strtol(str.data(), &ptr, 10);
    else if(mode == 2)
        y->e->right->len = std::strtol(str.data(), &ptr, 10);

    str.clear();

    while (true) {
        input >> std::noskipws >> v;
        if (v >= '0' && v <= '9') {
            str.push_back(v);
            continue;
        }
        else if (v == '(') {
            krm* lower = new krm(y->e->depth + 1);
            input >> v;
            if(mode == 1)
               y->e->left->value.emplace<krm*>(lower);
            else if(mode == 2)
                y->e->right->value.emplace<krm*>(lower);

            lower->e->parent = y;

            if(make_atom(input, lower, 1))
                do input >> v; while(v == ' ');
            else
                return false;

            if(!make_atom(input, lower, 2))
                return false;

        } else if (v == ')') {
                if(mode == 2)
                    input >> v;
            break;
        }
        else{
            return false;
        }

    }

    if(v != ')'){
        std::cout << "Unexpected symbol in the input stream(make_atom/value)" << std::endl;
        return false;
    }



    if(mode == 1){
        if (std::holds_alternative<int>(y->e->left->value))
            y->e->left->value.emplace<int>(std::strtol(str.data(), &ptr, 10));
    }
    if (mode == 2) {
        if (std::holds_alternative<int>(y->e->right->value))
            y->e->right->value.emplace<int>(std::strtol(str.data(), &ptr, 10));
        }

    return true;
}


bool krm::read_k(std::istream& input){

    char x;
    do input >> x; while (x == ' ');
    if(x != '(')
        std::cout << "Unexpected symbol in the input stream(read_k/first_symbol)" << std::endl;
    input >> x;

    if (x == '(' && make_atom(input, this, 1)) {
        do input >> x;
        while (x == ' ');
    }
    else{
        return false;
    }



    if (x == '(' && make_atom(input, this, 2)) {
        input >> x;
    }
    else{
        return false;
    }

    return true;
}
