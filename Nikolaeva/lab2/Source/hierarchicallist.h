#ifndef HIERARCHICALLIST_H
#define HIERARCHICALLIST_H

#define QT_NO_DEBUG_OUTPUT

#include <memory>
#include <iostream>
#include <QObject>
#include <QDebug>


class HierarchicalList : public QObject
{
    Q_OBJECT

public:
    //Умный укаазатель на список для избежания утечек памяти
    typedef std::shared_ptr<HierarchicalList> ListPointer;

    explicit HierarchicalList(QObject *parent = nullptr);
    ~HierarchicalList();

    HierarchicalList(const HierarchicalList&) = delete;
    HierarchicalList& operator=(const HierarchicalList&) = delete;

    //преобразование списка в строку
    std::string toStdString() const;

    //перегрузка оператора вывода
    friend QDebug operator<< (QDebug out, ListPointer list);

public slots:
    //Функции для доступа к данным, head - указатель на вложенные списки, tail - на следующие
    ListPointer getHead() const;
    ListPointer getTail() const;
    bool isNull() const;
    bool isAtom() const;
    char getAtom() const;

    //Функция для разворота списка
    static void reverseList(ListPointer& list, size_t depth = 1);

    //Функция для создания списка из строки
    static bool buildList(HierarchicalList::ListPointer& list, const std::string& str);

    //Функция рекурсивной печати следующих списков
    void print_seq(QDebug& out) const;

private slots:
    //преобразование следующих списков в строку
    void tailToStdTring(std::string& list);

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
    ListPointer head;
    ListPointer tail;
    //данные
    char atom;
};

//Функция для проверки строки на корректность
bool isCorrectStr(const std::string& str);


#endif // HIERARCHICALLIST_H
