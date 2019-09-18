#ifndef MYLIST_H
#define MYLIST_H

#include <QObject>
#include <QDebug>
#include <vector>
#include <string>

class MyList : public QObject
{

    /*
     * Класс для работы с иерархическими списками
    */

    Q_OBJECT
public:
    explicit MyList(QObject *parent = nullptr);
    MyList& operator=(const MyList& list) = delete;
    MyList(const MyList& list) = delete;
    static bool compareList(MyList* firstList, MyList* secondList, size_t depth = 0);
    bool buildList(const std::string& str);
    size_t size() const;
    char getAtom() const;
    friend QDebug& operator<< (QDebug& out, const MyList &list);
    ~MyList();

private:
    bool checkStr(const std::string& str) const;
    void createAtom(const char ch);

private:
    bool isAtom;
    std::vector<MyList *> childArray;
    char atom;

};

#endif // MYLIST_H
