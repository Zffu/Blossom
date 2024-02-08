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
	Lexar() {}
	std::vector<Token> tokens;

	bool tokenize(const std::string s) {
		str = s;
		baseItr = 0;
		stringItr = 0;
		stringEnd = s.size();

		while (!isEnd()) {
			scanToken(current());

			if (isEnd()) {
				break;
			}
		}
		
		verifyTokens();

		

		return true;
	}

	bool tokenizeFile(std::string fileName) {
		str = "";
		baseItr = 0;
		stringItr = 0;
		stringEnd = 0;

		ifstream in;
		
		try {
			in.open(fileName);

			char c;

			while (in.get(c)) {
				scanToken(c);
			}
		}
		catch (int e) {
			Logger::global().error("Tokenization", "An Error occured while tokenising the Blossom File" + fileName);

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
			Token invalidStringLitterralToken = Token(Token::Type::STRING_UNKNOWN, invalidStr);
			tokens.push_back(invalidStringLitterralToken);
			invalidStr = "";
		}

	}

private:
	std::string str;
	std::vector<Token>::iterator tokens_itr;
	Token eofToken;
	int baseItr;
	int stringItr;
	int stringEnd;
	bool inString = false;
	string invalidStr;

	bool isEnd() {
		return (stringItr >= stringEnd);
	}

	char current() {
		return str[stringItr];
	}

	void scanToken(char c) {
		bool matched = true;


		Token token;

		switch (c) {

		case '{':
			token.setType(Token::Type::BRACKET_OPEN);
			break;
		case '}':
			token.setType(Token::Type::BRACKET_CLOSE);
			break;
		case '(':
			token.setType(Token::Type::PARENTHESIS_OPEN);
			break;
		case ')':
			token.setType(Token::Type::PARENTHESIS_CLOSE);
			break;
		case '[':
			token.setType(Token::Type::LIST_OPEN);
			break;
		case ']':
			token.setType(Token::Type::LIST_CLOSE);
			break;
		case ';':
			token.setType(Token::Type::SEMICOLON);
			break;
		case '.':
			token.setType(Token::Type::DOT);
			break;
		case '\'':
		case '"':
			if (inString) {
				token.setRaw(invalidStr);
				token.setType(Token::Type::STRING_LITTERAL);
				inString = false;
				invalidStr = "";
			}
			else {
				inString = true;
				token.setType(Token::Type::STRING_OPENER);
			}
			break;
		}

		// That means that is a unkown string litteral.
		if (token.type == Token::Type::NONE && !isWhitespace(c)) {
			invalidStr += c;

			matched = false;
		}

		if (matched) {
			if (invalidStr != "") {
				Token invalidStringLitterralToken = Token(Token::Type::STRING_UNKNOWN, invalidStr);
				tokens.push_back(invalidStringLitterralToken);
				invalidStr = "";
			}

			if (token.type != Token::Type::NONE) {
				tokens.push_back(token);
			}
		}

		stringItr++;
	}


};



#endif