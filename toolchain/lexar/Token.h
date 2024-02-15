#ifndef BLOSSOM_TOOLCHAIN_LEXAR_TOKEN
#define BLOSSOM_TOOLCHAIN_LEXAR_TOKEN

/*
The Tokens of the Blossom Language.
Only contains things that are definitive symbols.
*/

#include<vector>
#include<string>

enum GroupType {
	PARENTHESIS,
	BRACKETS,
	LIST,
	MAIN
};

enum TokenType {

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

	STRING_UNKNOWN = 9,

	STRING_OPENER = 10
};

class Token {
public:

	TokenType type;
	GroupType group;
	std::vector<Token> sub;
	string raw;

	Token(TokenType t, string r) {
		type = t;
		raw = r;
	}

	Token(GroupType type, std::vector<Token> s) {
		group = type;
		sub = s;
	}

	void setType(TokenType t) {
		type = t;
	}

	void setRaw(string r) {
		raw = r;
	}

};

inline bool isTypeClosing(TokenType t) {
	return (t == PARENTHESIS_CLOSE || t == LIST_CLOSE || t == BRACKET_CLOSE);
}

inline bool isTypeOpening(TokenType t) {
	return (t == PARENTHESIS_OPEN || t == LIST_OPEN || t == BRACKET_OPEN);
}

GroupType getGroupType(TokenType t) {
	if (t == PARENTHESIS_OPEN || t == PARENTHESIS_CLOSE) return PARENTHESIS;
	if (t == LIST_OPEN || t == LIST_CLOSE) return LIST;
	if (t == BRACKET_OPEN || t == BRACKET_CLOSE) return BRACKETS;
}


#endif BLOSSOM_TOOLCHAIN_LEXAR_TOKEN