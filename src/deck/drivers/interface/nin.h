#ifndef _NIN_H_
#define _NIN_H_

#include "deck_core.h"

void ninInit(DeckInfo* info);

bool ninTest(void);
void ninTask(void* arg);

#endif /* _NIN_H_ */
