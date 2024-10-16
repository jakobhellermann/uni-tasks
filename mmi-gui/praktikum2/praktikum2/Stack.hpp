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
std::string pop(Stack stack);

int size(Stack&);
bool isEmpty(Stack&);
void deleteStack(Stack&);