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

int main1()
{
	Tree tree("+");
	print(tree.getValue());
	tree.addChild_nGo("5");
	print(tree.getValue());
	print(tree.goChild(0));
	print(tree.goParent());
	tree.addChild_nGo("*");
	tree.goRoot();
	tree.addChild_nGo("err");
	tree.goRoot();
	tree.goChild(1);
	print(tree.getValue());
	tree.goParent();
	tree.goChild(2);
	print(tree.getValue());

	Tree tree2("-");
	tree2.addChild_nGo("9");
	tree2.goParent();
	tree2.addChild_nGo("8");

	cout << endl << endl << endl;
	print(tree.print());
	print(tree2.print());

	Tree tree3("s");
	tree3 = tree + tree2;
	print(tree3.getValue());

	print(tree3.print());

	return 0;
}

int main2() {
	string inputText = "This is   a    sample    text\n alasaod  dsa d";

	// Using std::istringstream to split the text
	istringstream iss(inputText);
	vector<string> words;

	// Read each word from the stringstream
	do {
		string word;
		iss >> word;
		if (!word.empty()) {
			words.push_back(word);
		}
	} while (iss);

	// Display the result
	cout << "Original Text: " << inputText << endl;
	cout << "Array of Words:" << endl;
	for (const auto& word : words) {
		cout << "[" << word << "] ";
	}
	cout << endl;

	vector<string> test;
	test.push_back("val1");
	test.push_back("val2");
	test.push_back("val3");
	cout << "BEFORE: " << test[1] << endl;
	void change(string& x);
	change(test[1]);

	cout << "AFTER: " << test[1] << endl;

	return 0;
}

void change(string& x)
{
	x = "sukces";
}


int main()
{
	Tree tree1("+ * val$ue sin @ / 7 2");
	cout << "Tree: " << tree1.print() << endl;

	cout << endl << endl;
	Tree tree2("+ 1 9 2 * 5 + 7 2");
	cout << "Tree: " << tree2.print() << endl;

	cout << endl << endl;
	Tree tree3("sin + * - 7 2");
	cout << "Tree: " << tree3.print() << endl;

	cout << endl << endl;
	Tree tree4(" sin   +        *  -          7 242");
	cout << "Tree: " << tree4.print() << endl;

	cout << endl << endl;
	Tree tree5("ala ma kota");
	cout << "Tree: " << tree5.print() << endl;

	return 0;
}


// TODO: sprawdzanie czy val jest git w Node
// TODO: zrob przekazywanie vectora obiektow error
// TODO: wez oddziel moze tworzenie drzewa i jego naprawianie
// TODO: powroc do tego pomyslu, ze zrobisz klase Variable, ktora bedzie kontenerem stringow
// TODO: (i tam przechowuj nazwe zmiennej var i jej wartosc liczbowa, a dla nie var, to inf. czym to jest
// TODO: (operator, liczba))
// TODO: i do tej Variable, dodaj bool isActual i tam przechowuj inf. czy vector Variable jest aktualny

//TEST CZY GIT DZIALA
