#pragma once
using namespace std;
#include <string>
#include <vector>
#include "Parameter.h"
#include "Predicate.h"
#include "Rule.h"
#include "Datalog.h"
#include "Token.h"



class Parser {
private:
   vector<Token> tokens;
    bool isScheme = true;
    bool isRule = true;
    bool failure = false;
   Datalog datalog;

public:
   Parser(const vector<Token>& tokens) : tokens(tokens) { }


   TokenType tokenType() const {
       return tokens.at(0).getType();
   }


   void advanceToken() {
       tokens.erase(tokens.begin());
   }


   void throwError() {
       cout << "Failure!" << endl;
       cout << "  (" << tokens.at(0).typeName(tokens.at(0).getType()) << ",\"" << tokens.at(0).getValue() << "\"," << tokens.at(0).getLine() << ")" << endl;
       exit(1);
   }

    //function to allow main to access Datalog
    Datalog& getDatalog() {
       return datalog;
   }

   void match(TokenType t) {
       if (tokens.empty()) {
           throwError();
       }

       if (tokenType() == t) {
           advanceToken();
       }
       else {
           throwError();
       }
   }


   void idList() {
       if (tokenType() == COMMA) {
           match(COMMA);
           Parameter newParam(tokens.at(0).getValue(), true);
           if (isScheme) {
               datalog.getLastScheme().addParameter(newParam);
           }
           else if (!isScheme) {
               Parameter newParam(tokens.at(0).getValue(), true);
               datalog.getLastRule().getHead().addParameter(newParam);
           }
           match(ID);
           idList();
       } else {
           // lambda
       }
   }

   void schemeList() {
       if (tokenType() == ID) {
           scheme();
           schemeList();
       }
       else{/*lambda*/}
   }

   void factList() {
       if (tokenType() == ID) {
           fact();
           factList();
       }
       else{/*lambda*/}
   }

   void ruleList() {
       if (tokenType() == ID) {
           rule();
           ruleList();
       }
       else{/*lambda*/}
   }

   void queryList() {
       if (tokenType() == ID) {
           query();
           if (!tokens.empty()) {
               queryList();
           }
       }
       else{/*lambda*/}
   }

   void scheme() {
       if (tokenType() == ID) {
           Predicate newPred(tokens.at(0).getValue());
           datalog.addScheme(newPred);
           match(ID);
           match(LEFT_PAREN);
           Parameter newParam(tokens.at(0).getValue(), true);
           datalog.getLastScheme().addParameter(newParam);
           match(ID);
           idList();
           match(RIGHT_PAREN);
       }
       else {
           throwError();
       }
   }

   void fact() {
       if (tokenType() == ID) {
           Predicate factPred(tokens.at(0).getValue());
           datalog.addFact(factPred);
           match(ID);
           match(LEFT_PAREN);
           Parameter newParam(tokens.at(0).getValue(), true);
           datalog.getLastFact().addParameter(newParam);
           datalog.addDomain(tokens.at(0).getValue());
           match(STRING);
           stringList();
           match(RIGHT_PAREN);
           match(PERIOD);
       }
       else {
           throwError();
       }
   }

   void rule() {
       headPredicate();
       if (tokenType() == COLON_DASH) {
           match(COLON_DASH);
           predicate();
           predicateList();
           match(PERIOD);
       }
       else {
           throwError();
       }
   }

   void query() {
       predicate();
       match(Q_MARK);
   }

   void headPredicate() {
       Predicate head(tokens.at(0).getValue());
       Rule newRule(head);
       datalog.addRule(newRule);
       datalog.getLastRule().addHead(head);
       match(ID);
       match(LEFT_PAREN);
       Parameter newParam(tokens.at(0).getValue(), true);
       datalog.getLastRule().getHead().addParameter(newParam);
       match(ID);
       idList();
       match(RIGHT_PAREN);
   }

   void predicate() {
       if (isRule) {
           Predicate newBody(tokens.at(0).getValue());
           datalog.getLastRule().addBody(newBody);
       }
       else if(!isRule) {
           Predicate newQ(tokens.at(0).getValue());
           datalog.addQuery(newQ);
       }
       match(ID);
       match(LEFT_PAREN);
       parameter();
       parameterList();
       match(RIGHT_PAREN);
   }

   void predicateList() {
       if (tokenType() == COMMA) {
           match(COMMA);
           predicate();
           predicateList();
       }
   }

   void parameterList() {
       if (tokenType() == COMMA) {
           match(COMMA);
           parameter();
           parameterList();
       }
       else {/*lambda*/}
   }

   void stringList() {
       if (tokenType() == COMMA) {
           match(COMMA);
           Parameter newParam(tokens.at(0).getValue(), true);
           datalog.getLastFact().addParameter(newParam);
           datalog.addDomain(tokens.at(0).getValue());
           match(STRING);
           stringList();
       }
       else {/*lambda*/}
   }

   void parameter() {
       if (tokenType() == STRING) {
           if (isRule) {
               Parameter newParam(tokens.at(0).getValue(), false);
               datalog.getLastRule().getLastBody().addParameter(newParam);
           }
           else if (!isRule) {
               Parameter newParam(tokens.at(0).getValue(), false);
               datalog.getLastQuery().addParameter(newParam);
           }
           match(STRING);
       }
       if (tokenType() == ID){
           if (isRule) {
               Parameter newParam(tokens.at(0).getValue(), true);
               datalog.getLastRule().getLastBody().addParameter(newParam);
           }
           else if (!isRule) {
               Parameter newParam(tokens.at(0).getValue(), true);
               datalog.getLastQuery().addParameter(newParam);
           }
           match(ID);
       }
   }

   void datalogProgram() {
           match(SCHEMES);
           match(COLON);
           scheme();
           schemeList();
           match(FACTS);
           match(COLON);
           factList();
           isScheme = false;
           match(RULES);
           match(COLON);
           ruleList();
           isRule = false;
           match(QUERIES);
           match(COLON);
           if (tokens.empty()) {
               throwError();
           }
           query();
           if (!tokens.empty()) {
               queryList();
           }
       if (tokenType() != END) {
           throwError();
       }
   }

};
