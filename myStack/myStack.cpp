#include "myStack.h"
#include<iostream>

template<typename T>
myStack::Stack<T>::Stack(const Stack<T> &other) {
    Node<T> *temp = other.head;

    while (temp != nullptr) {
        push(temp->data);
        temp = temp->next;
    }
}

template<typename T>
myStack::Stack<T>::Stack(Stack<T> &&other) noexcept {
    swap(*this, other);
    other.stack_ = nullptr;
}

template<typename T>
myStack::Stack<T> &myStack::Stack<T>::operator=(const Stack &other) {
    if (this != &other) {
        clear();

        Node<T> *temp = other.head;
        while (temp != nullptr) {
            push(temp->data);
            temp = temp->next;
        }
    }

    return *this;
}

template<typename T>
myStack::Stack<T> &myStack::Stack<T>::operator=(Stack &&other) noexcept {
    if (this != &other) {
        clear();

        head = other.head;
        other.head = nullptr;
    }

    return *this;
}

template<typename T>
myStack::Stack<T>::~Stack() {
    clear();
}

template<typename T>
void myStack::Stack<T>::push(const T &value) {
    Node<T> *newNode = new Node<T>(value);

    newNode->next = head;
    head = newNode;
}

template<typename T>
void myStack::Stack<T>::push(T &&value) {
    Node<T> *newNode = new Node<T>(std::move(value));

    newNode->next = head;
    head = newNode;
}

template<typename T>
void myStack::Stack<T>::pop() {
    if (head != nullptr) {
        Node<T> *temp = head;
        head = head->next;
        delete temp;
    }
}

template<typename T>
T myStack::Stack<T>::top() const {
    if (head != nullptr) {
        return head->data;
    } else {
        throw std::out_of_range("Empty stack");
    }
}

template<typename T>
void myStack::Stack<T>::clear() {
    while (head != nullptr) {
        Node<T> *temp = head;
        head = head->next;
        delete temp;
    }
}