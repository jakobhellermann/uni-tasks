#include "Stack.hpp"

#include <exception>

Stack newStack() {
    return Stack{.top = nullptr};
}

void push(Stack& stack, std::string value) {
    StackElement* newElement = new StackElement{.name = value, .next = nullptr};

    if (stack.top) {
        stack.top->next = newElement;
    } else {
        stack.top = newElement;
    }
}

std::string pop(Stack& stack) {
    if (!stack.top) throw runtime_error("cannot pop from empty stack");
}

int size(Stack& stack) {
    std::size_t size = 0;
    for (StackElement* current = stack.top; current != nullptr; current = current->next) {
        size++;
    }

    return size;
}

bool isEmpty(Stack& stack) {
    return stack.top == nullptr;
}
void deleteStack(Stack&);