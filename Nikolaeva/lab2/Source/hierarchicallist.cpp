#include "hierarchicallist.h"


HierarchicalList::HierarchicalList(QObject *parent): QObject (parent) , pair(Pointers())
{
    /*
     * По умолчанию объект класса является пустым списком
    */

    flagIsAtom = false;
}


std::string HierarchicalList::toStdString() const
{
    std::string list;
    if (this->isNull()) {
        list += "()";
    }
    else if (this->isAtom()) {
        list += this->getAtom();
    }
    else {
        list += '(';
        list += std::get<Pointers>(this->pair).head->toStdString();

        if (std::get<Pointers>(this->pair).tail != nullptr)
            std::get<Pointers>(this->pair).tail->tailToStdTring(list);

        list += ')';
    }

    return list;
}


void HierarchicalList::tailToStdTring(std::string &list)
{
    if (!isNull()) {
        list += this->getHead()->toStdString();

        if (this->getTail() != nullptr)
            this->getTail()->tailToStdTring(list);
    }
}


bool HierarchicalList::isNull() const
{
    /*
     * Возвращает true, если элемент является нулевым списком,
     * false - в ином случае
    */

    return (!flagIsAtom && std::get<Pointers>(this->pair).head == nullptr && std::get<Pointers>(this->pair).tail == nullptr);
}


HierarchicalList::ListPointer HierarchicalList::getHead() const
{
    /*
     * Возвращает указатель на вложенные списки
    */
    return std::get<Pointers>(this->pair).head;
}


HierarchicalList::ListPointer HierarchicalList::getTail() const
{
    /*
     * Возврщает указатель на следующий список
    */

    return std::get<Pointers>(this->pair).tail;
}


bool HierarchicalList::isAtom() const
{
    /*
     * Если элемент атом - возращает true,
     * в ином случае - false
    */

    return flagIsAtom;
}


HierarchicalList::ListPointer HierarchicalList::cons(ListPointer& head, ListPointer& tail)
{
    /*
     * Функция создания списка
    */

    if (tail != nullptr && tail->isAtom()) {
        std::cerr << "Error: Tail(atom)\n";
        return nullptr;
    }
    else {
        ListPointer tmp (new HierarchicalList);
        tmp->pair = Pointers(head, tail);
        return tmp;
    }
}


void HierarchicalList::print_seq(QDebug& out) const
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


QDebug operator<<(QDebug out, const HierarchicalList::ListPointer list)
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




void HierarchicalList::createAtom(const char ch)
{
    /*
     * Создается объект класса - атом
    */
    this->pair.emplace<char>(ch);
    this->flagIsAtom = true;
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


bool HierarchicalList::buildList(HierarchicalList::ListPointer& list, const std::string& str)
{
    /*
     * Функция создания иерархического списка. Принимает на вход ссылку
     * на строку, проверяет корректность строки и вызывает приватный метод
     * readData().
    */

    qDebug() << "В список добавляется содержимое следующих скобок:" << str.c_str();

    if (!isCorrectStr(str))
        return false;

    auto it_begin = str.cbegin();
    auto it_end = str.cend();
    char prev = *it_begin;
    ++it_begin;
    HierarchicalList::readData(list, prev, it_begin, it_end);

    return true;
}


char HierarchicalList::getAtom() const
{
    /*
     * Функция возвращает значение атома
    */
    if (flagIsAtom) {
        return std::get<char>(this->pair);
    }
    else {
        qDebug() << "Error: getAtom(!atom)\n";
        return 0;
    }
}

bool isCorrectStr(const std::string &str)
{
    /*
     * Функция проверки корректности входных данных,
     * принимает на вход ссылку на строку, проверяет размер и структуру строки,
     * возвращает true, если строка корректна, и false в ином случае
    */

    qDebug() << "Проверка на корректность:" << str.c_str();
    int countBracket = 0;

    if (str.size() < 2) {
        qDebug() << "Строка не корректна!";
        return false;
    }

    if (str[0] != '(' || str[str.size() - 1] != ')') {
        qDebug() << "Строка не корректна!";
        return false;
    }

    size_t i;
    for (i = 0; i < str.size(); ++i) {
        char elem = str[i];
        if (elem == '(') {
            ++countBracket;
        }
        else if (elem == ')') {
            --countBracket;
        }
        else if (!isalpha(elem)) {
            qDebug() << "Строка не корректна!";
            return false;
        }

        if (countBracket <= 0 && i != str.size()-1) {
            qDebug() << "Строка не корректна!";
            return false;
        }
    }

    if (countBracket > 0 || i != str.size()) {
        qDebug() << "Строка неккоректна!";
        return false;
    }

    qDebug() << "Строка корректна.";
    return true;
}


void HierarchicalList::reverseList(HierarchicalList::ListPointer& list, size_t depth)
{
    /*
     * Функция, реверсирующая исходный список. Принмиает на вход ссылку на
     * исходный список. Ничего не возвращает.
     *
     * В цикле реверсируется список, для вложенного списка вызывается рекурсия.
    */

    std::string debugStr;
    for (size_t i = 0; i < depth; ++i) {
        debugStr += " ";
    }

    qDebug() << debugStr.c_str() << "Список до разворота" << list;
    auto prev = HierarchicalList::ListPointer(nullptr);
    auto next = HierarchicalList::ListPointer(nullptr);
    auto current = list;

    while (current != nullptr && !current->isNull()) {
        if (!current->getHead()->isAtom() && !current->getHead()->isNull()) {
            reverseList(std::get<Pointers>(current->pair).head, depth+1);
        }

        next = std::get<Pointers>(current->pair).tail;
        std::get<Pointers>(current->pair).tail = prev;
        prev = current;
        current = next;
    }
    if (prev != nullptr)
        list = prev;
    qDebug() << debugStr.c_str() << "Список после разворота" << list;
}

