#ifndef BLOSSOM_RUNNING_ENVIRONMENT_INTERNAL
#define BLOSSOM_RUNNING_ENVIRONMENT_INTERNAL

#include "Object.h"
#include "Method.h"
#include "MethodContext.h"

class PrintMethod: public Method {
	Object run(MethodContext ctx);
};

#endif