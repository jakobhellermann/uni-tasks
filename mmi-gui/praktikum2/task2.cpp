#include <iostream>
#include <string>

using namespace std;

bool caesarEncrypt(std::string& str, char key) {
    // check validity
    for (size_t i = 0; i < str.size(); i++) {
        char c = str[i];
        if (c < 'A' || c > 'Z') return false;
    }
    if (key < 'A' || key > 'Z') return false;

    int keyIndex = key - 'A';

    // do transformation
    for (size_t i = 0; i < str.size(); i++) {
        int letterIndex = str[i] - 'A';
        char replacementNum = (letterIndex + keyIndex) % 26;
        str[i] = 'A' + replacementNum;
    }
    return true;
}

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

TEST_CASE("noop") {
    string str = "MAINCPPERRORCAESARENCRYPTWASNOTDECLAREDINTHISSCOPE";
    CHECK(caesarEncrypt(str, 'A'));
    CHECK(str == "MAINCPPERRORCAESARENCRYPTWASNOTDECLAREDINTHISSCOPE");
}

TEST_CASE("rotate by C") {
    string str = "MAINCPPERRORCAESARENCRYPTWASNOTDECLAREDINTHISSCOPE";
    CHECK(caesarEncrypt(str, 'C'));
    CHECK(str == "OCKPERRGTTQTECGUCTGPETARVYCUPQVFGENCTGFKPVJKUUEQRG");
}

TEST_CASE("disallow non-alphabet string") {
    string str = "ASDFa";
    CHECK(!caesarEncrypt(str, 'C'));

    CHECK(str == "ASDFa");
}

TEST_CASE("disallow non-alphabet char") {
    string str = "OK";
    CHECK(!caesarEncrypt(str, 'c'));
}
