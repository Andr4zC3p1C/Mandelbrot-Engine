#include "mandelbrot_cpu.h"
#include "engine.h"

uint32_t compute_upper_bound(Complex *num, MS_Engine *engine)
{
	// The sequance for mandelbrot set
	uint32_t i = 0;
	Complex z;
	z.re = 0;
	z.im = 0;
	while (Complex_abs(z) < 2.0  && i < engine->maxIterations)
	{	
		Complex c = Complex_multiply(z, z);
		z = Complex_add(c, *num);
		i++;
	}

	return i;
}

void MS_updatePixel(uint16_t& x, uint16_t& y, Complex *num, MS_Engine *engine)
{
	uint32_t iterations = compute_upper_bound(num, engine);

	double t = (double)iterations / (double)engine->maxIterations;

	// Linear
	/*
	uint32_t color = t * 256.0 * 256.0 * 256.0;
	engine->map.pixels[x * 4 + engine->map.width * y * 4] = color >> 3 * 8;
	engine->map.pixels[x * 4 + 1 + engine->map.width * y * 4] = (color & 0x00ffffff) >> 2 * 8;
	engine->map.pixels[x * 4 + 2 + engine->map.width * y * 4] = (color & 0x0000ffff) >> 8;
	engine->map.pixels[x * 4 + 3 + engine->map.width * y * 4] = 255;

	
	engine->map.pixels[x * 4 + engine->map.width * y * 4] = 255 - (int)(9 * (1 - t)*t*t*t * 255);
	engine->map.pixels[x * 4 + 1 + engine->map.width * y*4] = 255 - (int)(15 * (1 - t)*(1 - t)*t*t * 255);
	engine->map.pixels[x * 4 + 2 + engine->map.width * y*4] = 255 - (int)(8.5 * (1 - t)*(1 - t)*(1 - t)*t * 255);
	engine->map.pixels[x * 4 + 3 + engine->map.width * y*4] = 255;
	*/
	
	engine->map.pixels[x * 4 + engine->map.width * y * 4] = (int)(8.5 * (1 - t)*(1 - t)*(1 - t)*t * 255);
	engine->map.pixels[x * 4 + 1 + engine->map.width * y*4] = (int)(15 * (1 - t)*(1 - t)*t*t * 255);
	engine->map.pixels[x * 4 + 2 + engine->map.width * y*4] = (int)(9 * (1 - t)*t*t*t * 255);
	engine->map.pixels[x * 4 + 3 + engine->map.width * y*4] = 255;
	
}

void MS_convertToComplexPlane(Complex *num, MS_Engine *engine)
{
	// Temporarily storing pixel locations
	double x = num->re;
	double y = num->im;

	// The conversion
	num->re = (x + engine->cameraPos.x / engine->zoom - (double)engine->map.width / 2.0) / (double)(engine->zoom * engine->map.width) * engine->defaultRadious * 2.0;
	num->im = (y + engine->cameraPos.y / engine->zoom - (double)engine->map.height / 2.0) / (double)(engine->zoom * engine->map.width) * engine->defaultRadious * 2.0;
}