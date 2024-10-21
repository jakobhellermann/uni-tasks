
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

    // single push
    push(stack, "item");
    CHECK(!isEmpty(stack));
    CHECK(size(stack) == 1);

    // single pop
    auto popped = pop(stack);
    CHECK(isEmpty(stack));
    CHECK(size(stack) == 0);
    CHECK(popped == "item");

    // no pop empty
    CHECK_THROWS(pop(stack));
    CHECK_THROWS(pop(stack));

    // many
    int n = 10;
    for (int i = 0; i < n; i++)
        push(stack, "item");

    pop(stack);
    pop(stack);
    CHECK(size(stack) == n - 2);

    deleteStack(stack);

    CHECK(isEmpty(stack));
    CHECK(size(stack) == 0);
}