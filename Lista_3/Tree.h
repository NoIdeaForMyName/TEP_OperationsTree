#pragma once

#include <string>
#include <vector>
#include <list>
#include <set>
#include <sstream>
#include "ConstValues.h"
#include "Error.h"
//#include "Interface.h"

using namespace std;

const int operators_nb = 7;
const int operators_1_arg_nb = 2;
const static string operators[operators_nb] = { "+", "-", "*", "/", "sin", "cos", "++" };
const static string operators_1_arg[operators_1_arg_nb] = { "sin", "cos" };
const static string add = "+";
const static string sub = "-";
const static string mul = "*";
const static string divi = "/";
const static string sinu = "sin";
const static string cosi = "cos";

const static string addV2 = "++";


const int ascii_0 = 48;
const int ascii_9 = 57;
const int ascii_A = 65;
const int ascii_Z = 90;
const int ascii_a = 97;
const int ascii_z = 122;

const string default_comp_nb = "1";
const string default_variable_name = "var";

enum argumentType
{
	number,
	variable,
	operator_1arg,
	operator_2arg,
};


class Tree
{

	class Value
	{
	public:
		Value();
		Value(string val, Error& err, int varNb);

		// value - no changes from the input value
		// valuatedVariable - for numbers and operators - no changes; for variables - valuated number
		argumentType calculateType(string& validVal, Error& err, int varNb);
		string validateVariable(const string var, Error& err, int varNb);
		bool valuate(string nb);

		string value;
		argumentType type;
		bool isVariable;
		string valuatedVariable;
	};


	class Node
	{
	public:
		Node(list<string>& expr, Tree* tree);
		~Node();

		Value* val;
		int childrenNb;
		vector<Node*> children;
		Tree* tree;

		void createChildren(int nb, list<string>& expr);
		int calculateChildrenNb(argumentType t);

		void repair();
		void join(Node* toJoinNode);
		void print(string& acc, bool isValuated);
		float compute();

		bool variablesContains(string val);
	};


public:
	Tree(string input);
	Tree(const Tree& toCopyTree);
	~Tree();

	void operator=(const Tree& toCopy);
	Tree operator+(const Tree& toAdd) const;

	string print(bool isValuated) const;
	vector<string> getVariables();
	Error* getErrors();
	float compute(list<string> valuations);

private:
	Node* root;
	vector<Value*> variables;
	Error errors;

	void joinWith(const Tree& toJointTree);

	void split_by_whitespace(list<string>& list, string txt);
};



