#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>

template <typename T>
class LinkedList {
public:
    struct Node {
        T* data;
        Node* next;

        Node(T* data, Node* next = nullptr) : data(data), next(next) {}
    };

    Node* head;
    Node* tail;
    size_t size;

    LinkedList() : head(nullptr), tail(nullptr), size(0) {}

    ~LinkedList() {
        clear();
    }

    void add(T* element) {
        Node* newNode = new Node(element);
        if (tail) {
            tail->next = newNode;
        } else {
            head = newNode;
        }
        tail = newNode;
        ++size;
    }

    bool remove(T* element) {
        Node* current = head;
        Node* previous = nullptr;

        while (current) {
            if (current->data == element) {
                if (previous) {
                    previous->next = current->next;
                } else {
                    head = current->next;
                }

                if (current == tail) {
                    tail = previous;
                }

                delete current;
                --size;
                return true;
            }

            previous = current;
            current = current->next;
        }

        return false;
    }

    void clear() {
        Node* current = head;
        while (current) {
            Node* toDelete = current;
            current = current->next;
            delete toDelete;
        }

        head = nullptr;
        tail = nullptr;
        size = 0;
    }

    bool isEmpty() const {
        return size == 0;
    }
};

#endif // LINKEDLIST_H