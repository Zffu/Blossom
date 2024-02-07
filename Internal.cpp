#include "env/internal/Internal.h"
#include "env/objects/Object.h"
#include "env/ctx/MethodContext.h"
#include <iostream>

Object PrintMethod::run(MethodContext ctx) {
	std::cout << "todo: Add Args";
	return Object();
}