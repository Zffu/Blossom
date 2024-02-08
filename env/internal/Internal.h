#ifndef BLOSSOM_RUNNING_ENVIRONMENT_INTERNAL
#define BLOSSOM_RUNNING_ENVIRONMENT_INTERNAL

#include "../objects/Object.h"
#include "../objects/Method.h"
#include "../ctx/MethodContext.h"

class PrintMethod: public Method {
	Object run(MethodContext ctx);
};

#endif