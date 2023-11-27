#pragma once

#include <string>
#include <vector>
#include <tuple>

using namespace std;

class Error // 3 types of error: 1. too short expression 2. too long expression 3. invalid variable
{
public:
	Error();

	void addTooShortExpressionError(string restVal);
	void addTooLongExpression(string restVal);
	void addInvalidVariableExpression(string invalid, string valid);
	void clear();

	bool isTooShort();
	vector<string>& getRestExpr();
	vector<tuple<string, string>>& getInvalidVariables();
	tuple<string, string>& isWrongImplemented();
	void setWrongImplementation(string invalid, string valid);

private:
	tuple<string, string> wrong_implementation;
	bool tooShort;
	vector<string> restExpr;
	vector<tuple<string, string>> invalidVariables;

};

