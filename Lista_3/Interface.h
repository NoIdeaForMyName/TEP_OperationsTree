#pragma once

#include "Tree.h"
#include "Error.h"
#include "ConstValues.h"
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <sstream>

using namespace std;

//const static int commandNb = 6;
//const static string commands[commandNb] = { "enter", "vars", "print", "comp", "join", "exit" };


const string ENTER = "enter";
const string VARS = "vars";
const string PRINT = "print";
const string COMP = "comp";
const string JOIN = "join";
const string EXIT = "exit";


const string start_info = "Commands:\n"
						  "enter <formula>\n"
						  "vars\n"
						  "print\n"
						  "comp <var0> <var1> ... <varN>\n"
						  "join <formula>\n"
						  "exit\n";

const string prompt_sign = ">> ";
//const string space = " ";
const string invalid_cmd_txt = "Invalid command name!";
const string invalid_argument_txt = "Invalid argument!";
const string invalid_variable_name_txt = "Invalid variable name!";
const string exiting_txt = "Exiting...";
const string no_tree_info_txt = "Create tree first!";
const string changed_to_txt = "->";

class Interface
{
public:
	Interface();
	void start();

private:
	Tree* tree;
	bool exit_interface;
	bool processCommand(string cmd);
	void split_cmd_name(const string& input, string& cmd_name, string& rest);

	void enter(const string& cmd);
	void vars();
	void print();
	void comp(const string& cmd);
	void join(const string& cmd);
	void exit();

	bool treeExists();

	bool split_to_int_and_inf(list<int>& list, string txt);
	bool isInteger(string n);
};
