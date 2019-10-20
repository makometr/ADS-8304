#include "queue.h"
#include <iostream>


    queue::queue() {
    tail = nullptr;
    head = nullptr;
}

void queue::push(int v) {

    el* n = new el(v);


    if(tail == nullptr) {
        tail = n;
        head = tail;
    }
    else {
        head->next = n;
        head = head->next;
        tail->next = head;
    }

    size++;
}

queue::el queue::pop() {

    if (head == tail) {
        el tmp = *tail;
        delete(tail);

        tail = nullptr;
        head = tail;

        size--;

        return tmp;
    }
    else {
        el last_elem = *head;
        el* tmp_head = head;

        head = tail;

        while (head->next != tmp_head) {
            head = head->next;
        }

        delete(tmp_head);

        head->next = nullptr;

        size--;

        return last_elem;
    }
}

int queue::getSize() {
    return size;
}