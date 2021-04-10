#pragma once
#include <stdio.h>
#include "product.h"

typedef FILE* FP;

FP openWrapper (char *filename, char *mode);
Product* readArbitrary(FP fp, int pos, int count, ...);
void writeArbitrary(FP fp, int count, ...);