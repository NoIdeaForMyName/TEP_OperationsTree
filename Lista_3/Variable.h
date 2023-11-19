#pragma once

#include<string>

using namespace std;

class Variable
{
public:
	Variable(string str);

	string toString();
	int getType();

private:
	string str;
	int type; // 0 - operator; 1 - number; 2 - variable
};
