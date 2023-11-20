#pragma once

#include <string>
#include <vector>
#include <list>
#include <sstream>
#include "ConstValues.h"
#include "Error.h"

using namespace std;

const int operators_nb = 6;
const int operators_1_arg_nb = 2;
const static string operators[operators_nb] = { "+", "-", "*", "/", "sin", "cos" };
const static string operators_1_arg[operators_1_arg_nb] = { "sin", "cos" };
const int ascii_0 = 48;
const int ascii_9 = 57;
const int ascii_A = 65;
const int ascii_Z = 90;
const int ascii_a = 97;
const int ascii_z = 122;

const string default_comp_nb = "1";

const string invalid_sign = "^";

const string invalid_signs_txt = "Invalid signs, changed to: ";
const string invalid_variable_txt = " - invalid variable, changed to: ";
const string default_variable_name = "var";

const string unnecessary_rest_txt = "Rest is unnecessary";
const string values_are_missing_txt = "Values are missing";
const string following_processed_info_txt = "The following expression will be processed: ";

enum argumentType
{
	number,
	variable,
	operator_1arg,
	operator_2arg
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
		void print(string& acc);
	};


public:
	Tree(string input);
	Tree(const Tree& toCopyTree);
	~Tree();

	void operator=(const Tree& toCopy);
	Tree operator+(const Tree& toAdd) const;

	string print() const;
	vector<string> getVariables();
	Error* getErrors();

private:
	Node* root;
	vector<Value*> variables;
	Error errors;

	void joinWith(const Tree& toJointTree);

	void split_by_whitespace(list<string>& list, string txt);
};



