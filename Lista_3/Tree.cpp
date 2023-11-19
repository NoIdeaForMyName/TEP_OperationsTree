#include "Tree.h"


//Node* root;
//vector<Value*> variables;
//Error errors;

Tree::Tree(string input)
{
	list<string> expression;
	split_by_whitespace(expression, input);
	root = new Node(expression, this);
	while (!expression.empty())
	{
		errors.addTooLongExpression(expression.front());
		expression.pop_front();
	}
}

Tree::Tree(const Tree& toCopyTree) // TODO MOZE POZNIEJ LEPIEJ TO ZROBISZ
{
	string input = toCopyTree.print();
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

void Tree::operator=(const Tree& toCopy) // TODO MOZE POZNIEJ LEPIEJ TO ZROBISZ
{
	delete root;
	variables.clear();
	errors.clear();
	list<string> expression;
	split_by_whitespace(expression, toCopy.print());
	root = new Node(expression, this);
	while (!expression.empty())
	{
		errors.addTooLongExpression(expression.front());
		expression.pop_front();
	}
}

Tree Tree::operator+(const Tree& toAdd) const
{
	Tree outputTree(*this);
	outputTree.joinWith(toAdd);
	return outputTree;
}

string Tree::print() const
{
	string accumulator;
	root->print(accumulator);
	return accumulator;
}

void Tree::joinWith(const Tree& toJointTree)
{
	errors.clear();
	if (root->childrenNb == 0)
	{
		root = toJointTree.root;
	}
	else
		root->join(toJointTree.root);
	for (int i = 0; i < toJointTree.variables.size(); i++)
		variables.push_back(toJointTree.variables[i]);
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
