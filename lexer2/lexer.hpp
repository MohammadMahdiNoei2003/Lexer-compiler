#include <iostream>
#include <string>
#include <vector>
#include <cctype>

using namespace std;

enum TokenType {
    KEYWORD_IF,
    KEYWORD_FOR,
    IDENTIFIER,
    INTEGER,
    OPERATOR_PLUS,
    OPERATOR_EQUALS,
    PAREN_OPEN,
    PAREN_CLOSE,
    WHITESPACE,
    UNKNOWN,
    ERROR
};

struct Token {
    TokenType type;
    string value;
};

bool isKeyword(const string& str) {
    return str == "if" or str == "for";
}

bool isIdentifierStart(char ch) {
    return isalpha(ch) or ch == '_';
}

bool isIdentifierChar(char ch) {
    return isalnum(ch) or ch == '_';
}

bool isDigit(char ch) {
    return isdigit(ch);
}

vector<Token> lexer(const string& input) {
    vector<Token> tokens;
    size_t i = 0;

    while (i < input.size()) {
        if (isspace(input[i])) {
            tokens.push_back({ WHITESPACE, "" "" });
            i++;
        }

        if (input[i] == '\t') {
            tokens.push_back({ WHITESPACE, "\t" });
            i++;
        }

        if (input[i] == '\n') {
            tokens.push_back({ WHITESPACE, "\n" });
            i++;
        }

        if (isIdentifierStart(input[i])) {
            size_t start = i;
            while (i < input.size() and isIdentifierChar(input[i])) {
                i++;
            }
            string identifier = input.substr(start, i - start);

            if (isKeyword(identifier)) {
                tokens.push_back({ identifier == "if" ? KEYWORD_IF : KEYWORD_FOR, identifier });
            } else {
                tokens.push_back({ IDENTIFIER, identifier });
            }
        } else if (isDigit(input[i])) {
            size_t start = i;
            while (i < input.size() and isDigit(input[i])) {
                i++;
            }

            if (i < input.size() and (input[i] == '_' or isalpha(input[i]))) {
                while (i < input.size() and isIdentifierChar(input[i])) {
                    i++;
                }
                tokens.push_back({ ERROR, input.substr(start, i - start)});
                cout << "Lexical error: Invalid identifier. '" << input.substr(start, i -start) << "'\n";
            } else {
                tokens.push_back({ INTEGER, input.substr(start, i - start) });
            }
        } else if (input[i] == '+') {
            tokens.push_back({ OPERATOR_PLUS, "+" });
            i++;
        } else if (input[i] == '=') {
            tokens.push_back({ OPERATOR_EQUALS, "=" });
            i++;
        } else if (input[i] == '(') {
            tokens.push_back({ PAREN_OPEN, "(" });
            i++;
        } else if (input[i] == ')') {
            tokens.push_back({ PAREN_CLOSE, ")" });
            i++;
        } else {
            tokens.push_back({ UNKNOWN, string(1, input[i]) });
            i++;
        }
    }

    return tokens;
}

void printTokens(const vector<Token>& tokens) {
    for (const Token& token : tokens) {
        cout << "Token: ";
        switch (token.type) {
            case KEYWORD_IF : cout << "KEYWORD_IF"; break;
            case KEYWORD_FOR: cout << "KEYWORD_FOR"; break;
            case IDENTIFIER: cout << "IDENTIFIER"; break;
            case INTEGER: cout << "INTEGER"; break;
            case OPERATOR_PLUS: cout << "OPERATOR_PLUS"; break;;
            case OPERATOR_EQUALS: cout << "OPERATOR_EQUALS"; break;
            case PAREN_OPEN: cout << "PAREN_OPEN"; break;
            case PAREN_CLOSE: cout << "PAREN_CLOSE"; break;
            case WHITESPACE: cout << "WHITESPACE"; break;
            default: cout << "UNKNOWN"; break;
        }
        cout << ", Value: " << token.value << endl;
    }
}
