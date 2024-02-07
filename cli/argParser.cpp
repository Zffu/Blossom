#include "argParser.h";
#include <vector> 
#include <iostream>

using namespace std;

vector<Argument> ArgParser::parseArgs() {
	bool alreadyHasFile = false;
	for (int i = 0; i < argc; i++) {
		if (argv[i][1] != '-') {
			if (!alreadyHasFile) {
				alreadyHasFile = true;
			}
			else {
				cout << "Arg Parser Error: Found multiple File Arguments!";
			}
		}
	}

	return vector<Argument>();
}
