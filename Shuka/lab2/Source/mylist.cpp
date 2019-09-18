#include "mylist.h"

MyList::MyList(QObject *parent) : QObject(parent)
{
    /*
     * По умолчанию объект класса является списком
    */

    isAtom = false;
    atom = 0;
}


MyList::~MyList()
{
    /*
     * Освобождение выделенной под список памяти
    */

    for (auto elem : childArray)
        delete elem;
}


QDebug& operator<<(QDebug& out, const MyList& list)
{
    /*
     * Перегрузка оператора вывода для отладки пограммы
    */

    out << "(";

    for (auto elem:list.childArray) {
        if (elem->isAtom)
            out << elem->atom;
        else
            out << *elem;
    }

    out << ")";
    return out;
}


bool MyList::checkStr(const std::string& str) const
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

    size_t i;
    for (i = 0; i < str.size(); ++i) {
        char elem = str[i];
        if (elem == '(')
            ++countBracket;
        else if (elem == ')')
            --countBracket;
        else if (!isalpha(elem))
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
     * Объект класса становится листом списка - атомом
    */

    this->atom = ch;
    this->isAtom = true;
}


bool MyList::buildList(const std::string& str)
{
    /*
     * Функция создания иерархического списка. Принимает на вход ссылку
     * на строку, проверяет корректность строки и рекурсивно создает список. Если
     * элемент - атом, тогда он добавляется в вектор указателей, если элемент - список,
     * тогда он создается рекурсивно и добавляется в вектор указателей.
    */

    qDebug() << "В список добавляется содержимое следующих скобок:" << str.c_str();

    if (!checkStr(str))
        return false;

    size_t i = 1;
    int countBracket = 0;

    while (i < str.size() - 1) {
        if (isalpha(str[i])) {
            qDebug() << "Добавялется атом:" << str[i];

            MyList *tmp = new MyList;
            tmp->createAtom(str[i]);
            childArray.push_back(tmp);
        }
        else {
            size_t j = i;
            ++countBracket;
            ++i;
            while (countBracket != 0) {
                if (str[i] == '(')
                    ++countBracket;
                else if (str[i] == ')')
                    --countBracket;
                ++i;
            }
            MyList* tmp = new MyList;
            tmp->buildList(str.substr(j, i-j));
            childArray.push_back(tmp);
            --i;
        }
        ++i;
    }

    return true;
}


size_t MyList::size() const
{
    /*
     * Функция возвращает количество вложенных списков и атомов
    */

    return childArray.size();
}


char MyList::getAtom() const
{
    /*
     * Функция возвращает значение атома
    */

    return atom;
}


bool MyList::compareList(MyList *firstList, MyList *secondList, size_t depth)
{
    /*
     * Функция сравнения двух списков.
     * Принимает на вход два списка, глубину рекурсии для отладки и
     * возвращает true, если списки идентичны, и false в ином случае.
     *
     * Сначала сравниваются размеры списков, затем функция итеративно проходит по
     * вложенным спискам. Если оба списка - атомы, тогда всё нормально. Если оба списка -
     * вложенные списки - функция вызывается рекурсивно для вложенных списков. Если элементы различны -
     * списки неидентичны.
    */

    std::string dbgStr = "";
    for(size_t i = 0; i < depth; ++i)
        dbgStr += " ";

    qDebug() << dbgStr.c_str() << "Сравнение списков";

    if (firstList->size() != secondList->size()) {
        qDebug() << dbgStr.c_str() << "Списки различной длины";
        return false;
    }

    for (size_t i = 0; i < firstList->size(); ++i) {
        if (firstList->childArray[i]->isAtom && secondList->childArray[i]->isAtom) {
            qDebug() << dbgStr.c_str() << "Сравниваются элементы:" <<
                        firstList->childArray[i]->getAtom() << "и" << secondList->childArray[i]->getAtom();
        }
        else if (!firstList->childArray[i]->isAtom && !secondList->childArray[i]->isAtom) {
            qDebug() << dbgStr.c_str() << "Заход во внутренний список";

            if (compareList(firstList->childArray[i], secondList->childArray[i],
                            depth + 1)) {
                qDebug() << dbgStr.c_str() << "Внутренние списки идентичны";
            }
            else {
                qDebug() << dbgStr.c_str() << "Внутренние списки различны";
                return false;
            }
        }
        else {
            qDebug() << dbgStr.c_str() << "Различные элементы в списках";
            return false;
        }
    }
    qDebug() << dbgStr.c_str() << "Списки идентичны.";
    return true;
}
