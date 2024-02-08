#ifndef BLOSSOM_CORE_CLI_ARGPARSE
#define BLOSSOM_CORE_CLI_ARGPARSE

#include "../commons/Logger.h"

#include <string>
#include <vector>
#include "../commons/stringutils.h"

using namespace std;

enum ArgumentType {
	FILE_NAME,
	OPTION_HELP,
	OPTION_VERSION,
	OTPION_INFO
};

class ArgumentContext {
public:
	string getFileName() {
		return fileName;
	}

	vector<ArgumentType> getArguments() {
		return types;
	}

	vector<string> getErrors() {
		return errors;
	}
	
	bool isFileLess() {
		return hasFileLessOptions;
	}

	void addArgument(ArgumentType arg, bool fileLess) {
		if (!hasSetFileLess) {
			hasSetFileLess = true;
			hasFileLessOptions = fileLess;
			types.push_back(arg);
			return;
		}

		if (hasFileLessOptions) {
			if (fileLess != hasFileLessOptions) {
				Logger::global().error("CLI Argument Parser", "Tried adding a incompatible argument in the context!(Context Fileless Status : " + boolToString(hasFileLessOptions) + " Argument Fileless Status : " + boolToString(fileLess) + ")");
				return;
			}
			else {
				Logger::global().error("CLI Argument Parser", "Tried adding another file-less argument but there was already one!");
				return;
			}
		}

		types.push_back(arg);
	}

	void addError(string error) {
		errors.push_back(error);
	}

	void setFileName(string file) {
		fileName = file;
	}


private:
	string fileName;
	vector<ArgumentType> types;
	vector<string> errors;
	bool hasFileLessOptions;
	bool hasSetFileLess;
};

class ArgParser {
public:
	static ArgumentContext parseArgs(int argc, char* argv[]) {
		bool hasFileArgument = false;
		ArgumentContext context;

		for (int i = 1; i < argc; i++) {
			if (argv[i][0] != '-') {
				if (hasFileArgument) {
					Logger::global().error("CLI Argument Parser", "Dissallowed use of the file argument: Found multiple file arguments.");
					return context;
				}
				if (context.getArguments().size() > 0) {
					Logger::global().error("CLI Argument Parser", "Illegal use of CLI Arguments: File must be the first argument when defining properties with it.");
					return context;
				}
				hasFileArgument = true;
				context.setFileName(argv[i]);
			}

			else {
				// Directly gets the first letter as its faster than looping trough the whole char*

				string full = argv[i];
				bool isFileLess = (full[1] == '-');
				char c = (isFileLess) ? full[2] : full[1];
				ArgumentType type;

				switch (c) {
				case 'v':
					type = ArgumentType::OPTION_VERSION;
					break;
				case 'i':
					type = ArgumentType::OTPION_INFO;
					break;
				case 'h':
					type = ArgumentType::OPTION_HELP;
					break;
				default:
					Logger::global().error("CLI Argument Parser", "Unknown Option: " + full);
					return context;
				}

				context.addArgument(type, isFileLess);
			}
		}

		return context;
	}
};

#endif 
