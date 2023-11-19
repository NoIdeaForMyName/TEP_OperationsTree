#pragma once

#include "Tree.h"
#include "ConstValues.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

//const static int commandNb = 6;
//const static string commands[commandNb] = { "enter", "vars", "print", "comp", "join", "exit" };

enum commands
{
	enter = "enter",
	vars = "vars",
	print = "print",
	comp = "comp",
	join = "join",
	EXIT = "exit"
};

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
const string exiting_txt = "Exiting...";

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
};
