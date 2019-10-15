#ifndef MYLIST_H
#define MYLIST_H

#include <QObject>
#include <QDebug>
#include <vector>
#include <string>
#include <iostream>
#include <memory>
#include <list>

class MyList : public QObject
{

    /*
     * Класс для работы с иерархическими списками
    */
    Q_OBJECT
public:
    typedef std::shared_ptr<MyList> MyListP;

    explicit MyList(QObject *parent = nullptr);
    ~MyList();

    MyList& operator=(const MyList& list) = delete;
    MyList(const MyList& list) = delete;

    MyListP getHead() const;
    MyListP getTail() const;
    bool isNull() const;
    bool getIsAtom() const;
    char getAtom() const;

    //void create_new_list(MyListP inp_list, std::list<char>& new_list);
    static bool buildList(MyListP& list, const std::string& str);
    friend QDebug operator<< (QDebug out, const MyListP list);

private:
    static bool checkStr(const std::string& str);
    static void readData(MyListP& list, const char prev, std::string::const_iterator& it,
                         const std::string::const_iterator& end);
    static void readSeq(MyListP& list, std::string::const_iterator& it,
                        const std::string::const_iterator& end);
    static MyListP cons(MyListP& head, MyListP& tail);
    void createAtom(const char ch);
    void print_seq(QDebug& out) const;

private:
    bool isAtom;
    MyListP head;
    MyListP tail;
    char atom;
};

#endif // MYLIST_H
