#include "Tree.h"
#include <string>
#include <vector>
#include<sstream>
#include <iostream>

using namespace std;

Tree::Node::Node()
	: parent(nullptr)
{}

Tree::Node::Node(const string val)
	: val(val)
	, parent(nullptr)
{}

Tree::Node::Node(const string val, Node* parent)
	: val(val)
	, parent(parent)
{}

Tree::Node::Node(const Node& toCopyNode)
	: val(toCopyNode.val)
{
	parent = nullptr;
}

Tree::Node::~Node() = default;

void Tree::Node::setParent(Node* newParent)
{
	//parent - trzeba usunac
	if (parent != nullptr)
		deleteUp(parent);
	parent = newParent;
	newParent->children.push_back(this);
}

void Tree::Node::addChild(Node* child)
{
	children.push_back(child);
	child->parent = this;
}

Tree::Node* Tree::Node::getParent()
{
	return parent;
}

vector<Tree::Node*> Tree::Node::getChildren()
{
	return children;
}

Tree::Tree(const string input)
{
	//root = new Node(val);
	//currNode = root;
	root = new Node;
	currNode = root;

	vector<string> inValues;
	split_by_whitespace(inValues, input);
	createTree(inValues);
}

Tree::Tree(const Tree& toCopyTree)
	: root(new Node(toCopyTree.root->val))
{
	currNode = root;
	copyDown(root, toCopyTree.root);
}

Tree::~Tree()
{
	deleteDown(root);
}

void Tree::copyDown(Node* newN, Node* n)
{
	//newN->val = n->val; already done
	//newN->setParent(n->parent); already done
	for (int i = 0; i < n->children.size(); i++)
	{
		newN->addChild(new Node(*(n->children[i])));
		copyDown(newN->children[i], n->children[i]);
	}
}


void Tree::deleteDown(Node* n)
{
	if (!n->children.empty())
		for (int i = 0; i < n->children.size(); i++)
			deleteDown(n->children[i]);
	delete n;
}

void Tree::deleteUp(Node* n)
{
	if (n->parent != nullptr)
		deleteUp(n->parent);
	delete n;
}

void Tree::operator=(const Tree& toCopy)
{
	deleteDown(root);
	root = new Node(*toCopy.root);
	currNode = root;
	copyDown(root, toCopy.root);
}

Tree Tree::operator+(const Tree& toAdd) const
{
	Tree outTree(*this);
	outTree.joinWith(toAdd);
	return outTree;
}

string Tree::getValue()
{
	return currNode->val;
}


bool Tree::goParent()
{
	if (currNode->parent != nullptr)
	{
		currNode = currNode->parent;
		return true;
	}
	return false;
}

bool Tree::goChild(int idx)
{
	if (idx >= currNode->children.size()) return false;
	currNode = currNode->children[idx];
	return true;
}

bool Tree::goLastChild()
{
	if (currNode->children.empty()) return false;
	currNode = currNode->children[currNode->children.size() - 1];
	return true;
}

void Tree::setCurr(string val)
{
	currNode->val = val;
}

void Tree::addChild_nGo(string val)
{
	Node* newNode = new Node(val);
	currNode->addChild(newNode);
	currNode = newNode;
}

bool Tree::setChild_nGo(int idx, string val)
{
	bool went = goChild(idx);
	if (went)
		currNode->val = val;
	return went;
}

void Tree::goRoot()
{
	currNode = root;
}

void Tree::joinWith(const Tree& toJointTree) // joins new tree to the leaf of current tree placed farthest to the right
{
	Tree* toJoint = new Tree(toJointTree);
	Node* tempCurrRoot = currNode;
	while (!tempCurrRoot->children.empty()) 
		tempCurrRoot = tempCurrRoot->children[tempCurrRoot->children.size() - 1];
	if (currNode == tempCurrRoot) currNode = toJoint->root;
	vector<Node*>& ch = tempCurrRoot->getParent()->children;
	ch.pop_back();
	tempCurrRoot->getParent()->addChild(toJoint->root);

	delete tempCurrRoot;
}

string Tree::print()
{
	string output = "";
	preorderTraversal(output, root);
	return output.substr(0, output.size()-1); // delete last space character (" ")
}

void Tree::preorderTraversal(string& accum, Node* n)
{
	accum += n->val + space;
	for (int i = 0; i < n->children.size(); i++)
		preorderTraversal(accum, n->children[i]);
}

void Tree::split_by_whitespace(vector<string>& vector, string txt)
{
	istringstream iss(txt);
	while (iss)
	{
		string val;
		iss >> val;
		vector.push_back(val);
	}
	vector.pop_back();
}

bool Tree::isOperator(string val)
{
	// operators: +, -, *, /, sin, cos
	for (int i = 0; i < operators_nb; i++)
		if (val == operators[i]) return true;
	return false;
}

bool Tree::isOperator_1_arg(string val)
{
	for (int i = 0; i < operators_1_arg_nb; i++)
		if (val == operators_1_arg[i]) return true;
	return false;
}

bool Tree::isNumber(string val) // ASCII: 48 - 57 numbers (0 - 9)
{
	for (int i = 0; i < val.size(); i++)
		if (val[i] < ascii_0 || val[i] > ascii_9) return false;
	return true;
}

