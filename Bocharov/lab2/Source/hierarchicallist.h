#ifndef HIERARCHICALLIST_H
#define HIERARCHICALLIST_H

#include <memory>
#include <iostream>


class HierarchicalList
{
public:
    //Умный укаазатель на список для избежания утечек памяти
    typedef std::shared_ptr<HierarchicalList> ListPointer;

    explicit HierarchicalList();
    ~HierarchicalList();

    //Функции для доступа к данным, head - указатель на вложенные списки, tail - на следующие
    ListPointer getHead() const;
    ListPointer getTail() const;
    bool isNull() const;
    bool isAtom() const;
    char getAtom() const;

    //static-методы можно вызывать как обычные функции, не создавая объект класса
    static bool buildList(ListPointer& list, const std::string& str);

    //Перегрузка оператора cout для печати списка, и функция рекурсивной печати следующих списков
    friend std::ostream& operator<< (std::ostream& out, const ListPointer& list);
    void print_seq(std::ostream& out) const;

    //Функция замены одного элемента на другой
    static void swapElements(ListPointer list, const char oldElem, const char newElem);

private:
    //Функция проверки входной строки на корректность
    static bool isCorrectStr(const std::string& str);

    //функции рекурсивного чтения списка
    static void readData(ListPointer& list, const char prev, std::string::const_iterator& it,
                         const std::string::const_iterator& end);
    static void readSeq(ListPointer& list, std::string::const_iterator& it,
                        const std::string::const_iterator& end);

    //Функция конструирования непустого списка
    static ListPointer cons(ListPointer& head, ListPointer& tail);

    //превращает объект класса в атом(список с данными)
    void createAtom(const char ch);


private:
    //Флаг для определения, является ли список - атомом
    bool flag;

        //указатели на вложенный и следующий список
    ListPointer nestedList;
    ListPointer nextList;
    //данные
        char atom;
    
};

#endif // HIERARCHICALLIST_H

