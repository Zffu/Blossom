#pragma once
#ifndef BLOSSOM_CORE_COMMONS_STRINGUTILS
#define BLOSSOM_CORE_COMMONS_STRINGUTILS

#include <string>

using namespace std;

string boolToString(bool b) {
	return (b) ? "true" : "false";
}

bool isWhitespace(char c) {
	return (' ' == c) || ('\n' == c) ||
        ('\r' == c) || ('\t' == c) ||
        ('\b' == c) || ('\v' == c) ||
        ('\f' == c);
}

bool isLetter(char c) {
    return (('a' <= c) && (c <= 'z')) || (('A' <= c) && (c <= 'Z'));
}

#endif
