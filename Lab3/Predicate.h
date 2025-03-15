#pragma once
using namespace std;
#include <vector>
#include <string>
#include "Parameter.h"




class Predicate {
private:
    string name;
    vector<Parameter> parameters;


public:


    Predicate(const string& name) : name(name), parameters() {}




    void addParameter(const Parameter& param) {
        parameters.push_back(param);
    }


    string getName() const {
        return name;
    }


    const vector<Parameter>& getParameters() const {
        return parameters;
    }


};
