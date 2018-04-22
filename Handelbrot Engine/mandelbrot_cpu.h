#ifndef MANDELBROT_CPU_H
#define MANDELBROT_CPU_H

#include <stdint.h>

struct Complex;
struct MS_Engine;

void MS_updatePixel(uint16_t& x, uint16_t& y, Complex *num, MS_Engine *engine);
void MS_convertToComplexPlane(Complex *num, MS_Engine *engine);

#endif
