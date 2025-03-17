#pragma once

using namespace std;
#include <iostream>
#include <vector>

#include "Database.h"
#include "Datalog.h"
#include "Relation.h"


class Interpreter {

private:
    Datalog& datalog;
    Databas& database;

public:
    Interpreter(Databas& db, Datalog& d) : database(db), datalog(d) {}

    void evaluateQueries() {
        vector<Predicate> queries = datalog.getQueries();

        for (const auto& query : queries) {
            string queryName = query.getName();
            vector<string> queryParams = query.getParametersAsString();

            //pull the corresponding Relation for the query
            Relation* rel = nullptr;
            for (auto& relation : database.getRelations()) {
                if (relation.getName() == queryName) {
                    rel = &relation;
                    break;
                }
            }

            Relation currRel = *rel;
            for (int i = 0; i < queryParams.size(); i++) {
                const string& param = queryParams[i];

                if (isConstant(param)) {
                    currRel = currRel.select(i, param);
                }
                else {
                    for (int j = i + 1; j < queryParams.size(); j++) {
                        if (queryParams[i] == queryParams[j]) {
                            currRel = currRel.select(i, param);
                        }
                    }
                }
            }

            currRel = currRel.project(queryParams);

            currRel.rename(queryParams);

            cout << "Query: " << query.getName() << " Result: " << currRel.toString() << endl;
        }



    }

    bool isConstant(const string& param) {
        if (param == "X" || param == "Y" || param == "Z") {
            return false;
        }
        return true;
    }


};