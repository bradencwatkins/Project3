#pragma once

using namespace std;
#include <sstream>
#include <string>
#include <iostream>
#include "Token.h"
#include <cctype>


class Scanner {
private:
    string input;
    int line = 1;
    int pos = 0;

public:
    Scanner(const string& input) : input(input) {}

    Token scanToken() {
        TokenType type;
        string value;


        while (pos < input.size() && isspace(input[pos])) {
            if (input[pos] == '\n') {
                line++;
            }
            pos++;
        }

        if (pos >= input.size()) {
            return Token(END, "", line);
        }
        if (input[pos] == ',') {
            pos++;
            return Token(COMMA, ",", line);
        }
        if (input[pos] == '.') {
            pos++;
            return Token(PERIOD, ".", line);
        }
        if (input[pos] == '?') {
            pos++;
            return Token(Q_MARK, "?", line);
        }
        if (input[pos] == '(') {
            pos++;
            return Token(LEFT_PAREN, "(", line);
        }
        if (input[pos] == ')') {
            pos++;
            return Token(RIGHT_PAREN, ")", line);
        }
        if (input[pos] == ':') {
            pos++;
            if (input[pos] == '-') {
                pos++;
                return Token(COLON_DASH, ":-", line);
            }
            return Token(COLON, ":", line);
        }
        if (input[pos] == '*') {
            pos++;
            return Token(MULTIPLY, "*", line);
        }
        if (input[pos] == '+') {
            pos++;
            return Token(ADD, "+", line);
        }

        if (input.substr(pos, 7) == "Schemes") {
            pos += 7;
            if (input[pos] == ' ' || input[pos] == '\n' || input[pos] == ':' || !isalpha(input[pos]) || !isalnum(input[pos])) {
                return Token(SCHEMES, "Schemes", line);
            }
            pos -= 7;
            while (isalpha(input[pos]) || isalnum(input[pos])) {
                value += input[pos];
                pos++;
            }
            return Token(ID, value, line);
        }

        if (input.substr(pos, 5) == "Facts") {
            pos += 5;
            if(input[pos] != ' ' && input[pos] != '\n' && input[pos] != ':') {
                pos -= 5;
                while (isalpha(input[pos]) || isalnum(input[pos])) {
                    value += input[pos];
                    pos++;
                }
                return Token(ID, value, line);
            }
            return Token(FACTS, "Facts", line);
        }

        if (input.substr(pos, 5) == "Rules") {
            pos += 5;
            if(input[pos] != ' ' && input[pos] != '\n' && input[pos] != ':') {
                pos -= 5;
                while (isalpha(input[pos]) || isalnum(input[pos])) {
                    value += input[pos];
                    pos++;
                }
                return Token(ID, value, line);
            }
            return Token(RULES, "Rules", line);
        }

        if (input.substr(pos, 7) == "Queries") {
            pos += 7;
            if(input[pos] != ' ' && input[pos] != '\n' && input[pos] != ':') {
                pos -= 7;
                while (isalpha(input[pos]) || isalnum(input[pos])) {
                    value += input[pos];
                    pos++;
                }
                return Token(ID, value, line);
            }
            return Token(QUERIES, "Queries", line);
        }

        if (isalpha(input[pos])) {
            value += input[pos];
            pos++;
            while (isalpha(input[pos]) || isalnum(input[pos])) {
                value += input[pos];
                pos++;
            }
            return Token(ID, value, line);
        }

        if (input[pos] == '\'') {
            value += input[pos];
            pos++;
            int linSubtracter = 0;
            while (pos < input.size() && input[pos] != '\'') {
                if (input[pos] == '\n') {
                    line++;
                    linSubtracter++;
                }
                if (pos + 1 < input.size() && input[pos] == '\'' && input[pos+1] == '\'') {
                    value += input[pos];
                    pos++;
                    value += input[pos];
                    pos++;
                } else {
                    value += input[pos];
                    pos++;
                }
            }
            if (input[pos] == '\'') {
                value += input[pos];
                pos++;
                return {STRING, value, line - linSubtracter};
            }
            return Token(UNDEFINED, value, line - linSubtracter);
        }

        if (input[pos] == '#') {
            value += input[pos];
            pos++;
            while (pos < input.size() && input[pos+1] != '\n') {
                value += input[pos];
                pos++;
            }
            pos++;
            value += input[pos-1];
            // if (input[pos] == '\n') {
            //     pos++;
            // }

            return Token(COMMENT, value, line);
        }

        value = input[pos];
        Token token(UNDEFINED, value, line);
        pos++;
        return token;
    }


};
