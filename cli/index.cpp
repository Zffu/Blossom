/**
The main file of the Blossom CLI. Handles the core CLI Command.

Correct Command Usage should be:
blossom <file> [options] or blossom <options> in some cases

Options:
--version or --v: Shows the version of blossom related software / programs.
--info or --i: Shows your Blossom's distribution information.
*/

#include "../commons/Logger.h"

#include <iostream>
#include <algorithm>
#include "./argParser.h"
#include "../toolchain/parser/Parser.h"
#include "./fileLess.h"
#include "../toolchain/lexar/Lexar.h"
#include <string>
#include <deque>
#include "../commons/file.h"

using namespace std;

void handleFileLessTokens(ArgumentContext ctx) {
	if (!ctx.isFileLess()) {
		Logger::global().error("CLI Command", "handleFileLessTokens was called with a non file-less token context!");
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
	for (Token t : group.sub) {
		if (t.sub.size() != 0) {
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
		Logger::global().error("CLI Command", "Invalid usage!");
		showHelpMessage();
		return 0;
	}
	
	ArgumentContext ctx = ArgParser::parseArgs(argc, argv);

	if (ctx.getErrors().size() > 0) {
		Logger::global().error("CLI Argument Parser", "Could not parse the arguments!");
		for (string error : ctx.getErrors()) {
			cout << "Argument Parser Error: " << error << endl;
		}
	}

	if (ctx.getFileName() == "" && !ctx.isFileLess()) {
		Logger::global().error("CLI Argument Parser", "Could not parse the file name!");
		return 0;
	}

	if (ctx.isFileLess()) {
		handleFileLessTokens(ctx);
		return 0;
	}
	
	Lexar lexar = Lexar(getContent(ctx.getFileName()));
	
	if (lexar.tokenize()) {
		std::vector<Token> tokens = lexar.tokens;
		Parser parser = Parser();
		Token group = parser.parseTokens(tokens);

		int spaceIndex = 1;

		cout << "Main" << endl;

		showGroupTokens(spaceIndex, group);
	}
	else {
		Logger::global().error("Tokenizer", "Tokenizing went wrong!");
	}

	return 0;
}

