#include "Interface.h"


Interface::Interface()
	:tree(nullptr)
	,exit_interface(false)
{}

void Interface::start()
{
	cout << start_info << endl;
	string command;

	while (!exit_interface)
	{
		cout << prompt_sign;
		getline(cin, command);
		processCommand(command);
	}
	cout << exiting_txt << endl;
}

bool Interface::processCommand(string cmd)
{
	bool valid_command = true;
	string cmd_name;
	string cmd_rest;
	split_cmd_name(cmd, cmd_name, cmd_rest);

	if (cmd_name == ENTER)
		enter(cmd_rest);

	else if (cmd_name == VARS)
		vars();

	else if (cmd_name == PRINT)
		print();

	else if (cmd_name == COMP)
		comp(cmd_rest);

	else if (cmd_name == JOIN)
		join(cmd_rest);

	else if (cmd_name == EXIT)
		exit();

	else
	{
		cout << invalid_cmd_txt << endl;
		valid_command = false;
	}

	return valid_command;
}

void Interface::split_cmd_name(const string& input, string& cmd_name, string& rest)
{
	bool first_whitespaces = true;
	bool rest_now = false;
	for (int i = 0; i < input.size(); i++)
	{
		if (rest_now) {rest += input[i];}

		else if (input[i] != space_ch)
		{
			first_whitespaces = false;
			cmd_name += input[i];
		}
		else if (!first_whitespaces)
			rest_now = true;
	}
}

void Interface::enter(const string& cmd)
{
	if (treeExists())
		delete tree;
	tree = new Tree(cmd);
	Error* err = tree->getErrors();
	if (!err->getInvalidVariables().empty())
	{
		cout << invalid_variable_name_txt << endl;
		vector<tuple<string, string>> invalid_valid = err->getInvalidVariables();
		for (int i = 0; i < invalid_valid.size(); i++)
		{
			cout << get<0>(invalid_valid[i]) << changed_to_txt << get<1>(invalid_valid[i]) << endl;
		}
	}
	if (!err->getRestExpr().empty())
	{
		vector<string> restExpr = err->getRestExpr();
		if (err->isTooShort())
			cout << values_are_missing_txt;
		else
			cout << unnecessary_rest_txt;
		for (int i = 0; i < restExpr.size(); i++) cout << restExpr[i] << space;
		cout << endl << following_processed_info_txt << tree->print(false) << endl;
	}

}

void Interface::vars()
{
	if (!treeExists()) 
		cout << no_tree_info_txt << endl;
	else
	{
		vector<string> vars = tree->getVariables();
		set<string> usedVars;
		for (int i = 0; i < vars.size(); i++)
		{
			string var = vars[i];
			if (usedVars.count(var) == 0)
			{
				usedVars.insert(var);
				cout << var << space;
			}
		}
		cout << endl;
	}

}

void Interface::print()
{
	if (!treeExists())
		cout << no_tree_info_txt << endl;
	else
	{
		cout << tree->print(false) << endl;
	}
}

void Interface::comp(const string& cmd)
{
	if (!treeExists())
		cout << no_tree_info_txt << endl;
	else
	{
		list<int> valuations;
		if (split_to_int_and_inf(valuations, cmd))
		{
			tree->compute(valuations); // TODO TODO TODO
		}
	}
}

void Interface::join(const string& cmd)
{
	if (!treeExists())
		cout << no_tree_info_txt << endl;

	Tree copyTree = *tree;
	enter(cmd);
	*tree = copyTree + *tree;
	//*tree = *tree + Tree(cmd);
}

void Interface::exit()
{
	exit_interface = true;
}

bool Interface::treeExists()
{
	return tree != nullptr;
}

bool Interface::split_to_int_and_inf(list<int>& list, string txt)
{
	string val;
	bool wrongInput = false;
	int lastIdx;
	for (int i = 0; i < txt.size() && !wrongInput; i++)
	{
		if (txt[i] != space_ch)
		{
			val += txt[i];

		}
		else if (isInteger(val))
		{
			list.push_back(stoi(val));
			val = "";
		}
		else
		{
			wrongInput = true;
			lastIdx = i;
		}
	} if (!wrongInput && val != "") list.push_back(stoi(val));

	if (wrongInput)
	{
		for (int i = 0; i < lastIdx; i++)
		{
			cout << space;
		}
		cout << invalid_sign << invalid_argument_txt;
	}

	return !wrongInput;
}

bool Interface::isInteger(string n)
{
	for (int i = 0; i < n.size(); i++)
		if (n[i] < ascii_0 || n[i] > ascii_9) return false;
	return true;
}


