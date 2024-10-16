
#include <iostream>
#include <string>

#include "Stack.hpp"

using namespace std;

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

TEST_CASE("stack operations") {
    Stack stack = newStack();
    CHECK(isEmpty(stack));
    CHECK(size(stack) == 0);

    push(stack, "item");
    CHECK(!isEmpty(stack));
    CHECK(size(stack) == 1);

    auto popped = pop(stack);
    CHECK(isEmpty(stack));
    CHECK(size(stack) == 0);
}