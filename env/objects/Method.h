
#ifndef BLOSSOM_ENV_METHOD
#define BLOSSOM_ENV_METHOD

#include "env/interpretors/Interpretors.h"
#include "env/objects/Object.h"
#include "env/ctx/MethodContext.h"
#include <string>

struct Method : public Object {
	Object run(MethodContext ctx);
};


#endif