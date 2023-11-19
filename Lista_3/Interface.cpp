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
		cin >> command;
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
	switch (cmd_name)
	{
	case enter:
		enter(cmd_rest);
		break;

	case vars:
		vars();
		break;

	case print:
		print();
		break;

	case comp:
		comp(cmd_rest);
		break;

	case join:
		join(cmd_rest);
		break;

	case EXIT:
		exit();
		break;

	default:
		cout << invalid_cmd_txt << endl;
		valid_command = false;
		break;
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
	tree = new Tree(cmd);
}

void Interface::vars()
{
	if (tree != nullptr)
	{
		
	}
	//TODO tree.getVars();
	//i potem je wypisz...
}

void Interface::print()
{
	if (tree != nullptr)
	{
		//TODO tree.getExpression()
		//i potem wypisz...
	}

}

void Interface::comp(const string& cmd)
{
	// TODO
}

void Interface::join(const string& cmd)
{
	if (tree != nullptr)
		*tree = *tree + Tree(cmd);
	else
		tree = new Tree(cmd);
}

void Interface::exit()
{
	exit_interface = true;
}
