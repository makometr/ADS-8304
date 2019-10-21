//
// Created by Dan on 20.10.2019.
//

#ifndef ADS_LR2_MYLIST_H
#define ADS_LR2_MYLIST_H


#include <vector>
#include <string>
#include <iostream>
#include <memory>
#include <list>

class MyList{

public:
    typedef std::shared_ptr<MyList> MyListP;

    explicit MyList();
    ~MyList();

    MyList& operator=(const MyList& list) = delete;
    MyList(const MyList& list) = delete;

    MyListP getHead() const;
    MyListP getTail() const;
    bool isNull() const;
    bool getIsAtom() const;
    char getAtom() const;

    friend std::ostream& operator<< (std::ostream& out, const MyListP list);
    static bool buildList(MyListP& list, const std::string& str);

private:
    static bool checkStr(const std::string& str);
    static void readData(MyListP& list, const char prev, std::string::const_iterator& it,
                         const std::string::const_iterator& end);
    static void readSeq(MyListP& list, std::string::const_iterator& it,
                        const std::string::const_iterator& end);
    static MyListP cons(MyListP& head, MyListP& tail);
    void createAtom(const char ch);
    void print_seq(std::ostream& out) const;

private:
    bool isAtom;
    MyListP head;
    MyListP tail;
    char atom;
};

#endif //ADS_LR2_MYLIST_H
