#pragma once
using namespace std;
#include <vector>
#include <string>
#include "Predicate.h"


class Rule {

private:
    Predicate headPredicate;
    vector<Predicate> bodyPredicates;

public:
    Rule(Predicate& headPred) : headPredicate(headPred) {}

    Predicate& getHead() {
        return headPredicate;
    }

    Predicate& getLastBody() {
        return bodyPredicates.back();
    }

    const vector<Predicate>& getPredicates() const {
        return bodyPredicates;
    }

    void addHead(Predicate h) {
        headPredicate = h;
    }

    void addBody(Predicate b) {
        bodyPredicates.push_back(b);
    }

};
