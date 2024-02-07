#ifndef BLOSSOM_ENV_METHOD_CONTEXT
#define BLOSSOM_ENV_METHOD_CONTEXT

#include <string>
#include "Object.h"
#include<vector>

class MethodContext {
public:
	MethodContext(Object p, std::vector<Object> a) {
		args = a;
		parent = p;
	}

	std::vector<Object> getArguments() {
		return args;
	}

	Object getParent() {
		return parent;
	}

private:
	std::vector<Object> args;
	Object parent;
};

#endif BLOSSOM_ENV_METHOD_CONTEXT