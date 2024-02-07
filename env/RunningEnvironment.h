#ifndef BLOSSOM_ENV_RUNNING
#define BLOSSOM_ENV_RUNNING

#include "Object.h"
#include "Method.h"
#include "Internal.h"
#include <unordered_map>
#include <string>
#include <vector>
#include <iostream>

class RunningEnvironment {
public:
	bool addObject(std::string field, Object o) {
		if (std::find(reserved.begin(), reserved.end(), field) != reserved.end()) {
			std::cout << "Running Environment Error: " << field << " is already a reserved field!";
			return false;
		}
		objects[field] = o;
	}
	bool addMethod(std::string field, Method m) {
		if (std::find(reserved.begin(), reserved.end(), field) != reserved.end()) {
			std::cout << "Running Environment Error: " << field << " is already a reserved field!";
			return false;
		}
		methods[field] = m;
	}

	bool hasProperty(std::string field) {
		return (std::find(reserved.begin(), reserved.end(), field) != reserved.end());
	}

	void loadInternalEnv() {
		addMethod("print", PrintMethod());
	}


private:
	std::unordered_map<std::string, Object> objects;
	std::unordered_map<std::string, Method> methods;
	std::vector<std::string> reserved;
};

#endif 
