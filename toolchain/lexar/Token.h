#ifndef BLOSSOM_TOOLCHAIN_LEXAR_TOKEN
#define BLOSSOM_TOOLCHAIN_LEXAR_TOKEN

/*
The Tokens of the Blossom Language.
Only contains things that are definitive symbols.
*/

#include<vector>

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