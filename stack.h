#ifndef STACK_H
#define STACK_H

#include <vector>
#include <stdexcept>

// Use inheritance from std::vector (choose public/private) as appropriate
template <typename T>
class Stack : private std::vector<T>
{
public:
    Stack();
    ~Stack();
    bool empty() const;
    size_t size() const;
    void push(const T& item);
    void pop();  // throws std::underflow_error if empty
    const T& top() const; // throws std::underflow_error if empty
    // Add other members only if necessary

    //buffer is inherted privtely, which is the data
    // size is inherted privarly, which keeps track of length

};


template <typename T>
Stack<T>::Stack() : std::vector<T>() {}

template <typename T>
Stack<T>::~Stack() {}

template <typename T>
void Stack<T>::push(const T& item) {
    this->push_back(item); // call vector function
}

template <typename T>
void Stack<T>::pop() {
    if (this->empty()) {
        throw std::underflow_error("Stack is empty");
    }
    this->pop_back(); // double check
}

template <typename T>
size_t Stack<T>::size() const {
    return std::vector<T>::size(); // same name so need to scope it
}

template <typename T>
bool Stack<T>::empty() const {
    return this->size() == 0; // call the stack size() which calls the vector size()
}

template <typename T>
const T& Stack<T>::top() const {
    if (this->empty()) {
        throw std::underflow_error("Stack is empty");
    }
    return this->back();
}


#endif