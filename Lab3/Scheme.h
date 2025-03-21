#pragma once

#include <string>
#include <vector>
#include <iostream>

#include "Datalog.h"
#include "Predicate.h"

using namespace std;



class Scheme {

private:

    vector<string> names;

public:

    Scheme(vector<string> names) : names(names) { }

    unsigned size() const {
        return names.size();
    }

    const string& at(int index) const {
        return names.at(index);
    }



};