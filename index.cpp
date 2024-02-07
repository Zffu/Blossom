/**
The main file of the Blossom CLI. Handles the core CLI Command.

Correct Command Usage should be:
blossom <file> [options] or blossom <options> in some cases

Options:
--version or --v: Shows the version of blossom related software / programs.
--info or --i: Shows your Blossom's distribution information.
*/

#include <iostream>
#include <algorithm>
#include "cli/argParser.h"
#include "toolchain/parser/Parser.h"
#include "cli/fileLess.h"
#include "toolchain/lexar/Lexar.h"
#include <string>
#include <deque>

using namespace std;

void handleFileLessTokens(ArgumentContext ctx) {
	if (!ctx.isFileLess()) {
		cout << "CLI Runtime Error! handleFileLessTokens was called with a non file-less token context!" << endl;
		return;
	}

	ArgumentType type = ctx.getArguments()[0];

	switch (type) {
	case ArgumentType::OPTION_HELP:
		showHelpMessage();
		break;
	case ArgumentType::OPTION_VERSION:
		showVersionMessage();
	}
}

void showGroupTokens(int index, Token group) {
	for (Token t : group.subTokens) {
		if (t.isGroupToken) {
			showGroupTokens(index++, t);
		}
		else {
			std::cout << std::string(index, ' ') << t.type << endl;
		}
	}
}

int main(int argc, char* argv[])
{
	if (argc <= 1) {
		cout << "Invalid Usage of the CLI Command!" << endl;
		showHelpMessage();
		return 0;
	}
	
	ArgumentContext ctx = ArgParser::parseArgs(argc, argv);

	if (ctx.getErrors().size() > 0) {
		cout << "Could not parse the command!" << endl;
		for (string error : ctx.getErrors()) {
			cout << "Argument Parser Error: " << error << endl;
		}
	}

	if (ctx.getFileName() == "" && !ctx.isFileLess()) {
		cout << "Argument Parser Error: Could not parse file name!" << endl;
		return 0;
	}

	if (ctx.isFileLess()) {
		handleFileLessTokens(ctx);
		return 0;
	}
	
	Lexar lexar = Lexar();
	
	if (lexar.tokenizeFile(ctx.getFileName())) {
		std::vector<Token> tokens = lexar.tokens;
		Parser parser = Parser();
		Token group = parser.parseTokens(tokens);

		int spaceIndex = 1;

		cout << "Main" << endl;

		showGroupTokens(spaceIndex, group);
	}
	else {
		cout << "Tokenizing when wrong!";
	}

	return 0;
}

