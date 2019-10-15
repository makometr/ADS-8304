#include "mylist.h"

MyList::MyList(QObject *parent) : QObject(parent)
{
    /*
     * По умолчанию объект класса является пустым списком
    */

    isAtom = false;
    atom = 0;
    head = nullptr;
    tail = nullptr;
}


MyList::~MyList()
{
    /*
     * Т.к в классе используются умные указатели, освбождение
     * памяти происхоит автоматически
    */
}


bool MyList::isNull() const
{
    /*
     * Возвращает true, если элемент является нулевым списком,
     * false - в ином случае
    */

    return (!isAtom && head == nullptr && tail == nullptr);
}


MyList::MyListP MyList::getHead() const
{
    /*
     * Если элемент не атом - возращает указатель на вложенный список,
     * в ином случае - nullptr
    */

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
    /*
     * Если элемент не атом - возращает указатель на следующий список,
     * в ином случае - nullptr
    */

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
    /*
     * Если элемент атом - возращает true,
     * в ином случае - false
    */

    return isAtom;
}


MyList::MyListP MyList::cons(MyListP& head, MyListP& tail)
{
    /*
     * Функция создания списка
    */
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


void MyList::print_seq(QDebug& out) const
{
    /*
     * Функция печати Tail
    */

    if (!isNull()) {
        out << this->getHead();

        if (this->getTail() != nullptr)
            this->getTail()->print_seq(out);
    }
}


QDebug operator<<(QDebug out, const MyList::MyListP list)
{
    /*
     * Перегрузка оператора вывода для отладки пограммы
    */

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


bool MyList::checkStr(const std::string& str)
{
    /*
     * Функция проверки корректности входных данных,
     * принимает на вход ссылку на строку, проверяет размер и структуру строки,
     * возвращает true, если строка корректна, и false в ином случае
    */

    qDebug() << "Проверка на корректность:" << str.c_str();
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

    qDebug() << "Строка корректна.";
    return true;
}


void MyList::createAtom(const char ch)
{
    /*
     * Создается объект класса - атом
    */
    this->atom = ch;
    this->isAtom = true;
}


void MyList::readData(MyListP &list, const char prev, std::string::const_iterator &it,
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


void MyList::readSeq(MyListP& list, std::string::const_iterator&it,
                     const std::string::const_iterator& end)
{
    /*
     * Функция считывания списка. Рекусривно считывает данные и спискок и
     * добавляет их в исходный.
    */

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
    /*
     * Функция создания иерархического списка. Принимает на вход ссылку
     * на строку, проверяет корректность строки и вызывает приватный метод
     * readData().
    */


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
    /*
     * Функция возвращает значение атома
    */
    if (isAtom) {
        return atom;
    }
    else {
        std::cerr << "Error: getAtom(!atom)\n";
        return 0;
    }
}

