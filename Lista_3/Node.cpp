#include "Tree.h"

Tree::Node::Node(list<string>& expr, Tree* tree)
	:tree(tree)
{
	if (expr.empty())
	{
		val = new Value();
		childrenNb = 0;
		children = nullptr;
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
		delete children->at(i);
	if (children != nullptr)
		delete children;
}

void Tree::Node::createChildren(int nb, list<string>& expr)
{
	childrenNb = nb;
	children = new vector<Node*>;
	for (int i = 0; i < nb; i++)
		children->push_back(new Node(expr, tree));
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
		tree->errors.addTooShortExpressionError(default_comp_nb);
	}
	for (int i = 0; i < childrenNb; i++)
		children->at(i)->repair();
}

void Tree::Node::join(Node* toJoinNode)
{
	Node* lastChild = children->at(childrenNb - 1);
	if (lastChild->childrenNb == 0)
	{
		children->at(childrenNb - 1) = toJoinNode;
		delete lastChild;
	}
	else
		lastChild->join(toJoinNode);
}

void Tree::Node::print(string& acc)
{
	acc += val->value;
	for (int i = 0; i < childrenNb; i++)
		children->at(i)->print(acc);
}