void Tree::fixVariable_n_Inf(string& var) // cyfry: 48-57; litery: 65-90 i 97-122
{
	bool isLetter = false;
	vector<int> changes;
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
		{
			if (changes.empty())
				changes.push_back(i);
			else
				changes.push_back(i - changes[changes.size() - 1]);
		}
			
	}

	if (isLetter)
	{
		if (!changes.empty())
			informChanges(var, changedVar, changes);
		var = changedVar;
	}
	else 
	{
		cout << var << invalid_variable_txt;
		var = default_variable_name + to_string(variables.size());
		cout << var << endl;
	}
}

void Tree::informChanges(string& old_, string& new_, vector<int>& changes)
{
	cout << old_ << endl;
	for (int i = 0; i < changes.size(); i++)
	{
		int pos = changes[i];
		for (int j = 0; j < pos; j++)
			cout << space;
		cout << invalid_sign;
	}
	cout << tab << invalid_signs_txt <<  new_ << endl;
}

void Tree::createTree(vector<string>& inValues)
{
	bool early_end = false;
	bool next_val = true;
	string val;
	int idx = 0;
	while (idx + 1 < inValues.size() && !early_end)
	//while (idx < inValues.size()-1 && !early_end)
	{
		if (next_val)
		{
			val = inValues[idx];
			currNode->val = val;
			next_val = false;
		}
		
		if (isOperator(val))
		{
			if (isOperator_1_arg(val))
			{
				if (currNode->children.empty())
				{
					//currNode->addChild(new Node(inValues[i + 1]));
					currNode->addChild(new Node);
					goLastChild();
					idx++;
					next_val = true;
				}
				else
				{
					early_end = !goParent();
					val = currNode->val;
				}
			}
			else
			{
				if (currNode->children.size() < 2)
				{
					//currNode->addChild(new Node(inValues[i + 1]));
					currNode->addChild(new Node);
					goLastChild();
					idx++;
					next_val = true;
				}
				else
				{
					early_end = !goParent();
					val = currNode->val;
				}
			}
		}
		else if (isNumber(val))
		{
			early_end = !goParent();
			val = currNode->val;
			//idx++;
		}
		else
		{
			fixVariable_n_Inf(val);
			variables.push_back(val);
			currNode->val = val; // changed (fixed) variable
			early_end = !goParent();
			val = currNode->val;
			//idx++;
		}
	}
	if (!early_end && currNode->val == "")
	{
		if (!inValues.empty())
			currNode->val = inValues[inValues.size() - 1];
		else
			currNode->val = default_comp_nb;
	}

	if (early_end)
	{
		string wholeInput;
		string reducedInput = print();
		for (int i = 0; i < inValues.size(); i++) 
		{
			wholeInput += inValues[i];
			if (i != inValues.size() - 1)
				wholeInput += " ";
		}
		int restFirstIdx = reducedInput.size();
		cout << wholeInput << endl;
		for (int i = 0; i < restFirstIdx; i++) cout << space;
		cout << invalid_sign << tab << unnecessary_rest_txt
		<< endl << following_processed_info_txt << reducedInput << endl;
	}

	// plan: currNode jest w tym momencie na samym dole - wracamy nim do gory i sprawdzamy poprawnosc...
	// currNode moze byc albo na operatorze albo na liczbie...

	if (!isNumber(root->val))
	{
		if (isNumber(currNode->val)) goParent(); // making sure that currNode is on operator
		bool treeFixed = false;
		int added_nb = 0;
		while (!treeFixed)
		{
			if (isOperator_1_arg(currNode->val))
			{
				if (currNode->children.empty())
				{
					currNode->addChild(new Node(default_comp_nb));
					added_nb++;
				}
				treeFixed = !goParent();
			}
			else
			{
				if (currNode->children.size() != 2)
				{
					currNode->addChild(new Node(default_comp_nb));
					added_nb++;
				}
				if (currNode->children.size() == 2)
					treeFixed = !goParent();
			}
		}
		// info about adding...
		if (added_nb != 0)
		{
			string input;
			for (int i = 0; i < inValues.size(); i++)
			{
				input += inValues[i];
				if (i != inValues.size() - 1)
					input += " ";
			}
			cout << input << endl;
			for (int i = 0; i <= input.size(); i++) cout << space;
			cout << invalid_sign << tab << values_are_missing_txt << endl
				<< following_processed_info_txt << print() << endl;
		}
		/*
		 gdyby sie uprzec. zeby nie robic tego wypisywania bledu w sposob podany wyzej, tylko "zgodnie ze sztuka"
		 to moznaby przejsc znowu po drzewie OD GORY NA DOL i liczyc po drodze indeksy i wtedy gdyby znalazlo
		 sie blad, to od razu wiadomo na jakim indeksie wystepuje, ale nie robilem tego w ten sposob,
		 bo ze wzgledu na implementacje, jest wiadome, ze za kazdym razem, brakujace wartosci (liczby)
		 musza zostac dopisane na sam koniec w notacji polskiej
		 */
	}


}

