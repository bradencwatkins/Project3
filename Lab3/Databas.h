//
// Created by brade on 3/16/2025.
//

#ifndef DATABAS_H
#define DATABAS_H

using namespace std;
#include <iostream>
#include <string>
#include <vector>

#include "Scheme.h"
#include "Tuple.h"
#include "Relation.h"
#include "Parser.h"
#include "Predicate.h"
#include "Datalog.h"

class Databas {

private:
    vector<Relation> relations;
    Datalog datalog;

public:
    Databas() : relations(), datalog() {}

    Databas(const vector<Relation>& relations) : relations(relations) { }

    Datalog& getDatalog() {
        return datalog;
    }

    vector<Relation>& getRelations() {
        return relations;
    }

    //this function makes the relations, and enters the names and schemes into each relation
    void setNames(Datalog& d) {
        vector<Predicate> schemes = d.getSchemes();
        for (const auto& schemePred : schemes) {
            vector<string> schemeNames = schemePred.getParametersAsString();
            Scheme scheme(schemeNames);

            Relation newRelation(schemePred.getName(), scheme);
            relations.push_back(newRelation);
        }
    }

    void setFacts(Datalog& d) {
        vector<Predicate> facts = d.getFacts();

        for (const auto& factPred : facts) {
            string factName = factPred.getName();
            Tuple factTuple(factPred.getParametersAsString());
            for (auto& relation : relations) {
                if (relation.getName() == factName) {
                    relation.addTuple(factTuple);
                    break;
                }
            }
        }
    }

    void printRelations() const {
        for (const auto& relation : relations) {
            cout << "Scheme: " << endl;
            relation.printScheme();  // Assuming Relation has a printScheme() method
            cout << "Tuples: " << endl;
            relation.printTuple();  // Assuming Relation has a printTuples() method
        }
    }

};




#endif //DATABAS_H
