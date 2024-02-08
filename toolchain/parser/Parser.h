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

		for (Token token : t) {

			if (token.type == Token::PARENTHESIS_CLOSE) {
				if (!hasParenthesisOpened) {
					Logger::global().error("Parser", "Parenthesis was closed before being opened");
					return Token();
				}
				else {
					hasParenthesisOpened = false;
					if (stack.size() == 0) {
						Logger::global().debug("Parser", "Sub Token Stack Was closed but was empty!");
					}
					Token group = Token(stack);
					sub.push_back(group);
					stack.clear();
				}
			}
			
			else if (token.type == Token::PARENTHESIS_OPEN) {
				hasParenthesisOpened = true;
			}

			else if (hasParenthesisOpened) {
				stack.push_back(token);
			}
		}

		return Token(sub);
	}

private:
std::vector<Token> tokens;
int index;

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