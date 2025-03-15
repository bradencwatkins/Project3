#pragma once
#include <string>
#include <sstream>


using namespace std;


enum TokenType {
    COMMA, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN, COLON, COLON_DASH, MULTIPLY, ADD, SCHEMES, FACTS,
    RULES, QUERIES, ID, STRING, COMMENT, UNDEFINED, END
 };


class Token {
private:
    TokenType type;
    string value;
    int line;




public:
    Token(TokenType type, string value, int line) : type(type), value(value), line(line) {}


    TokenType getType() const {
        return type;
    }

    int getLine() const {
        return line;
    }

    string getValue() const {
        return value;
    }


    string typeName(TokenType type) const {
        switch (type) {
            case COMMA: return "COMMA";
            case Q_MARK: return "Q_MARK";
            case MULTIPLY: return "MULTIPLY";
            case ADD: return "ADD";
            case SCHEMES: return "SCHEMES";
            case RULES: return "RULES";
            case QUERIES: return "QUERIES";
            case COMMENT: return "COMMENT";
            case UNDEFINED: return "UNDEFINED";
            case FACTS: return "FACTS";
            case COLON: return "COLON";
            case COLON_DASH: return "COLON_DASH";
            case ID: return "ID";
            case LEFT_PAREN: return "LEFT_PAREN";
            case RIGHT_PAREN: return "RIGHT_PAREN";
            case PERIOD: return "PERIOD";
            case STRING: return "STRING";
            case END: return "END";
            default: return "UNDEFINED";
        }
    }




    string toString() const {
        stringstream out;
        out << "(" << typeName(type) << "," << "\"" << value << "\"" << "," << line << ")";
        return out.str();
    }
};
