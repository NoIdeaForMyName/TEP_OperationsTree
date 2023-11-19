#include "Error.h"


Error::Error()
	: tooShort(false)
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

vector<string> Error::getRestExpr()
{
	return restExpr;
}

vector<tuple<string, string>> Error::getInvalidVariables()
{
	return invalidVariables;
}
