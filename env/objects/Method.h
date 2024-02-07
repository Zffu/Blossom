
#ifndef BLOSSOM_ENV_METHOD
#define BLOSSOM_ENV_METHOD

#include "Interpretors.h"
#include "Object.h"
#include "MethodContext.h"
#include <string>

struct Method : public Object {
	Object run(MethodContext ctx);
};


#endif