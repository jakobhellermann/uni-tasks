#include "Stack.hpp"

#include <stdexcept>

Stack newStack() {
    return Stack{.top = nullptr};
}

void push(Stack& stack, std::string value) {
    StackElement* newElement = new StackElement{.name = value, .next = stack.top};
    stack.top = newElement;
}

std::string pop(Stack& stack) {
    if (!stack.top) throw std::runtime_error("cannot pop from empty stack");

    StackElement* top = stack.top;
    std::string value = std::move(stack.top->name);

    stack.top = stack.top->next;

    delete top;
    return value;
}

size_t size(Stack& stack) {
    std::size_t size = 0;
    for (StackElement* current = stack.top; current != nullptr; current = current->next) {
        size++;
    }

    return size;
}

bool isEmpty(Stack& stack) {
    return stack.top == nullptr;
}
void deleteStack(Stack& stack) {
    StackElement* current = stack.top;
    while (current != nullptr) {
        StackElement* next = current->next;
        delete current;
        current = next;
    }
}