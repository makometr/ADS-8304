#include "hierachy.h"

HierarchicalList::HierarchicalList()
{
    /*
     * По умолчанию объект класса является пустым списком
    */

    flag = false;
    data = 0;
}


bool HierarchicalList::isNull() const
{
    /*
     * Возвращает true, если элемент является нулевым списком,
     * false - в ином случае
    */

    return (!flag && nestedList == nullptr && nextList == nullptr);
}


HierarchicalList::ListPointer HierarchicalList::getNext() const
{
    /*
     * Если элемент не атом - возращает указатель на вложенный список,
     * в ином случае - nullptr
    */

    if (!flag) {
        return nextList;
    }
    else {
        std::cerr << "Error: Next(atom)\n";
        return nullptr;
    }
}


HierarchicalList::ListPointer HierarchicalList::getNested() const
{
    /*
     * Если элемент не атом - возращает указатель на следующий список,
     * в ином случае - nullptr
    */

    if (!flag) {
        return nestedList;
    }
    else {
        std::cerr << "Error: Nested(atom)\n";
        return nullptr;
    }
}


bool HierarchicalList::isAtom() const
{
    /*
     * Если элемент атом - возращает true,
     * в ином случае - false
    */

    return flag;
}


HierarchicalList::ListPointer HierarchicalList::cons(ListPointer& nestedList, ListPointer& nextList)
{
    /*
     * Функция создания списка
    */

    if (nextList != nullptr && nextList->isAtom()) {
        std::cerr << "Error: Next(atom)\n";
        return nullptr;
    }
    else {
        ListPointer tmp(new HierarchicalList);
        tmp->nestedList = nestedList;
        tmp->nextList = nextList;
        return tmp;
    }
}


char HierarchicalList::getAtom() const
{
    /*
     * Функция возвращает значение атома
    */
    if (flag) {
        return data;
    }
    else {
        std::cerr << "Error: getAtom(!atom)\n";
        return 0;
    }
}


void HierarchicalList::print_seq(std::ostream& out) const
{
    /*
     * Функция печати Tail
    */

    if (!isNull()) {
        out << this->getNested();

        if (this->getNext() != nullptr)
            this->getNext()->print_seq(out);
    }
}


std::ostream& operator<<(std::ostream& out, const HierarchicalList::ListPointer& list)
{
    /*
     * Перегрузка оператора вывода
    */

    if (list == nullptr || list->isNull()) {
        out << "()";
    }
    else if (list->isAtom()) {
        out << list->getAtom();
    }
    else {
        out << "(";

        out << list->getNested();
        if (list->getNext() != nullptr)
            list->getNext()->print_seq(out);

        out << ")";
    }

    return out;
}


bool HierarchicalList::isCorrectStr(const std::string& str)
{
    /*
     * Функция проверки корректности входных данных,
     * принимает на вход ссылку на строку, проверяет размер и структуру строки,
     * возвращает true, если строка корректна, и false в ином случае
    */

    std::cout << "Проверка на корректность:" << str << "\n";
    int countBracket = 0;

        if (str.size() < 2){
            std::cout << "Строка Некорректна.\n";
            return false;
        }

    if (str[0] != '(' || str[str.size() - 1] != ')'){
        std::cout << "Строка Некорректна.\n";
        return false;
    }

    size_t i;
    for (i = 0; i < str.size(); ++i) {
        char elem = str[i];
        if (elem == '(')
            ++countBracket;
        else if (elem == ')')
            --countBracket;
        else if (!isalpha(elem)){
            std::cout << "Строка Некорректна.\n";
            return false;
        }

        if (countBracket <= 0 && i != str.size()-1){
            std::cout << "Строка Некорректна.\n";
            return false;
        }
    }

    if (countBracket != 0 || i != str.size()) {
        std::cout << "Строка Некорректна.\n";
        return false;
    }

    std::cout << "Строка корректна.\n";
    return true;
}


void HierarchicalList::createAtom(const char ch)
{
    /*
     * Создается объект класса - атом
    */
    this->data = ch;
    this->flag = true;
}


void HierarchicalList::readData(ListPointer& list, const char prev, std::string::const_iterator &it,
                                const std::string::const_iterator& end)
{
    /*
     * Функция считывания данных. Считывает либо атом, лио рекурсивно считывает список
    */

    if (prev != '(') {
        list->createAtom(prev);
    }
    else {
        readSeq(list, it, end);
    }
}


void HierarchicalList::readSeq(ListPointer& list, std::string::const_iterator&it,
                               const std::string::const_iterator& end)
{
    /*
     * Функция считывания списка. Рекусривно считывает данные и спискок и
     * добавляет их в исходный.
    */

    ListPointer nestedList(new HierarchicalList);
    ListPointer nextList(new HierarchicalList);

    if (it == end)
        return;

    if (*it == ')') {
        ++it;
    }
    else {
        char prev = *it;
        ++it;
        readData(nestedList, prev, it, end);
        readSeq(nextList, it, end);
        list = cons(nestedList, nextList);
    }
}


bool HierarchicalList::buildList(ListPointer& list, const std::string& str)
{
    /*
     * Функция создания иерархического списка. Принимает на вход ссылку
     * на строку, проверяет корректность строки и вызывает приватный метод
     * readData().
    */

    std::cout << "В список добавляется содержимое следующих скобок:" << str << "\n";

    if (!isCorrectStr(str))
        return false;

    auto it_begin = str.cbegin();
    auto it_end = str.cend();
    char prev = *it_begin;
    ++it_begin;
    readData(list, prev, it_begin, it_end);

    return true;
}
