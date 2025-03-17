#pragma once

using namespace std;
#include <iostream>
#include <set>

#include "Scheme.h"
#include "Tuple.h"

class Relation {

private:

    string name;
    Scheme scheme;
    set<Tuple> tuples;

public:

    Relation(const string& name, const Scheme& scheme)
      : name(name), scheme(scheme) { }

    //insert tuple into relation
    void addTuple(const Tuple& tuple) {
        tuples.insert(tuple);
    }

    void printScheme() const {
        cout << name << ": ";
        for (int i = 0; i < scheme.size(); i++) {
            cout << scheme.at(i) << " ";
        }
        cout << endl;
    }

    void printTuple() const {
        for (const auto& tuple : tuples) {
            cout << tuple.toString(scheme) << " ";
        }
        cout << endl;
    }

    //get the relations name
    string getName() const {
        return name;
    }

    string toString() const {
        stringstream out;
        for (const auto& tuple : tuples) {
            out << tuple.toString(scheme) << endl;
        }
        return out.str();
    }

    Relation select(int index, const string& value) const {
        Relation result(name, scheme);
        for (const auto& tuple : tuples) {
            if (tuple.at(index) == value) {
                result.addTuple(tuple);
            }
        }
        return result;
    }

    Relation project(const vector<string>& variables) const {
        // Create a new relation to store the projected tuples
        vector<int> varIndices;  // This will hold the indices of the variables in the original scheme
        set<string> seenVariables;  // This will track which variable names we've already added to the projection

        // Determine the indices for the variables in the original scheme
        for (int i = 0; i < variables.size(); ++i) {
            const string& var = variables[i];
            if (seenVariables.find(var) == seenVariables.end()) {  // If this variable hasn't been seen yet
                seenVariables.insert(var);
                for (int j = 0; j < scheme.size(); ++j) {
                    if (scheme.at(j) == var) {
                        varIndices.push_back(j);  // Store the index of this variable
                        break;
                    }
                }
            }
        }

        // Create a new scheme with only the projected columns
        vector<string> projectedScheme;
        for (int index : varIndices) {
            projectedScheme.push_back(scheme.at(index));  // Add the column names to the projected scheme
        }

        // Create a new relation with the projected scheme
        Relation projectedRelation(name, Scheme(projectedScheme));

        // Add only the projected columns to the relation's tuples
        for (const auto& tuple : tuples) {
            vector<string> projectedValues;
            for (int index : varIndices) {
                projectedValues.push_back(tuple.at(index));  // Only keep the projected values
            }
            Tuple projectedTuple(projectedValues);
            projectedRelation.addTuple(projectedTuple);  // Add the projected tuple to the new relation
        }

        return projectedRelation;
    }

    void rename(const vector<string>& newScheme) {
        scheme = Scheme(newScheme);
    }

};
