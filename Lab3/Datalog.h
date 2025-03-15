#pragma once
using namespace std;
#include <vector>
#include <string>
#include "Predicate.h"
#include "Rule.h"
#include "Parser.h"
#include <set>
#include "Database.h"

class Datalog {


private:
    vector<Predicate> scheme;
    vector<Predicate> facts;
    vector<Rule> rules;
    vector<Predicate> queries;
    set<string> domains;


public:
    void addScheme(Predicate p) {
        scheme.push_back(p);
    }

    Predicate& getLastScheme() {
        return scheme.back();
    }

    void addFact(Predicate p) {
        facts.push_back(p);
    }

    Predicate& getLastFact() {
        return facts.back();
    }

    void addDomain(string d) {
        domains.insert(d);
    }

    void addRule(Rule r) {
        rules.push_back(r);
    }

    Rule& getLastRule() {
        return rules.back();
    }

    Predicate& getLastQuery() {
        return queries.back();
    }

    void addQuery(Predicate p) {
        queries.push_back(p);
    }

    const vector<Predicate>& getSchemes() const {
        return scheme;
    }

    string getSchemeName(int position) {
        return scheme.at(position).getName();
    }

    vector<string> getSchemeNames() {
        vector<string> names;
        for (const auto& pred : scheme) {
            names.push_back(pred.getName());
        }
        return names;
    }

    //printing the schemes, first predicate, then parameters
    void printSchemes() {
        cout << "Schemes(" << scheme.size() << "):" << endl;
        for (const auto& pred : scheme) {
            cout << "  " << pred.getName() << "(";
            const vector<Parameter>& params = pred.getParameters();
            for (int i = 0; i < params.size(); i++) {
                cout << params.at(i).getValue();
                if (params.size() - 1 != i) {
                    cout << ",";
                }
            }
            cout << ")" << endl;
        }
    }

    void printFacts() {
        cout << "Facts(" << facts.size() << "):" << endl;
        for (const auto& pred : facts) {
            cout << "  " << pred.getName() << "(";
            const vector<Parameter>& params = pred.getParameters();
            for (int i = 0; i < params.size(); i++) {
                cout << params.at(i).getValue();
                if (params.size() - 1 != i) {
                    cout << ",";
                }
            }
            cout << ")." << endl;
        }
    }

    void printRules() {
        cout << "Rules(" << rules.size() << "):" << endl;
        for (auto& rool : rules) {
            cout << "  " << rool.getHead().getName() << "(";
            const vector<Parameter>& headParams = rool.getHead().getParameters();
            for (int k = 0; k < headParams.size(); k++) {
                cout << headParams.at(k).getValue();
                if (headParams.size() - 1 != k) {
                    cout << ",";
                }
            }

            cout << ") :- ";
            const vector<Predicate>& preds = rool.getPredicates();
            for (int i = 0; i < preds.size(); i++) {
                const vector<Parameter>& params = preds.at(i).getParameters();
                cout << preds.at(i).getName() << "(";
                for (int j = 0; j < params.size(); j++) {
                    cout << params.at(j).getValue();
                    if (params.size() - 1 != j) {
                        cout << ",";
                    }
                }
                cout << ")";
                if (preds.size() - 1 != i) {
                    cout << ",";
                }
            }
            cout << "." << endl;
        }
    }

    void printQueries() {
        cout << "Queries(" << queries.size() << "):" << endl;
        for (const auto& pred : queries) {
            cout << "  " << pred.getName() << "(";
            const vector<Parameter>& params = pred.getParameters();
            for (int i = 0; i < params.size(); i++) {
                cout << params.at(i).getValue();
                if (params.size() - 1 != i) {
                    cout << ",";
                }
            }
            cout << ")?" << endl;
        }
    }

    void printDomains() {
        cout << "Domain(" << domains.size() << "):" << endl;
        for (const auto& doms : domains) {
            cout << "  " << doms << endl;
        }
    }



};
