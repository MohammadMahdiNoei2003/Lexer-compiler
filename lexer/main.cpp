#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <unordered_set>

using namespace std;

struct Token {
    string type;
    string value;
};

unordered_set<string> keywords = {"if", "while", "for", "return", "int", "float", "else", "break", "continue"};

bool isKeyword(const string& token) {
    return keywords.find(token) != keywords.end();
}

vector<Token> lex(string input) {
    vector<Token> tokens;
    string state = "Q0";
    string token;

    for (char ch: input) {
        if (state == "Q0") {
            if (isalpha(ch) or ch == '_') {
                token += ch;
                state = "Q1";
            } else if (isspace(ch)) {
                tokens.push_back({ "WHITESPACE", string(1, ch) });
            } else if (ch == '+' or ch == '-' or ch == '*' or ch == '/' or ch == '=') {
                tokens.push_back({ "OPERATOR", string(1, ch) });
            } else if (ch == ',' or ch == ';' or ch == '(' or ch == ')') {
                tokens.push_back({ "PUNCTUATION", string(1, ch) });
            } else {
                cout << "Invalid character: " << ch << endl;
            }
        } else if (state == "Q1") {
            if (isalnum(ch) or ch == '_') {
                token += ch;
            } else {
                if (isKeyword(token)) {
                    tokens.push_back({ "KEYWORD", token });
                } else {
                    tokens.push_back({ "IDENTIFIER", token });
                }
                token = "";
                state = "Q0";

                if (ch == '+' or ch == '-' or ch == '*' or ch == '/' or ch == '=') {
                    tokens.push_back({ "OPERATOR", string(1, ch) });
                } else if (ch == ',' or ch == ';' or ch == '(' or ch == ')') {
                    tokens.push_back({ "PUNCTUATION", string(1, ch) });
                } else if (isspace(ch)) {
                    tokens.push_back({ "WHITESPACE", string(1, ch)});
                } else {
                    cout << "Invalid character: " << ch << endl;
                }
            }
        }
    }

    if (!token.empty()) {
        if (isKeyword(token)) {
            tokens.push_back({ "KEYWORD", token});
        } else {
            tokens.push_back({ "IDENTIFIER", token});
        }
    }

    return tokens;
}

int main() {
    string input = "if (x + y) while int a = 10;";

    vector<Token> tokens = lex(input);

    for (const auto& token: tokens) {
        cout << "Token Type: " << token.type << ", Value: \"" << token.value << "\"" << endl;
    }

    return 0;
}