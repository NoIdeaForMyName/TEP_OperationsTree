#include "Tree.h"

Tree::Value::Value()
	: value("")
	, type(number)
	, isVariable(false)
	, valuatedVariable("")
{}

Tree::Value::Value(string val, Error& err, int varNb)
	:value(val)
{
	string validVar;
	type = calculateType(validVar, err, varNb);
	if (type == variable)
	{
		isVariable = true;
		value = validVar;
	}
	else 
	{
		isVariable = false;
		valuatedVariable = value;
	}

}

argumentType Tree::Value::calculateType(string& validVal, Error& err, int varNb)
{
	for (int i = 0; i < operators_1_arg_nb; i++)
		if (value == operators_1_arg[i]) return operator_1arg;
	for (int i = 0; i < operators_nb; i++)
		if (value == operators[i]) operator_2arg;
	for (int i = 0; i < value.size(); i++)
		if (value[i] < ascii_0 || value[i] > ascii_9)
		{
			validVal = validateVariable(value, err, varNb);
			return variable;
		}
	return number;
}

string Tree::Value::validateVariable(const string var, Error& err, int varNb) // cyfry: 48-57; litery: 65-90 i 97-122
{
	bool changes = false;
	bool isLetter = false;
	string changedVar;
	for (int i = 0; i < var.size(); i++)
	{
		if (var[i] >= ascii_0 && var[i] <= ascii_9)
			changedVar += var[i];
		else if ((var[i] >= ascii_A && var[i] <= ascii_Z) || (var[i] >= ascii_a && var[i] <= ascii_z))
		{
			changedVar += var[i];
			isLetter = true;
		}
		else
			changes = true;

	}

	if (isLetter)
	{
		if (changes)
			err.addInvalidVariableExpression(var, changedVar);
		return changedVar;
	}
	changedVar = default_variable_name + to_string(varNb);
	err.addInvalidVariableExpression(var, changedVar);
	return changedVar;
}

bool Tree::Value::valuate(string nb)
{
	valuatedVariable = "";
	for (int i = 0; i < nb.size(); i++)
	{
		if (nb[i] < ascii_0 || nb[i] > ascii_9) return false;

		valuatedVariable += nb[i];
	}
}

