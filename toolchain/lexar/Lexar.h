#ifndef BLOSSOM_TOOLCHAIN_LEXAR
#define BLOSSOM_TOOLCHAIN_LEXAR

#include "../../commons/Logger.h"

#include <vector>
#include <string>
#include <iostream>
#include "./Token.h"
#include "../../commons/stringutils.h"
#include <fstream>

/*
The Lexar of Blossom.

*/

class Lexar {
public:
	Lexar(std::string s) {
		str += s;
		stringEnd = s.size();
	}
	std::vector<Token> tokens;

	bool tokenize() {
		while (!isEnd()) {
			scanToken(current());

			if (isEnd()) {
				break;
			}
		}
		
		verifyTokens();
		return true;
	}

	void verifyTokens() {

		if (inString) {
			Logger::global().error("Lexer", "Unfinished string litterral opening!");
			inString = false;
		}

		if (invalidStr != "") {
			Token invalidStringLitterralToken = Token(TokenType::STRING_UNKNOWN , invalidStr);
			tokens.push_back(invalidStringLitterralToken);
			invalidStr = "";
		}

	}

private:
	std::string str = "";
	int stringItr = 0;
	int stringEnd = 0;
	bool inString = false;
	std::string invalidStr = "";

	inline bool isEnd() {
		return (stringItr >= stringEnd);
	}

	inline char current() {
		return str[stringItr];
	}

	void scanToken(char c) {
		bool matched = true;


		Token token = Token(TokenType::NONE, "");

		switch (c) {

		case '{':
			token.setType(TokenType::BRACKET_OPEN);
			break;
		case '}':
			token.setType(TokenType::BRACKET_CLOSE);
			break;
		case '(':
			token.setType(TokenType::PARENTHESIS_OPEN);
			break;
		case ')':
			token.setType(TokenType::PARENTHESIS_CLOSE);
			break;
		case '[':
			token.setType(TokenType::LIST_OPEN);
			break;
		case ']':
			token.setType(TokenType::LIST_CLOSE);
			break;
		case ';':
			token.setType(TokenType::SEMICOLON);
			break;
		case '.':
			token.setType(TokenType::DOT);
			break;
		case '\'':
		case '"':
			if (inString) {
				token.setRaw(invalidStr);
				token.setType(TokenType::STRING_LITTERAL);
				inString = false;
				invalidStr = "";
			}
			else {
				inString = true;
				token.setType(TokenType::STRING_OPENER);
			}
			break;
		}

		// That means that is a unkown string litteral.
		if (token.type == TokenType::NONE && !isWhitespace(c)) {
			invalidStr += c;

			matched = false;
		}

		if (matched) {
			if (invalidStr != "") {
				Token invalidStringLitterralToken = Token(TokenType::STRING_UNKNOWN, invalidStr);
				tokens.push_back(invalidStringLitterralToken);
				invalidStr = "";
			}

			if (token.type != TokenType::NONE) {
				tokens.push_back(token);
			}
		}

		++stringItr;
	}


};



#endif