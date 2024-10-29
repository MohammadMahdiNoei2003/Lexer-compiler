    #include <iostream>
    #include <string>
    #include <cctype>
    #include <vector>
    #include <unordered_map>
    #include <unordered_set>

    using namespace std;

    enum TokenType {
        IDENTIFIER,
        INTEGER,
        FLOAT,
        OPERATOR_PLUS,
        OPERATOR_EQUALS,
        PAREN_OPEN,
        PAREN_CLOSE,
        KEYWORD_IF,
        KEYWORD_FOR,
        WHITESPACE,
        UNKNOWN,
        ERROR
    };

    struct Token {
        TokenType type;
        string value;
    };

    class DFA {
        unordered_map<int, unordered_map<char, int>> transitionTable;
        unordered_set<int> acceptingStates;
        unordered_map<int, TokenType> tokenTypes;
        int startState;

    public:
        DFA(int start, unordered_set<int> accepting,
            unordered_map<int, unordered_map<char, int>> transitions,
            unordered_map<int, TokenType> types)
            : startState(start), acceptingStates(accepting), 
            transitionTable(transitions), tokenTypes(types) {}

        Token run(const string& input) {
            int currentState = startState;
            string tokenValue;

            for (char ch : input) {
                if (transitionTable[currentState].count(ch) == 0) {
                    return {ERROR, tokenValue + ch};
                }
                currentState = transitionTable[currentState][ch];
                tokenValue += ch;
            }

            if (acceptingStates.count(currentState)) {
                return {tokenTypes[currentState], tokenValue};
            }

            return {ERROR, tokenValue};
        } 
    };

    vector<Token> lexer(const string& input, DFA& dfa) {
        vector<Token> tokens;
        string buffer;

        for (char ch : input) {
            if (isspace(ch)) {
                if (!buffer.empty()) {
                    Token token = dfa.run(buffer);
                    if (token.type == ERROR) {
                        cerr << "Lexical error: Invalid identifier. '" << token.value << "'\n";
                    } else {
                        tokens.push_back(token);
                    }
                    buffer.clear();
                }
                tokens.push_back({WHITESPACE, " "});
            } else if (ch == '(' || ch == ')' || ch == '+' || ch == '=') {
                if (!buffer.empty()) {
                    Token token = dfa.run(buffer);
                    if (token.type == ERROR) {
                        cerr << "Lexical error: Invalid identifier. '" << token.value << "'\n";
                    } else {
                        tokens.push_back(token);
                    }
                    buffer.clear();
                }
                buffer += ch;
                Token token = dfa.run(buffer);
                tokens.push_back(token);
                buffer.clear();
            } else {
                buffer += ch;
            }
        }

        if (!buffer.empty()) {
            Token token = dfa.run(buffer);
            if (token.type == ERROR) {
                cerr << "Lexical error: Invalid identifier. '" << token.value << "'\n";
            } else {
                tokens.push_back(token);
            }
        }

        return tokens;
    }

    void printTokens(const vector<Token>& tokens) {
        for (const Token& token : tokens) {
            cout << "Token: ";
            switch (token.type) {
                case IDENTIFIER: cout << "IDENTIFIER"; break;
                case INTEGER: cout << "INTEGER"; break;
                case FLOAT: cout << "FLOAT"; break;
                case OPERATOR_PLUS: cout << "OPERATOR_PLUS"; break;
                case OPERATOR_EQUALS: cout << "OPERATOR_EQUALS"; break;
                case PAREN_OPEN: cout << "PAREN_OPEN"; break;
                case PAREN_CLOSE: cout << "PAREN_CLOSE"; break;
                case KEYWORD_IF: cout << "KEYWORD_IF"; break;
                case KEYWORD_FOR: cout << "KEYWORD_FOR"; break;
                case WHITESPACE: cout << "WHITESPACE"; break;
                default: cout << "UNKNOWN"; break;
            }
            cout << ", Value: " << token.value << endl;
        }
    }