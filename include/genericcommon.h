#ifndef _GENERIC_COMMON_H
#define _GENERIC_COMMON_H

#include <stdio.h>
#include<assert.h>
#include <stdlib.h>
#include <string.h>
////////////////////////
// Quelques macros utilisees
// catid et makeid sont 2 macros qui permettent de générer des noms
// de symboles, variables ou fonction
#ifdef catid
#undef catid
#endif
#define catid(a,b) a##b

#ifdef makeid
#undef makeid
#endif
#define makeid(a,b) catid(a,b)


#endif
