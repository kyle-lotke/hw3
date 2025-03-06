#include <iostream>
#include "stack.h"

void testStack() {
    Stack<int> s;

    // Test empty stack
    std::cout << "Initial stack empty: " << (s.empty() ? "PASS" : "FAIL") << std::endl;

    // Test push
    s.push(10);
    s.push(20);
    s.push(30);
    std::cout << "Stack size after 3 pushes: " << (s.size() == 3 ? "PASS" : "FAIL") << std::endl;
    std::cout << "Top element (should be 30): " << (s.top() == 30 ? "PASS" : "FAIL") << std::endl;

    // Test pop
    s.pop();
    std::cout << "Stack size after 1 pop: " << (s.size() == 2 ? "PASS" : "FAIL") << std::endl;
    std::cout << "Top element after pop (should be 20): " << (s.top() == 20 ? "PASS" : "FAIL") << std::endl;

    // Test popping all elements
    s.pop();
    s.pop();
    std::cout << "Stack empty after popping all elements: " << (s.empty() ? "PASS" : "FAIL") << std::endl;

    // Test popping from an empty stack (should throw exception)
    try {
        s.pop();
        std::cout << "Pop on empty stack: FAIL (no exception thrown)" << std::endl;
    } catch (const std::underflow_error&) {
        std::cout << "Pop on empty stack: PASS (exception caught)" << std::endl;
    }

    // Test top() on empty stack (should throw exception)
    try {
        s.top();
        std::cout << "Top on empty stack: FAIL (no exception thrown)" << std::endl;
    } catch (const std::underflow_error&) {
        std::cout << "Top on empty stack: PASS (exception caught)" << std::endl;
    }
}

int main() {
    testStack();
    return 0;
}
