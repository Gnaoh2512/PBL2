#ifndef SORTEDLINKLIST_H
#define SORTEDLINKLIST_H

#include <iostream>

template <typename T>
class SortedLinkedList {

public:
    struct Node {
        T data;
        Node* next;
        Node(const T& data) : data(data), next(nullptr) {}
    };

    Node* head;
    int size;
    
    SortedLinkedList() : head(nullptr), size(0) {}

    ~SortedLinkedList() {
        Node* current = head;
        while (current) {
            Node* toDelete = current;
            current = current->next;
            delete toDelete;
        }
    }

    void add(const T& item) {
        Node* newNode = new Node(item);
        if (!head || head->data >= item) {
            newNode->next = head;
            head = newNode;
        } else {
            Node* current = head;
            while (current->next && current->next->data < item) {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
        }
        size++;
    }

    bool search(const T& item) const {
        Node* current = head;
        while (current) {
            if (current->data == item) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    int getSize() const {
        return size;
    }

    void display() const {
        Node* current = head;
        while (current) {
            std::cout << current->data << " -> ";
            current = current->next;
        }
        std::cout << "nullptr" << std::endl;
    }
    
};

#endif // SORTEDLINKLIST_H