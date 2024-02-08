#ifndef BLOSSOM_TOOLCHAIN_PARSER
#define BLOSSOM_TOOLCHAIN_PARSER

#include "../../commons/Logger.h"

#include <vector>
#include <iostream>
#include "../lexar/Token.h"

class Parser {

public:
	Token parseTokens(std::vector<Token> t) {
		tokens = t;
		index = 0;
		std::vector<Token> sub;

		bool hasParenthesisOpened = false;
		std::vector<Token> stack;

		Token main = getSubTokens(-1, TokenGroupType::MAIN);
		return main;
	}

private:
std::vector<Token> tokens;
int index;

Token getSubTokens(int startIndex, TokenGroupType groupType) {
	std::vector<Token> stack;

	for(int i = startIndex + 1, i < tokens.size(), i++) {
		Token token = tokens[i];

		if(isTypeGroupClosing(token.type)) {
			if(getGroupTypeByType(token.type) == groupType) {
				break;
			}
		}
		else if(isTypeGroupOpening(token.type)) {
			Token group = getSubTokens(i, getGroupTypeByType(token.type));
			stack.push_back(group);
		}
		else {
			stack.push_back(token);
		}
	}

	return Token(stack, groupType);
} 

bool hasNext() {
	return ((index + 1) < tokens.size());
}

Token peek() {
	return tokens[index + 1];
}

Token next() {
	index++;
	return tokens[index];
}

};

#endif