#include "Tree.h"


//Node* root;
//vector<Value*> variables;
//Error errors;

//TREE

Tree::Tree(string input)
{
	list<string> expression;
	split_by_whitespace(expression, input);
	root = new Node(expression, this);
	if (expression.empty()) root->repair();
	while (!expression.empty())
	{
		errors.addTooLongExpression(expression.front());
		expression.pop_front();
	}
}

Tree::Tree(const Tree& toCopyTree)
{
	string input = toCopyTree.print(false);
	list<string> expression;
	split_by_whitespace(expression, input);
	root = new Node(expression, this);
	while (!expression.empty())
	{
		errors.addTooLongExpression(expression.front());
		expression.pop_front();
	}
}

Tree::~Tree()
{
	delete root;
}

void Tree::operator=(const Tree& toCopy)
{
	delete root;
	variables.clear();
	errors.clear();
	list<string> expression;
	split_by_whitespace(expression, toCopy.print(false));
	root = new Node(expression, this);
	while (!expression.empty())
	{
		errors.addTooLongExpression(expression.front());
		expression.pop_front();
	}
}

Tree Tree::operator+(const Tree& toAdd) const
{
	string thisExpr = print(false);
	while (thisExpr[thisExpr.size() - 1] != space_ch) thisExpr.pop_back();
	thisExpr.pop_back();
	string expression = thisExpr + space + toAdd.print(false);
	//Tree outputTree(*this);
	//outputTree.joinWith(*(new Tree(toAdd)));
	return Tree(expression);
}

string Tree::print(bool isValuated) const
{
	string accumulator;
	root->print(accumulator, isValuated);
	accumulator.pop_back();
	return accumulator;
}

vector<string> Tree::getVariables()
{
	vector<string> output;
	set<string> usedVars;
	for (int i = 0; i < variables.size(); i++)
	{
		string var = variables[i]->value;
		if (usedVars.count(var) == 0)
		{
			usedVars.insert(var);
			output.push_back(var);
		}
	}
	return output;
}

Error* Tree::getErrors()
{
	return &errors;
}

float Tree::compute(list<string> valuations)
{
	//for (int i = 0; i < variables.size(); i++)
	//{
	//	string valuation = valuations.front();
	//	valuations.pop_front();
	//	variables[i]->valuatedVariable = valuation;
	//}
	vector<string> variablesNames = getVariables();
	for (int i = 0; i < variablesNames.size(); i++)
	{
		string varName = variablesNames[i];
		string valuation = valuations.front();
		valuations.pop_front();
		for (int j = 0; j < variables.size(); j++)
			if (variables[j]->value == varName)
			{
				variables[j]->valuatedVariable = valuation;

			}

	}
	return root->compute();
}

void Tree::joinWith(const Tree& toJointTree)
{
	errors.clear();
	if (root->childrenNb == 0)
	{
		delete root;
		root = toJointTree.root;
	}
	else
		root->join(toJointTree.root);
	//for (int i = 0; i < toJointTree.variables.size(); i++) // TODO MUSI BYC COPY
		//variables.push_back(toJointTree.variables[i]);
}

void Tree::split_by_whitespace(list<string>& list, string txt)
{
	istringstream iss(txt);
	while (iss)
	{
		string val;
		iss >> val;
		list.push_back(val);
	}
	list.pop_back();
}



//VALUE

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
		if (value == operators[i]) return operator_2arg;
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
	return true;
}



//NODE

Tree::Node::Node(list<string>& expr, Tree* tree)
	:tree(tree)
{
	if (expr.empty())
	{
		val = new Value();
		childrenNb = 0;
		//children = nullptr;
	}
	else
	{
		val = new Value(expr.front(), tree->errors, tree->variables.size());
		expr.pop_front();
		if (val->type == variable)
		{
			// add to variables...
			tree->variables.push_back(val);
		}

		childrenNb = calculateChildrenNb(val->type);

		createChildren(childrenNb, expr);
	}
}

Tree::Node::~Node()
{
	for (int i = 0; i < childrenNb; i++)
		delete children[i];
	delete val;
}

void Tree::Node::createChildren(int nb, list<string>& expr)
{
	childrenNb = nb;
	//children = new vector<Node*>;
	if (val->value != addV2)
		for (int i = 0; i < nb; i++)
			children.push_back(new Node(expr, tree));
	else
	{
		bool valid = true;
		for (int i = 0; i < nb; i++)
			children.push_back(new Node(expr, tree));
		if (children[0]->val->type != number && children[0]->val->type != variable)
			valid = false;
		if (children[1]->val->type != operator_1arg && children[1]->val->type != operator_2arg)
			valid = false;

		if (!valid)
		{
			tree->errors.setWrongImplementation(addV2, add);
			val->value = add;
			val->valuatedVariable = add;
		}
	}

}

int Tree::Node::calculateChildrenNb(argumentType t)
{
	switch (t)
	{
	case number | variable: return 0;
	case operator_1arg: return 1;
	case operator_2arg: return 2;
	}
}

void Tree::Node::repair()
{
	if (val->value == "")
	{
		val->value = default_comp_nb;
		val->valuatedVariable = default_comp_nb;
		tree->errors.addTooShortExpressionError(default_comp_nb);
	}
	for (int i = 0; i < childrenNb; i++)
		children[i]->repair();
}

void Tree::Node::join(Node* toJoinNode)
{
	Node* lastChild = children[childrenNb - 1];
	if (lastChild->childrenNb == 0)
	{
		children[childrenNb - 1] = toJoinNode;
		delete lastChild;
	}
	else
		lastChild->join(toJoinNode);
}

void Tree::Node::print(string& acc, bool isValuated)
{
	if (!isValuated)
		acc += val->value + space;
	else
		acc += val->valuatedVariable + space;
	for (int i = 0; i < childrenNb; i++)
		children[i]->print(acc, isValuated);
}

float Tree::Node::compute()
{
	if (childrenNb == 0)
	{
		return stof(val->valuatedVariable);
	}

	if (val->type == operator_2arg)
	{
		if (val->value == add || val->value == addV2)
			return children[0]->compute() + children[1]->compute();
		if (val->value == sub)
			return children[0]->compute() - children[1]->compute();
		if (val->value == mul)
			return children[0]->compute() * children[1]->compute();
		if (val->value == divi)
			return children[0]->compute() / children[1]->compute();
		//if (val->value == addV2)
			//return 
	}

	else if (val->type == operator_1arg)
	{
		if (val->value == sinu)
			return sin(children[0]->compute());
		if (val->value == cosi)
			return cos(children[0]->compute());
	}

	return 0; // somethings wrong if it is returned
}

