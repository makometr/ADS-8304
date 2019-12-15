#include "hierarchicallist.h"

HierarchicalList::HierarchicalList()
{
    /*
     * По умолчанию объект класса является пустым списком
    */

    flag = false;
    atom = 0;

}


HierarchicalList::~HierarchicalList()
{
    
}


bool HierarchicalList::isNull() const
{
    /*
     * Возвращает true, если элемент является нулевым списком,
     * false - в ином случае
    */

    return (!flag && nestedList == nullptr && nextList == nullptr);
}


HierarchicalList::ListPointer HierarchicalList::getHead() const
{
    /*
     * Если элемент не атом - возращает указатель на вложенный список,
     * в ином случае - nullptr
    */

    if (!flag) {
        return nestedList;
    }
    else {
        std::cout << "Error: Head(atom)\n";
        return nullptr;
    }
}


HierarchicalList::ListPointer HierarchicalList::getTail() const
{
    /*
     * Если элемент не атом - возращает указатель на следующий список,
     * в ином случае - nullptr
    */

    if (!flag) {
        return nextList;
    }
    else {
        std::cerr << "Error: Tail(atom)\n";
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


HierarchicalList::ListPointer HierarchicalList::cons(ListPointer& head, ListPointer& tail)
{

    if (tail != nullptr && tail->isAtom()) {
        std::cout << "Error: Tail(atom)\n";
        return nullptr;
    }
    else {
        ListPointer tmp(new HierarchicalList);
        tmp->nestedList = head;
        tmp->nextList = tail;
        return tmp;
    }
}


void HierarchicalList::print_seq(std::ostream& out) const
{
    /*
     * Функция печати Tail
    */

    if (!isNull()) {
        out << getHead();

        if (getTail() != nullptr)
            getTail()->print_seq(out);
    }
}


void HierarchicalList::swapElements(ListPointer list, const char oldElem, const char newElem)
{
    /*
     * Рекурсивная функция замены одного элемента списка на другой.
     * Принимает на вход умный указатель на список, элемент, который надо заменить и
     * элемент, на который надо заменить. Глубина рекурсии передается параметром depth.
     *
     * Если текущий список "пустой" - это базовый случай.
     * Если текущий список "не атом" - это рекурсивный случай.
     *
     * Если список - атом, проверяется, совпадает ли элемент с тем, который надо заменить,
     * и происходит замена.
    */


    //Если список пустой
    if (list == nullptr || list->isNull()) {
        return;
    }
    //Если список - атом
    else if (list->isAtom()) {
        if (list->atom == oldElem) {
            list->atom = newElem;
        }
    }
    //Вызов рекурсии для следующих списков
    else {
        swapElements(list->nestedList, oldElem, newElem);
        swapElements(list->nextList, oldElem, newElem);
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

        out << list->getHead();
        if (list->getTail() != nullptr)
            list->getTail()->print_seq(out);

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

    std::cout << "isCorrect str: " << str << "\n";
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

    std::cout << "Str is correct.\n";
    return true;
}


void HierarchicalList::createAtom(const char ch)
{
    /*
     * Создается объект класса - атом
    */
    atom = ch;
    flag = true;
}


void HierarchicalList::readData(ListPointer& list, const char prev, std::string::const_iterator &it,
                                const std::string::const_iterator& end)
{
    /*
     * Функция считывания данных. Считывает либо атом, либо рекурсивно считывает список
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

    ListPointer headList(new HierarchicalList);
    ListPointer tailList(new HierarchicalList);

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


bool HierarchicalList::buildList(ListPointer& list, const std::string& str)
{
    /*
     * Функция создания иерархического списка. Принимает на вход ссылку
     * на строку, проверяет корректность строки и вызывает приватный метод
     * readData().
    */

    std::cout << "Creating list from str: " << str << "\n";

    if (!isCorrectStr(str)) {
        std::cout << "Str is incorrect!!!\n";
        return false;
    }

    auto it_begin = str.cbegin();
    auto it_end = str.cend();
    char prev = *it_begin;
    ++it_begin;

    readData(list, prev, it_begin, it_end);

    return true;
}


char HierarchicalList::getAtom() const
{
    /*
     * Функция возвращает значение атома
    */
    if (flag) {
        return atom;
    }
    else {
        std::cout << "Error: getAtom(!atom)\n";
        return 0;
    }
}

