#include <string>

struct StackElement {
    std::string name;
    StackElement* next;
};

struct Stack {
    StackElement* top;
};

Stack newStack();

void push(Stack& stack, std::string element);
std::string pop(Stack& stack);

size_t size(Stack& stack);
bool isEmpty(Stack& stack);
void deleteStack(Stack& stack);