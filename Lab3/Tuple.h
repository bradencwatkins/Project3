#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "Scheme.h"

using namespace std;

class Tuple {

private:

    vector<string> values;

public:

    Tuple(vector<string> values) : values(values) { }

    unsigned size() const {
        return values.size();
    }

    const string& at(int index) const {
        return values.at(index);
    }

    bool operator<(const Tuple t) const {
        return values < t.values;
    }



    // TODO: add more delegation functions as needed
    string toString(const Scheme& scheme) const {
        const Tuple& tuple = *this;
        stringstream out;
        // fix the code to print "name=value" pairs
        for (int i = 0; i < scheme.size(); i++) {
            out << scheme.at(i) << "=" << tuple.at(i);
            if (i != scheme.size() - 1) {
                out << ", ";
            }
        }
        return out.str();
    }

};