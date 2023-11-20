#include "Tree.h"
#include "Interface.h"
#include <iostream>
#include <sstream>
#include<string>

using namespace std;

template <typename T>
void print(T txt)
{
	cout << txt << endl;
}

template <typename T>
void printVector(vector<T> v)
{
	for (int i = 0; i < v.size(); i++)
		cout << v.at(i) << " ";
	cout << endl;
}

template <typename T>
void printVectorTuple(vector<tuple<T, T>> v)
{
	for (int i = 0; i < v.size(); i++)
		cout << get<0>(v.at(i)) << " -> " << get<1>(v.at(i)) << "; ";
	cout << endl;
}

int main2()
{
	string expression = "+ sin x! 2 s@@iema 44 2 + * 23 4 $$#x";
	//string expression = "+ 2 5";
	Tree tree1(expression);
	tree1 = tree1 + Tree("/ sin y@ cos z");



	print("TREE: ");
	print(tree1.print(false));

	vector<string> vars = tree1.getVariables();
	print("VARIABLES: ");
	printVector(vars);

	Error* error = tree1.getErrors();
	if (error->isTooShort())
		print("TOO SHORT\nNEEDED REST: ");
	else
		print("TOO LONG\nUNUSED REST: ");
	printVector(error->getRestExpr());
	print("\nINVALID VARIABLES: ");
	printVectorTuple(error->getInvalidVariables());

	return 0;
}

int main()
{
	Interface interface;
	interface.start();

	return 0;
}
