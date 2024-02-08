#include "../internal/Internal.h"
#include "../objects/Object.h"
#include "../ctx/MethodContext.h"
#include <iostream>

Object PrintMethod::run(MethodContext ctx) {
	std::cout << "todo: Add Args";
	return Object();
}