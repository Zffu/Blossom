#ifndef BLOSSOM_RUNNING_ENVIRONMENT_INTERNAL
#define BLOSSOM_RUNNING_ENVIRONMENT_INTERNAL

#include "env/objects/Object.h"
#include "env/objects/Method.h"
#include "env/ctx/MethodContext.h"

class PrintMethod: public Method {
	Object run(MethodContext ctx);
};

#endif