#ifndef MYSTACK_H
#define MYSTACK_H

#define QT_NO_DEBUG_OUTPUT

#include <QObject>
#include <string>
#include <QDebug>
#include <memory>


//перечисления для приоритета операций
enum class optype {power = 3, multiply = 2, minus = 1, plus = 1, null = 0};

//Элемент стека, состоящий из выражения и приоритета этого выражения
typedef std::pair<std::string, optype> Data;


class MyStack : public QObject
{
    /*
     * Класс-реализация стека, для перевода выражения из
     * постфиксной формы в инфиксную.
    */

    Q_OBJECT

public:

    struct Node{
        typedef std::shared_ptr<Node> NodeP;
        Data elem;
        NodeP nextNode;
    };

    explicit MyStack(QObject* parent = nullptr);
    ~MyStack() = default;

    //Запрет конструктора копирования и оператора присваивания
    MyStack& operator=(const MyStack& list) = delete;
    MyStack(const MyStack& list) = delete;

public slots:
    //Стандартные методы для работы со стеком
    void pop();
    void push(const Data elem);
    bool isEmpty() const;
    Data top() const;
    size_t size() const;

private:
    Node::NodeP topElem;
    size_t sizeStack;
};

#endif // MYSTACK_H
