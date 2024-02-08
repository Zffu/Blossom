
#ifndef BLOSSOM_ENV_METHOD
#define BLOSSOM_ENV_METHOD

#include "../interpretors/Interpretors.h"
#include "../objects/Object.h"
#include "../ctx/MethodContext.h"
#include <string>

struct Method : public Object {
	Object run(MethodContext ctx);
};


#endif