#ifndef BLOSSOM_TOOLCHAIN_LEXAR_TOKEN
#define BLOSSOM_TOOLCHAIN_LEXAR_TOKEN

/*
The Tokens of the Blossom Language.
Only contains things that are definitive symbols.
*/

#include<vector>
#include<string>

enum TokenGroupType {
	MAIN = 0,
	BRACKETS = 1,
	PARENTHESIS = 2,
	LIST = 3
};

std::string getOpeningChar(TokenGroupType type) {
	switch (type) {
	case BRACKETS:
		return "{";
	case PARENTHESIS:
		return "(";
	case LIST:
		return "[";
	default:
		return "";
	}
}

std::string getClosingChar(TokenGroupType type) {
	switch (type) {
	case BRACKETS:
		return "}";
	case PARENTHESIS:
		return ")";
	case LIST:
		return "]";
	default:
		return "";
	}
}

TokenGroupType getGroupTypeFromString(char c) {
	if (c == '{' || c == '}') return BRACKETS;
	if (c == '[' || c == ']') return LIST;
	if (c == '(' || c == ')') return PARENTHESIS;
}

bool isAGroupOpening(char c) {
	return (c == '{' || c == '[' || c == '(');
}

bool isAGroupClosing(char c) {
	return (c == '}' || c == ']' || c == ')');
}

class Token {
public:
	std::vector<Token> subTokens;
	bool isGroupToken = false;

	enum Type {

		// Dynamically assigned types / Internal Types
		NONE = -1,
		STRING_LITTERAL = -2,
		NUMBER_LITTERAL = -3,
		ENDOFFILE = -4,

		// Grouping Types
		BRACKET_OPEN = 1,
		BRACKET_CLOSE = 2,
		PARENTHESIS_OPEN = 3,
		PARENTHESIS_CLOSE = 4,
		LIST_OPEN = 5,
		LIST_CLOSE = 6,

		// Misc Types
		DOT = 7,
		SEMICOLON = 8,
		STRING_OPENER = 10,


		// Unknown
		STRING_UNKNOWN = 9


	};

	Type type;
	string raw;

	Token(Type t, string r) {
		type = t;
		raw = r;
	}

	Token(std::vector<Token> sub) {
		isGroupToken = true;
		subTokens = sub;
	}

	Token() {
		type = Type::NONE;
		raw = "";
	}

	void setType(Type t) {
		type = t;
	}

	void setRaw(string r) {
		raw = r;
	}

};

#endif BLOSSOM_TOOLCHAIN_LEXAR_TOKEN