#include "Tree.h"
#include <iostream>
#include <sstream>
#include<string>

using namespace std;

template <typename T>
void print(T txt)
{
	cout << txt << endl;
}

int main()
{

	Tree tree1("+ 1 sin x");
	print(tree1.print());

}