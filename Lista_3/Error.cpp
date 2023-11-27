#include "Error.h"


Error::Error()
	: tooShort(false)
	, wrong_implementation("", "")
{}


void Error::addTooShortExpressionError(string restVal)
{
	tooShort = true;
	restExpr.push_back(restVal);
}

void Error::addTooLongExpression(string restVal)
{
	tooShort = false;
	restExpr.push_back(restVal);
}

void Error::addInvalidVariableExpression(string invalid, string valid)
{
	invalidVariables.push_back(make_tuple(invalid, valid));
}

void Error::clear()
{
	restExpr.clear();
	invalidVariables.clear();
}

bool Error::isTooShort()
{
	return tooShort;
}

vector<string>& Error::getRestExpr()
{
	return restExpr;
}

vector<tuple<string, string>>& Error::getInvalidVariables()
{
	return invalidVariables;
}

tuple<string, string>& Error::isWrongImplemented()
{
	return wrong_implementation;
}

void Error::setWrongImplementation(string invalid, string valid)
{
	wrong_implementation = make_tuple(invalid, valid);
}


