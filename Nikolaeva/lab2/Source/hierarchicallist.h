#ifndef HIERARCHICALLIST_H
#define HIERARCHICALLIST_H

#define QT_NO_DEBUG_OUTPUT

#include <memory>
#include <variant>
#include <iostream>
#include <QObject>
#include <QDebug>


class HierarchicalList : public QObject
{
    Q_OBJECT

public:
    typedef std::shared_ptr<HierarchicalList> ListPointer;

    struct Pointers {
        ListPointer head;
        ListPointer tail;

        Pointers () {}
        Pointers (ListPointer head, ListPointer tail) :
            head(head), tail(tail) {}
    };

    HierarchicalList(QObject *parent = nullptr);
    ~HierarchicalList() = default;

    HierarchicalList(const HierarchicalList&) = delete;
    HierarchicalList& operator=(const HierarchicalList&) = delete;

    std::string toStdString() const;

    friend QDebug operator<< (QDebug out, ListPointer list);

public slots:
    ListPointer getHead() const;
    ListPointer getTail() const;
    bool isNull() const;
    bool isAtom() const;
    char getAtom() const;

    static void reverseList(ListPointer& list, size_t depth = 1);

    static bool buildList(HierarchicalList::ListPointer& list, const std::string& str);

    void print_seq(QDebug& out) const;

private slots:
    void tailToStdTring(std::string& list);

    static void readData(ListPointer& list, const char prev, std::string::const_iterator& it,
                         const std::string::const_iterator& end);
    static void readSeq(ListPointer& list, std::string::const_iterator& it,
                        const std::string::const_iterator& end);

    static ListPointer cons(ListPointer& head, ListPointer& tail);

    void createAtom(const char ch);

private:
    bool flagIsAtom;
    std::variant<Pointers, char> pair;
};

bool isCorrectStr(const std::string& str);


#endif // HIERARCHICALLIST_H
