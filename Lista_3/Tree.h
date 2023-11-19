#pragma once

#include <string>
#include <vector>
#include "ConstValues.h"

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

class Tree
{

	class Node
	{
	public:
		Node();
		Node(const string val);
		Node(const string val, Node* parent);
		Node(const Node& toCopyNode);
		~Node();

		string val;
		Node* parent;
		vector<Node*> children;

		void setParent(Node* newParent);
		void addChild(Node* child);
		Node* getParent();
		vector<Node*> getChildren();
	};

public:
	//Tree();
	Tree(string input);
	Tree(const Tree& toCopyTree);
	~Tree();

	void operator=(const Tree& toCopy);
	Tree operator+(const Tree& toAdd) const;

	string getValue();
	bool goParent();
	bool goChild(int idx);
	bool goLastChild();
	//void setParent_nGo(string val);
	//void setChildren(string* ch_val);
	void setCurr(string val);
	void addChild_nGo(string val);
	bool setChild_nGo(int idx, string val);
	void goRoot();
	string print();
	string printVars(); // TODO
	int compute(string valuations); // TODO
	int compute(); // TODO -> dla braku zmienych (vars)

	bool processInput(string& error_msg);

private:
	Node* root;
	Node* currNode;
	vector<string> variables;

	void copyDown(Node* newN, Node* n);
	static void deleteDown(Node* n);
	static void deleteUp(Node* n);

	void joinWith(const Tree& toJointTree);

	void preorderTraversal(string& accum, Node* n);

	void split_by_whitespace(vector<string>& vector, string txt);
	bool isOperator(string val);
	bool isOperator_1_arg(string val);
	bool isNumber(string val);
	void fixVariable_n_Inf(string& var);
	void informChanges(string& old_, string& new_, vector<int>& changes);

	void createTree(vector<string>& inValues);
};
