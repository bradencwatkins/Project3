#pragma once
using namespace std;
#include <vector>
#include <string>




class Parameter {


private:
    string value;
    bool isId;


public:
    Parameter(const string& value, const bool& isId) : value(value), isId(isId) {}


    string getValue() const {
        return value;
    }

    bool getisId() const {
        return isId;
    }


};
