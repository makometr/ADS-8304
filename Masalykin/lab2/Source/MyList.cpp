//
// Created by Dan on 20.10.2019.
//

#include "MyList.h"

MyList::MyList()
{




    isAtom = false;
    atom = 0;
    head = nullptr;
    tail = nullptr;
}


MyList::~MyList()
{

}


bool MyList::isNull() const
{
   

    return (!isAtom && head == nullptr && tail == nullptr);
}


MyList::MyListP MyList::getHead() const
{
    

    if (!isAtom) {
        return head;
    }
    else {
        std::cerr << "Error: Head(atom)\n";
        return nullptr;
    }
}


MyList::MyListP MyList::getTail() const
{

    if (!isAtom) {
        return tail;
    }
    else {
        std::cerr << "Error: Tail(atom)\n";
        return nullptr;
    }
}


bool MyList::getIsAtom() const
{

    return isAtom;
}


MyList::MyListP MyList::cons(MyListP& head, MyListP& tail)
{
    if (tail != nullptr && tail->getIsAtom()) {
        std::cerr << "Error: Tail(atom)\n";
        return nullptr;
    }
    else {
        MyListP tmp(new MyList);
        tmp->head = head;
        tmp->tail = tail;
        return tmp;
    }
}






bool MyList::checkStr(const std::string& str)
{
   

    std::cout << "Validation check:" << str.c_str()<<std::endl;
    int countBracket = 0;

    if (str.size() < 2)
        return false;

    if (str[0] != '(' || str[str.size() - 1] != ')')
        return false;

    size_t i;
    for (i = 0; i < str.size(); ++i) {
        char elem = str[i];
        if (elem == '(')
            ++countBracket;
        else if (elem == ')')
            --countBracket;
        else if (!isalpha(elem))
            return false;

        if (countBracket <= 0 && i != str.size()-1)
            return false;
    }

    if (countBracket > 0 || i != str.size()) {
        return false;
    }

    std::cout<< "The line is correct."<<std::endl;
    return true;
}


void MyList::createAtom(const char ch)
{
   
    this->atom = ch;
    this->isAtom = true;
}


void MyList::readData(MyListP &list, const char prev, std::string::const_iterator &it,
                      const std::string::const_iterator& end)
{
    

    if (prev != '(') {
        list->createAtom(prev);
    }
    else {
        readSeq(list, it, end);
    }
}


void MyList::readSeq(MyListP& list, std::string::const_iterator&it,
                     const std::string::const_iterator& end)
{

    MyListP headList(new MyList);
    MyListP tailList(new MyList);

    if (it == end)
        return;

    if (*it == ')') {
        ++it;
    }
    else {
        char prev = *it;
        ++it;
        readData(headList, prev, it, end);
        readSeq(tailList, it, end);
        list = cons(headList, tailList);
    }
}


bool MyList::buildList(MyListP& list, const std::string& str)
{


    if (!checkStr(str))
        return false;

    auto it_begin = str.cbegin();
    auto it_end = str.cend();
    char prev = *it_begin;
    ++it_begin;
    readData(list, prev, it_begin, it_end);

    return true;
}


char MyList::getAtom() const
{
    
    if (isAtom) {
        return atom;
    }
    else {
        std::cerr << "Error: getAtom(!atom)\n";
        return 0;
    }
}

std::ostream& operator<<(std::ostream& out, const MyList::MyListP list)
{
    

    if (list == nullptr || list->isNull()) {
        out << "()";
    }
    else if (list->getIsAtom()) {
        out << list->getAtom();
    }
    else {
        out << "(";

        out << list->getHead();
        if (list->getTail() != nullptr)
            list->getTail()->print_seq(out);

        out << ")";
    }

    return out;
}

void MyList::print_seq(std::ostream& out) const
{
   

    if (!isNull()) {
        out << this->getHead();

        if (this->getTail() != nullptr)
            this->getTail()->print_seq(out);
    }
}
