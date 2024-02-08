#ifndef BLOSSOM_ENV_OBJECT
#define BLOSSOM_ENV_OBJECT

#include "../interpretors/Interpretors.h"
#include <string>

struct Object {
	std::string getInterpretorEquivalent(Interpretors interpretor);
};

#endif