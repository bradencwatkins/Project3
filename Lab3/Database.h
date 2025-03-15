#pragma once


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

class Database {

private:
    vector<Relation> relations;
    Datalog datalog;

public:

    // Datalog& getDatalog() {
    //     return datalog;
    // }
    //
    // void setNames(Datalog& d) {
    //     vector<string> names = d.getSchemeNames();
    //     for (const auto& name : names) {
    //         cout << name << endl;  // Print the names or store them as necessary
    //     }
    // }

};