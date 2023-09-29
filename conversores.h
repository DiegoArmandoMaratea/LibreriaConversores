#ifndef CONVERSORES_H
#define CONVERSORES_H

#include <stdint.h>

void initDac();
void initAdc();
void DacConversion(int valor);
int AdcLectura(int channel);

#endif
