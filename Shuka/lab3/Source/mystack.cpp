#include "mystack.h"

MyStack::MyStack(QObject* parent) : QObject(parent)
{
    topElem = nullptr;
    sizeStack = 0;
}


void MyStack::pop()
{
    /*
     * Удаление верхнего элемента из стека
    */
    if (topElem != nullptr) {
        Node::NodeP oldTopElem = topElem;
        topElem = oldTopElem->nextNode;
        sizeStack -= 1;
        oldTopElem->nextNode = nullptr;
    }
    else {
        qDebug() << "Error: stack is empty";
    }
}


void MyStack::push(const Data elem)
{
    /*
     * Добавление элемента в стек
    */

    Node::NodeP tmp = topElem;
    topElem = Node::NodeP(new Node);
    topElem->elem = elem;
    sizeStack += 1;
    topElem->nextNode = tmp;
}


bool MyStack::isEmpty() const
{
    /*
     * Проверка стека на пустоту
    */

    return topElem == nullptr;
}


Data MyStack::top() const
{
    /*
     * Доступ к верхнему элементу стека
    */
    if (topElem != nullptr) {
        return topElem->elem;
    }
    else {
        qDebug() << "Error: stack is empty!";
        return Data("", optype::null);
    }
}


size_t MyStack::size() const
{
    /*
     * Получение размера стека
    */

    return sizeStack;
}

