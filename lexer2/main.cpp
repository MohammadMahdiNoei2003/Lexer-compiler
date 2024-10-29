#include <iostream>
#include<vector>
#include <string>

#include "lexer.hpp"

using namespace std;

int main() {
    string input = "if (x = 10 + y) for (z = 20x)";
    vector<Token> tokens = lexer(input);
    printTokens(tokens);

    return 0;
}