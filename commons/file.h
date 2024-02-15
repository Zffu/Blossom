/*

Small Lib for File Management in Blossom.

*/

#ifndef BLOSSOM_COMMONS_FILELIB
#define BLOSSOM_COMMONS_FILELIB

#include <string>
#include "fstream"

std::string getContent(std::string path) {
	std::ifstream stream; 
	std::string content = "";
	try {
		stream.open(path);
		
		char c;

		while (stream.get(c)) {
			content += c;
		}
	}
	catch(int e) {
		return "";
	}

	return content;
}

#endif 
