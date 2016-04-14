// GetOpt.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

#include "COptionsParcer.h"
#include "COptions.h"

using namespace std;

int main(int argc, char* argv[])
{
	COptionsParcer parcer;

	COption help("help", "Show possible options", noArgument);
	COptionInt option("number", "Test int option", requiredArgument);
	COptionString file("file", "Test string option", requiredArgument);

	vector<COption*> options;
	options.push_back(&help);
	options.push_back(&option);
	options.push_back(&file);

	parcer.InitializeOptions(options);
	parcer.Parse(argc, argv);
	parcer.OutputParseResults();

	int n;
	cin >> n;
}
