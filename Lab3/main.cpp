#include <iostream>
using namespace std;
#include <fstream>
#include <sstream>
#include "Token.h"
#include "Parser.h"
#include "Scanner.h"
#include "Databas.h"
#include "Interpreter.h"
#include "Databas.h"
#include <vector>

string fileToString(const string& filename) {
    ifstream file(filename);

    stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}


int main(int argc, char* argv[]) {
    Datalog datalog;
    Databas database;

    string fileText = fileToString(argv[1]);

    Scanner s(fileText);
    vector<Token> tokenList;
    bool lastComment = false;

    Token t = s.scanToken();
    if (t.getType() == COMMENT) {
        lastComment = true;
    }
    while (t.getType() != END) {

        tokenList.push_back(t);
        if (lastComment) {
            tokenList.pop_back();
            lastComment = false;
        }
        //cout << t.toString() << endl;
        t = s.scanToken();
        if (t.getType() == COMMENT) {
            lastComment = true;
        }

    }
    tokenList.push_back(t);
    // cout << t.toString() << endl;
    //  for (int j = 0; j < tokenList.size(); j++) {
    //      cout << (tokenList.at(j)).toString() << endl;
    //  }

    Parser p = Parser(tokenList);
    p.datalogProgram();
    cout << "Success!" << endl;
    p.getDatalog().printSchemes();
    p.getDatalog().printFacts();
    p.getDatalog().printRules();
    p.getDatalog().printQueries();
    p.getDatalog().printDomains();

    Databas db;
    db.setNames(p.getDatalog());
    db.setFacts(p.getDatalog());
    db.printRelations();

    Interpreter interpreter(db, datalog);
    interpreter.evaluateQueries();

}
